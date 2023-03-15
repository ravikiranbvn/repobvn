#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>
#include<linux/stat.h>
#include<linux/gpio.h>
#include<linux/uaccess.h>
#include<sled.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>

#define BUFF_SZ 80
int GPIO_P3_9;

int maj_num=0;
char lbuff[BUFF_SZ];

int led_init(int gpio_num)
{
	int retVal=0;

	retVal = gpio_request(gpio_num,"sled");

	if(retVal <0 ) 
		return retVal;

	retVal= gpio_direction_output(gpio_num, 1);
	return retVal;
}

void led_on(int gpio_num)
{
	gpio_set_value(gpio_num,1);
}


void led_off(int gpio_num)
{
	gpio_set_value(gpio_num,0);
}

void led_deinit(int gpio_num)
{
	gpio_free(gpio_num);
}

int my_led_open(struct inode *in,struct file *fs)
{
	led_init(GPIO_P3_9);
	printk("my_led_open called...\n");
	return 0;
}
int my_led_close(struct inode *in,struct file *fs)
{
	printk("my_led_close called...\n");
	return 0;
}
int my_led_read(struct file *fp,char *ubuff,size_t sz,loff_t *offset)
{
	printk("my_led_read called...\n");
	return 0;
}
ssize_t my_led_write(struct file *fp, const char __user *ubuff, size_t sz, loff_t *offset)
{
	int ret;
	ret = copy_from_user(lbuff, ubuff, sz);
	printk("Copied...\n");

	if(lbuff[0]=='o' && lbuff[1]=='n')
		led_on(GPIO_P3_9);
	else if(lbuff[0]=='o' && lbuff[1]=='f' && lbuff[2]=='f')
		led_off(GPIO_P3_9);
	else
		printk("Invalid led operation...\n");
	return 0;
}

struct file_operations my_led_fops = {
	.owner = THIS_MODULE,
	.open = my_led_open,
	.release =my_led_close,
	.read = my_led_read,
	.write = my_led_write
     };

static int sled_probe(struct platform_device *pdev)

{
	struct sled_platform_data *sled_pdata = (struct sled_platform_data *)pdev->dev.platform_data;
	printk(KERN_INFO "my device-id %d\n",pdev->id);
	GPIO_P3_9 = sled_pdata->sled_gpio_num;
	printk(KERN_INFO "my sled_no %d \n", GPIO_P3_9);
	return 0;
}

static struct platform_driver sled_drv = {
	 .driver = {
                .owner = THIS_MODULE,
                .name = "sleddrv",
        },
        .probe = sled_probe,
};

static int __init sled_init(void)
{
	maj_num=register_chrdev(0,"my_led_drv",&my_led_fops);
	printk("chr dev Registered with maj num %d\n",maj_num);
	platform_driver_register(&sled_drv);
	return 0;
}
static void __exit sled_exit(void)
{
	unregister_chrdev(maj_num,"my_led_drv");
	printk("simple module is unloaded...\n");
}

module_init(sled_init);
module_exit(sled_exit);

MODULE_LICENSE("GPL");

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "publisher.h"
#include "subscriber.h"

string username;
unsigned long password;
int disp = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ChatBox");

    ui->username->setPlaceholderText(QString("Username"));
    ui->password->setPlaceholderText(QString("Password"));
    ui->password->setEchoMode(QLineEdit::Password);
    ui->type->setPlaceholderText(QString("Type your message here"));

    ui->disp->hide();
    ui->disp_2->hide();
    ui->disp_3->hide();
    ui->disp_4->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->type->hide();
    ui->send->hide();
    ui->logout->hide();

    pb = new CB_Publisher(ui->send, ui->type,
                          ui->pushButton, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4,
                          ui->disp,ui->disp_2, ui->disp_3, ui->disp_4);

    sb = new CB_Subscriber(ui->disp,ui->disp_2, ui->disp_3, ui->disp_4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_type_returnPressed()
{
    ui->send->clicked();
}

void MainWindow::on_password_returnPressed()
{
    username = ui->username->text().toUtf8().constData();
    password = ui->password->text().toInt();

    if((username.compare("Akhil")==0 && password==1) ||
            (username.compare("Chaitu")==0 && password==2) ||
            (username.compare("Alekya")==0 && password==3) ||
            (username.compare("Ravi")==0 && password==4))
    {
        ui->username->hide();
        ui->password->hide();
        ui->disp->show();
        ui->disp_2->show();
        ui->disp_3->show();
        ui->disp_4->show();
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->type->show();
        ui->send->show();
        ui->logout->show();
    }

    else
    {
        info.setText("Entered credentials are wrong");
        info.exec();
    }
}

void MainWindow::on_logout_clicked()
{
    QMessageBox::StandardButton reply = info.question(this,"Chatbox","Are you sure you want to logout?",QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        ui->disp->setText("");
        ui->disp_2->setText("");
        ui->disp_3->setText("");
        ui->disp_4->setText("");
        ui->username->setText("");
        ui->password->setText("");
        ui->disp->hide();
        ui->disp_2->hide();
        ui->disp_3->hide();
        ui->disp_4->hide();
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->type->hide();
        ui->send->hide();
        ui->logout->hide();
        ui->username->show();
        ui->password->show();
    }

}

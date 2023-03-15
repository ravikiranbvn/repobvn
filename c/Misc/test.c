#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Important notes------------------------------------------------------
// Declarations
// int *abc[10];            // An array of 10 elements whose type is pointer to int.
// int (*abc)[10];          // A pointer to a array of 10 elements whose type is int.
// int (*fPtr)(double x);   // fPtr is a pointer to a function that has
// one double parameter and returns int.
// float (* func())[3][10]; // the function func returns a pointer to a two-dimensional array of 3 rows
// and 10 columns

// char *(* fTab[])(void);  // fTab is an array whose elements have the
// type... pointer to... a function, with no parameters, whose
// return value has the type... pointer to... char
// int *(*(*)[10])(void)    // The type “pointer to an array of ten elements whose
// type is pointer to a function with no parameters which
// returns a pointer to int .”

//-----------------------------------------------------------------------
// For function pointer test

float Plus(float a, float b) { return a + b; }
float Minus(float a, float b) { return a - b; }
float Multiply(float a, float b) { return a * b; }
float Divide(float a, float b) { return a / b; }

typedef float (*pt2Func)(float, float);

//------------------------------------------------------------------------

void test_charArray(void)
{
    // code to test the understading of a character array
    char a[10] = "Jim";
    int i = 0;
    printf("%c\n", a[i++]); // i = 0 // output J
    printf("%c\n", a[i]);   // i = 1 // output i
    printf("%c\n", a[++i]); // i = 2 // output m

    //reset i
    i = 0;
    printf("%c %d\n", a[i]++, i); // i = 0  // output J
    printf("%c %d\n", a[i], i);   // i = 0  // output K
    printf("%c %d\n", a[i]++, i); // i = 0  // output K
    printf("%c %d\n", ++a[i], i); // i = 0  // output M
}

//-----------------------------------------------------------------------

void test_ptrArithmetic(void)
{
    // code to test the understading of pointer arithmetic
    double dArr[5] = {0.0, 0.1, 0.2, 0.3, 0.5};
    double *dPtr = dArr;
    int index = 0;
    printf("%.1f\n", *dPtr); // output 0.0
    dPtr += 1;
    printf("%.1f\n", *dPtr); // output 0.1
    dPtr += 1;
    printf("%.1f\n", *dPtr); // output 0.2
    dPtr -= 1;
    printf("%.1f\n", *dPtr); // output 0.1
    dPtr += 2;
    printf("%.1f\n", *dPtr); // output 0.3

    index = dPtr - dArr;
    printf("%d\n", index); // output 3
}

//-----------------------------------------------------------------------

void test_strReverse(void)
{
    char str[11] = "helloWorld";
    printf("before reverse: %s\n", str);

    char ch;
    for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j)
        ch = str[i], str[i] = str[j], str[j] = ch;

    printf("after reverse: %s\n", str);
}

//-----------------------------------------------------------------------

int *create_a_int(int default_value)
{
    int *varPtr = (int *)malloc(sizeof(int));
    *varPtr = default_value;
    return varPtr;
}

void test_basicDynamicMemAlloc(void)
{
    int *ptr = NULL;
    ptr = create_a_int(10);
    printf("%d\n", *ptr);
    free(ptr);
}

//-----------------------------------------------------------------------

typedef int bool_t;
typedef bool_t (*less_than_func_t)(int, int);

bool_t less_than(int a, int b)
{
    return a < b ? 1 : 0;
}

bool_t less_than_modular(int a, int b)
{
    return (a % 5) < (b % 5) ? 1 : 0;
}

void test_functionptr(void)
{
    less_than_func_t func_ptr = NULL;

    func_ptr = &less_than;
    bool_t result = func_ptr(3, 7);
    printf("%d\n", result);

    func_ptr = &less_than_modular;
    result = func_ptr(3, 7);
    printf("%d\n", result);
}

//-----------------------------------------------------------------------

// Solution with a function pointer - <pt2Func> is a function pointer and points to
// a function which takes two floats and returns a float. The function pointer
// "specifies" which operation shall be executed.
// Reference: https://www.newty.de/fpt/intro.html
void Switch_With_Function_Pointer(float a, float b, float (*pt2Func)(float, float))
{
    float result = pt2Func(a, b); // call using function pointer

    printf("Switch replaced by function pointer: 2+5="); // display result
    printf("%f\n", result);
}

void test_funcPtrReplaceSwitch(void)
{
    Switch_With_Function_Pointer(2, 5, &Plus);
}

//-----------------------------------------------------------------------

void test_funcArrayOfPointers(void)
{
    float (*funcArr1[10])(float, float) = {NULL};

    // assign the function's address
    funcArr1[0] = &Plus;
    funcArr1[1] = &Minus;
    funcArr1[2] = &Divide;
    funcArr1[3] = &Multiply;

    // calling a function using an index to address the function pointer
    printf("%f\n", (*funcArr1[0])(56, 30));
    printf("%f\n", (*funcArr1[1])(56, 30));
    printf("%f\n", (*funcArr1[2])(56, 30));
    printf("%f\n", (*funcArr1[3])(56, 30));
}

//-----------------------------------------------------------------

pt2Func GetPtr(const char opCode)
{
    if (opCode == '+')
        return &Plus;
    else if (opCode == '-')
        return &Minus;
    else if (opCode == '/')
        return &Divide;
    else if (opCode == '*')
        return &Multiply;
    else
        return &Plus; // default
}

void test_returnAfuncPtr()
{
    float (*pt2Func)(float, float) = {NULL};

    pt2Func = GetPtr('*');
    printf("%f\n", (*pt2Func)(2, 4));
}

//-----------------------------------------------------------------

typedef void (*callback)(void);
void register_callback(callback ptr_reg_callback);

/* registration goes here */
void register_callback(callback ptr_reg_callback)
{
    printf("inside register_callback\n");
    /* calling our callback function my_callback */
    (*ptr_reg_callback)();                                  
}

/* callback function definition goes here */
void my_callback(void)
{
    printf("inside my_callback\n");
}
 
void test_callBack(void)
{
    /* initialize function pointer to my_callback */
    callback ptr_my_callback = my_callback;                           
    printf("This is a program demonstrating function callback\n");
    /* register our callback function */
    register_callback(ptr_my_callback);                             
    printf("back inside test callBack func()\n");
}

//-----------------------------------------------------------------

int main()
{
    // Enable only one test to run and see results
    
    // test_charArray();
    // test_ptrArithmetic();
    // test_strReverse();
    // test_basicDynamicMemAlloc();
    // test_functionptr();
    // test_funcPtrReplaceSwitch();
    // test_funcArrayOfPointers();
    // test_returnAfuncPtr();
    // test_callBack();

    return 0;
}
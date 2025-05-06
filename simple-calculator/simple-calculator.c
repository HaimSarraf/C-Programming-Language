#include <stdio.h>
#include <math.h>

int main()
{
    int num1, num2, operator;

    float result;

    printf("Welcome to Simple Calculator\n");

    printf("Choose one of the Following Operators :\n1.Add\n2.Subtract\n3.Multiply\n4.Divine\n5.Modulus\n6.Power\n7.Exit\n");

    printf("\nNow Enter Your Choise's Number :");

    scanf("%d", &operator);

    printf("Please Enter The First Number : ");

    scanf("%d", &num1);

    printf("Now, Enter The Second Number : ");

    scanf("%d", &num2);

    if (operator == 1)
    {
        result = num1 + num2;
    }
    else if (operator == 2)
    {
        result = num1 - num2;
    }
    else if (operator == 3)
    {
        result = num1 * num2;
    }
    else if (operator == 4)
    {
        result = num1 / num2;
    }
    else if (operator == 5)
    {
        result = num1 % num2;
    }
    else if (operator == 6)
    {
        result = num1 ^ num2;
    }
    else if (operator == 7)
    {
        printf("Exit\n");
    }
    else
        printf("Please Enter a Valid Number (1-7)");

    printf("Result of Operation is : %.2f\n", result);
}
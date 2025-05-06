#include <stdio.h>
#include <math.h>

double division(double, double);
double modulus(double, double);
void choose_an_operator();

int main()
{
    int operator;

    double num1, num2, result;

    while (1)
    {
        choose_an_operator();

        scanf("%d", &operator);

        if (operator <= 0 || operator >= 7)
        {
            break;
        }

        printf("\nPlease Enter The First Number : ");
        scanf("%lf", &num1);
        printf("\nNow, Enter The Second Number : ");
        scanf("%lf", &num2);

        switch (operator)
        {
        case 1:
            result = num1 + num2;
            break;
        case 2:
            result = num1 - num2;
            break;
        case 3:
            result = num1 * num2;
            break;
        case 4:
            result = division(num1, num2);
            break;
        case 5:
            result = modulus(num1, num2);
            break;
        case 6:
            result = pow(num1, num2);
            break;

        default:
            break;
        }
        printf("\nResult of Operation is : %.2f", result);
    };

    return 0;
}

void choose_an_operator()
{
    printf("\n\n\n\n\nWelcome to Simple Calculator\n");
    printf("\nChoose one of the Following Operators :\n");
    printf("1.Add\n");
    printf("2.Subtract\n");
    printf("3.Multiply\n");
    printf("4.Divine\n");
    printf("5.Modulus\n");
    printf("6.Power\n");
    printf("7.EXIT\n");
    printf("\nNow Enter Your Choise's Number :");
}

double division(double a, double b)
{

    if (b == 0)
    {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return NAN;
    }

    return a / b;
}
double modulus(double a, double b)
{
    if (b == 0)
    {
        fprintf(stderr, "Error: Modulus by zero is not allowed.\n");
        return NAN;
    }

    return (int)a % (int)b;
}
#include <stdio.h>

int difficulty;

void input_difficulty();

int main()
{
    input_difficulty();
}

void input_difficulty()
{
    while (1)
    {
        printf("\nSelect Difficulty : ");

        printf("\n1. Easy(Standard)");

        printf("\n2. Veteran(Impossible to win)");

        printf("\nEnter Your Choise : ");

        scanf("%d", &difficulty);

        if (difficulty != 1 && difficulty != 2)
        {
            printf("\n\nIncorrect choise !!\n\n");
        }
        else
        {
            break;
        }
    }
}
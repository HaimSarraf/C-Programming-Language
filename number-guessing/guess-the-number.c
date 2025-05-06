#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int random, guess, number_of_Guesses = 0;

    srand(time(NULL));

    printf("The Number_Guessing Game Just Started\n");

    random = rand() % 100 + 1 ;

    do
    {
        printf("Please Enter Your Guess between 1 to 100 : ");

        scanf("%d", &guess);

        number_of_Guesses++;

        if (guess < random)
        {
            printf("Enter a Bigger Number.\n");
        }
        else if (guess > random)
        {
            printf("Enter a smaller Number.\n");
        }
        else
        {
            printf("Congratulations ! You Guessed The Currect Number in %d Attempts !!!", number_of_Guesses);
        }

    } while (guess != random);

    printf("\n :)");
}
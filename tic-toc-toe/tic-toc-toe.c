#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int Player;
    int CPU;
    int Draw;
} Score;

int difficulty;
Score score = {.Player = 0, .CPU = 0, .Draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[3][3]);
int check_win(char board[3][3], char player);
// int check_draw(char board[3][3]);

int main()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    input_difficulty();

    print_board(board);
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

void clear_screen()
{
#ifdef _Win32
    system("cls");
#else
    system("clear");
#endif
}

void print_board(char board[3][3])
{
    clear_screen();

    printf("\nScore : [ Player : %d\t CPU : %d\tDraw : %d ]",
           score.Player, score.CPU, score.Draw);

    printf("\n\nTic Toc Toe\n\n");

    for (int i = 0; i < 3; i++)
    {
        printf("\n");

        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", board[i][j]);

            if (j < 2)
            {
                printf("|");
            }
        }

        if (i < 2)
        {
            printf("\n---+---+---");
        }
    }

    printf("\n\n");
}

int check_win(char board[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (
            board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return 1;
        }
        if (
            board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return 1;
        }
    }

    if (
        board[0][0] == player &&
            board[1][1] == player &&
            board[2][2] == player ||
        board[0][2] == player &&
            board[1][1] == player &&
            board[2][0] == player)
    {
        return 1;
    }

    return 0;
}

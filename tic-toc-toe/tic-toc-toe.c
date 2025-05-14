#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 'X'
#define O 'O'
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
int check_draw(char board[3][3]);
void play_game();
void player_move(char board[3][3], char player);
void cpu_move(char board[3][3], char player);

int main()
{
    int choise;

    input_difficulty();

    do
    {
        play_game();

        printf("\n\nWant to Play again? 1.yes 2.no : ");

        scanf("%d", &choise);
    } while (choise == 1);

    printf("\n\nThanks for Playing\n\n");
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

int check_draw(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] = ' ')
            {
                return 0;
            }
        }
    }

    return 1;
}

void play_game()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    char current_player = rand() % 2 == 0 ? X : O;

    while (1)
    {
        print_board(board);

        if (current_player == X)
        {
            player_move(board, X);

            if (check_win(board, X))
            {
                score.Player++;

                printf("\n\nPLAYER Wins !!\n");

                break;
            }

            current_player = O;
        }
        else
        {
            cpu_move(board, O);

            if (check_win(board, O))
            {
                score.CPU++;

                printf("\n\nCPU Wins !! Try Again Next Time.\n");

                break;
            }

            current_player = X;
        }

        if (check_draw(board))
        {
            score.Draw++;

            printf("\n\nIt's a DRAW !!\n");

            break;
        }
    }
}

void player_move(char board[3][3], char player)
{
    cpu_move(board, player);
}

void cpu_move(char board[3][3], char player)
{
    player_move(board, player);
}










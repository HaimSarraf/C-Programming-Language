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
Score score = {.Player = 0, .CPU = 0, .Draw = 0};

typedef struct
{
    int Easy;
    int Hard;
} Difficulty;
Difficulty difficulty = {.Easy = 0, .Hard = 1};

void input_difficulty();
void clear_screen();
void print_board(char board[3][3]);
int check_win(char board[3][3], char player);
int check_draw(char board[3][3]);
void play_game();
void player_move(char board[3][3]);
void cpu_move(char board[3][3]);
int is_valid_move(char board[3][3], int row, int col);

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
    int choice;

    while (1)
    {
        printf("\nSelect Difficulty : ");

        printf("\n1. Easy(Standard)");

        printf("\n2. Veteran(Impossible to win)");

        printf("\nEnter Your Choice : ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            difficulty.Easy = 1;
            difficulty.Hard = 0;
            break;
        }
        else if (choice == 2)
        {
            difficulty.Easy = 0;
            difficulty.Hard = 1;
            break;
        }
        else
        {
            printf("\n\nIncorrect choice !!\n\n");
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
            if (board[i][j] == ' ')
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

    print_board(board);

    while (1)
    {
        if (current_player == X)
        {
            player_move(board);

            print_board(board);

            if (check_win(board, X))
            {
                score.Player++;

                print_board(board);

                printf("\n\nPLAYER Wins !!\n");

                break;
            }

            current_player = O;
        }
        else
        {
            cpu_move(board);

            print_board(board);

            if (check_win(board, O))
            {
                score.CPU++;

                print_board(board);

                printf("\n\nCPU Wins !! Try Again Next Time.\n");

                break;
            }

            current_player = X;
        }

        if (check_draw(board))
        {
            score.Draw++;

            print_board(board);

            printf("\n\nIt's a DRAW !!\n");

            break;
        }
    }
}

void player_move(char board[3][3])
{
    int count = 0, x, y;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1)
    {
        board[x][y] = X;
        
        return;
    }

    int row, col;

    do
    {
        printf("\nPlayer's Turn.");

        printf("\nEnter Row and Column (1-3) for Player : ");

        scanf("%d", &row);

        scanf("%d", &col);

        row--; // converting to zero-based

        col--; // converting to zero-based

    } while (!is_valid_move(board, row, col));

    board[row][col] = X;
}

void cpu_move(char board[3][3])
{
    //? 1. Play for immediate win
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;

                if (check_win(board, O))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    //! 2. Play for immediate block
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;

                if (check_win(board, X))
                {
                    board[i][j] = O;

                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Hard mode
    if (difficulty.Hard)
    {
        //! 3.Play Center if possible
        if (board[1][1] == ' ')
        {
            board[1][1] = O;
            return;
        }
    }

    //? 4.Play for corners if possible
    if (board[0][0] == ' ')
    {
        board[0][0] = O;
        return;
    }
    if (board[0][2] == ' ')
    {
        board[0][2] = O;
        return;
    }
    if (board[2][0] == ' ')
    {
        board[2][0] = O;
        return;
    }
    if (board[2][2] == ' ')
    {
        board[2][2] = O;
        return;
    }

    //* 5.Play for first available move
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;

                return;
            }
        }
    }
}

int is_valid_move(char board[3][3], int row, int col)
{
    return !(row < 0 || row > 2 ||
             col < 0 || col > 2 ||
             board[row][col] != ' ');
}

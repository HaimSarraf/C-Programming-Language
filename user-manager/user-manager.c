#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_USERS 10
#define LENGTH 30

typedef struct
{
    char username[LENGTH];
    char password[LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int login_user(); // return the user index
void fix_fgets_input(char *);
void input_credentials(char *username, char *password);

int main()
{
    int option;

    while (1)
    {
        printf("\n\n---------------------------------------------------------------------");
        printf("\nUser Management Panel\n");
        printf("\n1.Register");
        printf("\n2.Login");
        printf("\n3.Exit the Panel");
        printf("\nSelect an Option: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:

            register_user();

            break;
        case 2:

            int user_index = login_user();

            if (user_index >= 0)
            {
                printf("\nLogin Successfull ! Welcome, %s !", users[user_index].username);
            }
            else
            {
                printf("\nLogin Failed. Incorrect Username or Password !\n");
            }

            break;
        case 3:

            printf("\nExiting The Panel\n");

            return 0;

            break;

        default:
            printf("\nInvalid Option. Choose between 1, 2 or 3 ! \n");

            break;
        }
    }

    return 0;
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("No more Registration available\n");
        return;
    }

    int new_index = user_count;

    printf("Register a new User :\n");

    input_credentials(users[new_index].username, users[new_index].password);

    user_count++;

    printf("\nRegistration Successful !\n");
}

int login_user()
{
    char username[LENGTH];
    char password[LENGTH];

    input_credentials(username, password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }

    return -1;
}

void input_credentials(char *username, char *password)
{
    printf("\nEnter username : ");

    fgets(username, LENGTH, stdin);

    fix_fgets_input(username);

    printf("Enter Password : ");

    fflush(stdout);

    // Change terminal Properties
    struct termios old_props, new_props;
    if (tcgetattr(STDIN_FILENO, &old_props) != 0)
    {
        perror("tcgetattr failed");
        return;
    }
    new_props = old_props;
    new_props.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_props) != 0)
    {
        perror("tcsetattr failed");
        return;
    }

    char ch;
    int i = 0;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {

        if (ch == '\b' || ch == 127) // 127: ASCII for DEL
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_props) != 0)
    {
        perror("tcsetattr failed to restore");
    }
}

void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");

    string[index] = '\0';
}

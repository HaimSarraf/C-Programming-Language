#include <stdio.h>
#include <string.h>

void create_account();
void deposite_money();
void withdraw_money();
void check_balance();

const char *ACCOUNT_FILE = "account.dat";

typedef struct
{
    char name[50];
    int acc_no;
    float balacne;
} Account;

int main()
{

    while (1)

    {
        int chiose;
        printf("\n\n*** Bank Management Systam***");
        printf("\n1. Create Account");
        printf("\n2. Deposite Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. EXIT\n\n");
        printf("\nEnter your choise please : ");
        scanf("%d", &chiose);

        switch (chiose)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposite_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("Closing the Panel. Thanks for Your visit .");
            return 0;
            break;

        default:
            printf("Invalid Choise !\n");
            break;
        }
    }
}

void create_account()
{
    Account acc;

    printf("\nCrating Account...\n");

    //!

    FILE *file = fopen(ACCOUNT_FILE, "ab+");

    if (file == NULL)
    {
        printf("Unable to Open File !!");

        return;
    }

    //!

    char ch;

    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    printf("\nEnter Your Name : ");

    fgets(acc.name, sizeof(acc.name), stdin);

    int ind = strcspn(acc.name, "\n");

    acc.name[ind] = '\0';

    printf("\nEnter Your Account-No : ");

    scanf("%d", &acc.acc_no);

    acc.balacne = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);

    printf("\nAccount Created Successfully!");
}

void deposite_money()
{
    printf("\nDepositing Money...\n");

    FILE *file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL)
    {
        printf("Unable to Open FILE !!");

        return;
    }

    int acc_no;

    float money;

    Account acc_to_read;

    printf("Enter Your Account_No: ");

    scanf("%d", &acc_no);

    printf("Enter Amount to Deposite: ");
    
    scanf("%f", &money);
    
    while (fread(&acc_to_read, sizeof(acc_to_read), 1, file))
    {
        

        if (acc_to_read.acc_no == acc_no)
        {
            acc_to_read.balacne += money;

            fseek(file, -sizeof(acc_to_read), SEEK_CUR);

            fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);

            fclose(file);

            printf("Successfully Deposited [ %.2f ] $ !"
                   "\nNew Balance is [ %.2f ] $ !"
                   "\n\nACCOUNT_NO_[%d] *** ACCOUNT_BALANCE_[ %.2f ]$",
                   money, acc_to_read.balacne,
                   acc_to_read.acc_no, acc_to_read.balacne);
            return;
        }
    }

    fclose(file);

    printf("Money could not be Deposited Since Account_No_%d was Not Found in records !!", acc_no);
}

void withdraw_money()
{
    printf("\nWithdrawing Money...\n");

    FILE *file = fopen(ACCOUNT_FILE, "rb+");

    if (file ==NULL)
    {
        printf("\nUnable to Open File !!");

        return;
    }
    
    Account acc_to_read;

    int acc_no;

    float money;

    printf("Enter Your Account_No: ");

    scanf("%d", &acc_no);

    printf("Enter the Amount you wish to Withdraw: ");

    scanf("%f", &money);

    while (fread(&acc_to_read, sizeof(acc_to_read),1,file))
    {
        if (acc_to_read.acc_no == acc_no)
        {
            if (acc_to_read.balacne >= money)
            {
                acc_to_read.balacne -= money;

                fseek(file, -sizeof(acc_to_read), SEEK_CUR);

                fwrite(&acc_to_read, sizeof(acc_to_read), 1, file );
            
                printf("\nSuccessfully witdrawn [ %.2f ] $"
                       "\nReamining Balance is [ %.2f ] $"
                       "\n\nACCONT_NO_%d *** ACCOUNT_BALANCE_[ %.2f ] $\n",
                       money, acc_to_read.balacne ,
                       acc_to_read.acc_no, acc_to_read.balacne
                );
            } else {
                printf("\nInsufficient Balance !!\n");
            }
            
            fclose(file);
            return;
        }
        
    }

    fclose(file);
    
    printf("Money could not be Witdrawn Since Account_No_%d was Not Found in records !!", acc_no);
    
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");

    printf("\nChecking Your Balance...\n");

    if (file == NULL)
    {
        printf("Unable to Open File !!");
    }

    int acc_no;

    Account acc_read;

    printf("Please Enter Your Account Number :");

    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("\nYour Current Balance is [ %.2f ] $", acc_read.balacne);

            fclose(file);

            return;
        }
    }

    printf("\nAccount No:%d NOT FOUND !!\n", acc_no);
}

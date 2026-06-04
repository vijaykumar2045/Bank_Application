#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Bank
{
    char username[50];
    char password[50];

    int accountNumber;

    char name[50];
    char gender[10];
    char dob[20];

    char email[50];
    char phone[15];

    float balance;

} user;

int verifyAccountNumber(int acc)
{
    return (acc >= 1000 && acc <= 9999);
}

int verifyPhone(char phone[])
{
    int i;

    if(strlen(phone) != 10)
        return 0;

    for(i = 0; i < 10; i++)
    {
        if(!isdigit(phone[i]))
            return 0;
    }

    return 1;
}

int verifyEmail(char email[])
{
    if(strchr(email, '@') != NULL &&strstr(email, ".com") != NULL)
        return 1;

    return 0;
}

int verifyPassword(char pass[])
{
    int i;
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    if(strlen(pass) < 6)
        return 0;

    for(i = 0; pass[i] != '\0'; i++)
    {
        if(isupper(pass[i]))
            upper = 1;
        else if(islower(pass[i]))
            lower = 1;
        else if(isdigit(pass[i]))
            digit = 1;
        else
            special = 1;
    }

    return (upper && lower && digit && special);
}

void registration()
{
    printf("\n===== REGISTRATION =====\n");

    printf("Create Username: ");
    scanf("%s", user.username);

    do
    {
        printf("Create Password: ");
        scanf("%s", user.password);

        if(!verifyPassword(user.password))
        {
            printf("\nPassword must contain:\n");
            printf("- Minimum 6 characters\n");
            printf("- One Uppercase Letter\n");
            printf("- One Lowercase Letter\n");
            printf("- One Digit\n");
            printf("- One Special Character\n\n");
        }

    } while(!verifyPassword(user.password));

    do
    {
        printf("Enter Account Number (4 digits): ");
        scanf("%d", &user.accountNumber);

        if(!verifyAccountNumber(user.accountNumber))
            printf("Invalid Account Number\n");

    } while(!verifyAccountNumber(user.accountNumber));

    getchar();

    printf("Enter Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    printf("Enter Gender: ");
    scanf("%s", user.gender);

    printf("Enter Date of Birth(DD/MM/YYYY): ");
    scanf("%s", user.dob);

    do
    {
        printf("Enter Email ID: ");
        scanf("%s", user.email);

        if(!verifyEmail(user.email))
            printf("Invalid Email ID\n");

    } while(!verifyEmail(user.email));

    do
    {
        printf("Enter Phone Number: ");
        scanf("%s", user.phone);

        if(!verifyPhone(user.phone))
            printf("Invalid Phone Number\n");

    } while(!verifyPhone(user.phone));

    printf("Enter Initial Balance: ");
    scanf("%f", &user.balance);

    printf("\nRegistration Successful\n");
}

int login()
{
    char uname[50];
    char pass[50];

    printf("\n===== LOGIN =====\n");

    printf("Enter Username: ");
    scanf("%s", uname);

    printf("Enter Password: ");
    scanf("%s", pass);

    if(strcmp(uname, user.username) == 0 && strcmp(pass, user.password) == 0)
    {
        return 1;
    }

    return 0;
}

void bankMenu()
{
    int choice;
    float amount;
    char ch;

    while(1)
    {
        printf("\n===== BANK MENU =====\n");
        printf("1. Balance Enquiry\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Account Details\n");
        printf("5. Logout\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nCurrent Balance: %.2f\n", user.balance);
                break;

            case 2:
                printf("Enter Deposit Amount: ");
                scanf("%f", &amount);

                if(amount > 0)
                {
                    user.balance += amount;

                    printf("Amount Deposited Successfully\n");

                    printf("Do you want  check your balance? (Yes/No): ");
                    scanf(" %s", &ch);

                    if(ch == 'Y' || ch == 'y')
                    {
                        printf("Current Balance: %.2f\n", user.balance);
                    }
                }
                else
                {
                    printf("Invalid Amount\n");
                }
                break;

            case 3:
                printf("Enter Withdraw Amount: ");
                scanf("%f", &amount);

                if(amount <= 0)
                {
                    printf("Invalid Amount\n");
                }
                else if(amount > user.balance)
                {
                    printf("Insufficient Balance\n");
                }
                else
                {
                    (user.balance -= amount);

                    printf("Amount Withdrawn Successfully\n");

                    printf("Do you want check your balance? (Yes/No): ");
                    scanf(" %s", &ch);

                    if(ch == 'Y' || ch == 'y')
                    {
                        printf("Current Balance: %.2f\n", user.balance);
                    }
                }
                break;

            case 4:
                printf("\n===== ACCOUNT DETAILS =====\n");
                printf("Name            : %s\n", user.name);
                printf("Gender          : %s\n", user.gender);
                printf("Date of Birth   : %s\n", user.dob);
                printf("Email ID        : %s\n", user.email);
                printf("Phone Number    : %s\n", user.phone);
                printf("Account Number  : %d\n", user.accountNumber);
                printf("Balance         : %.2f\n", user.balance);
                break;

            case 5:
                printf("\nLogged Out Successfully\n");
                return;


            default:
                printf("Invalid Choice\n");
        }

    } while(1);
}

int main()
{
    int mainChoice;

    do
    {
        printf("\n===== BANK APPLICATION =====\n");
        printf("1. Registration\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &mainChoice);

        switch(mainChoice)
        {
            case 1:
                registration();
                break;

            case 2:
                if(strlen(user.username) == 0)
                {
                    printf("\nPlease Register First\n");
                }
                else if(login())
                {
                    printf("\nLogin Successful\n");
                    bankMenu();
                }
                else
                {
                    printf("\nInvalid Username or Password\n");
                }
                break;

            case 3:
                printf("\nThank You For Visiting Our Bank \n");
                break;

            default:
                printf("\nInvalid Choice\n");
        }

    } while(mainChoice != 3);

    return 0;
}




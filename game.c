//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUSIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
// system includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// system dependant includes
#ifdef _WIN64
#include <conio.h>
#else
#define clear_screen() printf("\e[1;1H\e[2J")
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TRUE 1
#define FALSE 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY DECLARATION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int DICE[6] = {1, 2, 3, 4, 5, 6};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN MENU FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mainMenu(void)
{
    printf("########## 2 PLAYER DICE GAME ##########\n");
    
    int MAIN_MENU_LOOP = TRUE;
    while (MAIN_MENU_LOOP == TRUE)
    {
        printf("1.) continue to login\n");
        printf("2.) view high scores\n");
        printf("3.) rules\n");
        printf("4.) exit program");

        int userInput;
        scanf("%d", &userInput);
    }

    // return
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOGIN FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// temp buffer to hold usernames and passwords from logins.txt
typedef struct userAndPassTypeTag
{
    char username[32];
    char password[32];
}
userAndPassType;

userAndPassType userData[16];

int ADD_USER_TO_FILE (char* username, char* password)
{
    FILE *LOGINFILE = fopen("assets/logins.txt", "a");

    if (LOGINFILE == NULL)
    {
        printf("assets/logins.txt is missing, please create this file\n");
        return 1;
    }

    fprintf(LOGINFILE, "%s", username);
    fprintf(LOGINFILE, ",");
    fprintf(LOGINFILE, "%s", password);
    fprintf(LOGINFILE, "\n");
    fclose(LOGINFILE);

    printf("%s has been validated\n", username);

    // return
    return 0;
}

int CHECK_USER (char* username, char *password)
{
    FILE *LOGINFILE = fopen("assets/logins.txt", "r");
    
    if (LOGINFILE == NULL)
    {
        printf("assets/logins.txt is missing, please create this file\n");
        return 1;
    }

    char currentChar = 0;
    char tempBuffer[32];
    unsigned int structureIndex = 0u;
    unsigned int bufferIndex = 0u;

    while (currentChar != EOF)
    {
        currentChar = fgetc(LOGINFILE);

        if (currentChar == ',') 
        {
            tempBuffer[bufferIndex] = 0;
            strcpy(userData[structureIndex].username, tempBuffer);
            bufferIndex = 0u;
        }
        else if (currentChar == '\n')
        {
            tempBuffer[bufferIndex] = 0;
            strcpy(userData[structureIndex].password, tempBuffer);
            bufferIndex = 0u;
            structureIndex++;
        }
        else
        {
            tempBuffer[bufferIndex] = currentChar;
            bufferIndex++;
        }
    }    
    
    fclose(LOGINFILE);
    
    int index = 0;
    
    while (index < sizeof(userData))
    {
        if (strcmp(userData[index].username, username) == 0)
        {
            if (strcmp(userData[index].password, password) == 0)
            {
                printf("welcome %s\n", username);
                sleep(1);
                break;
            }
            else
            {
            printf("incorrect password\n");
            clear_screen();
            index++;
            //return USER_LOGIN();
            }
        }
        else
        {
            printf("incorrect username\n");
            clear_screen();
            index++;
            //return USER_LOGIN();
        }
    }
    
    /* ---------------------------------------------------------------------
    TO DO: FIX SO PROGRAM DOESNT CRASH WHEN AN INCORRECT USERNAME IS ENTERED 
    --------------------------------------------------------------------- */ 

    // return
    return 0;
}

int CREATE_USER (void)
{
    int CREATE_USER_LOOP = TRUE;
    while (CREATE_USER_LOOP == TRUE)
    {
        clear_screen();
        
        char username[15], password[15];
        printf("enter your username for the new user\n");
        scanf("%s", username);
        printf("enter your password for the new user\n");
        scanf("%s", password);

        int confirmUsername;
        printf("is %s your username? type '1' for yes, '2' for no\n", username);
        scanf("%d", &confirmUsername);

        if (confirmUsername == 1)
        {
            int confirmPassword;
            printf("is %s your password? type '1' for yes, '2' for no\n", password);
            scanf("%d", &confirmPassword);

            if (confirmPassword == 1)
            {
                ADD_USER_TO_FILE(username, password);
                CREATE_USER_LOOP = FALSE;
            }
            else
            {
                clear_screen();
                continue;
            }
        }
        else
        {
            clear_screen();
            continue;
        }

    }
    
    // return
    return 0;
}

int USER_LOGIN (void)
{
    int VALIDATION_LOOP = TRUE;
    while (VALIDATION_LOOP == TRUE)
    {
        clear_screen();

        char username[15], password[15];
        printf("enter your username for the existing user\n");
        scanf("%s", username);
        printf("enter your password for the existing user\n");
        scanf("%s", password);

        int confirmUsername;
        printf("is %s your username? type '1' for yes, '2' for no\n", username);
        scanf("%d", &confirmUsername);

        if (confirmUsername == 1)
        {
            int confirmPassword;
            printf("is %s your password? type '1' for yes, '2' for no\n", password);
            scanf("%d", &confirmPassword);

            if (confirmPassword == 1)
            {
                CHECK_USER(username, password);
                VALIDATION_LOOP = FALSE;
            }
            else
            {
                clear_screen();
                continue;
            }
        }
        else
        {
            clear_screen();
            continue;
        }
    }
    
    // return 
    return 0;
}

int player1Login (void)
{
    int PLAYER_1_LOGIN_LOOP = TRUE;
    while (PLAYER_1_LOGIN_LOOP == TRUE)
    {
        clear_screen();
        printf("##### PLAYER 1 LOGIN #####\n");
        printf("1.) create new user\n");
        printf("2.) use existing user\n");

        int userInput;
        scanf("%d", &userInput);

        if (userInput == 1)
        {
            CREATE_USER();

            printf("would you like to create another user? type '1' for yes, '2' for no\n");

            int userInput;
            scanf("%d", &userInput);

            while (userInput == 1)
            {
                clear_screen();
                CREATE_USER();

                printf("would you like to create another user? type '1' for yes, '2' for no\n");

                int userInput;
                scanf("%d", &userInput);

                if (userInput != 1)
                {
                    clear_screen();
                    break;
                }
            }

            USER_LOGIN();
            break;
        }
        else if (userInput == 2)
        {
            USER_LOGIN();
            break;
        }
        else
        {
            printf("invalid input - try again\n");
            continue;
        }
    }
    
    // return
    return 0;    
}

int player2Login (void)
{
    int PLAYER_2_LOGIN_LOOP = TRUE;
    while (PLAYER_2_LOGIN_LOOP == TRUE)
    {
        clear_screen();
        printf("##### PLAYER 2 LOGIN #####\n");
        printf("1.) create new user\n");
        printf("2.) use existing user\n");

        int userInput;
        scanf("%d", &userInput);

        if (userInput == 1)
        {
            CREATE_USER();

            printf("would you like to create another user? type '1' for yes, '2' for no\n");

            int userInput;
            scanf("%d", &userInput);

            while (userInput == 1)
            {
                clear_screen();
                CREATE_USER();

                printf("would you like to create another user? type '1' for yes, '2' for no\n");

                int userInput;
                scanf("%d", &userInput);

                if (userInput != 1)
                {
                    clear_screen();
                    break;
                }
            }

            USER_LOGIN();
            break;
        }
        else if (userInput == 2)
        {
            USER_LOGIN();
            break;
        }
        else
        {
            printf("invalid input - try again\n");
            continue;
        }
    }
    
    // return
    return 0;    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main (void)
{
    // main menu function call
    //mainMenu();
    // player login function calls
    player1Login();
    player2Login();
    // return
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

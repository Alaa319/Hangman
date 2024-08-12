#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 20
#define STRIKES 6

void rules(void); //display rules of the game
void maskWord(char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no

int main()
{

    FILE *wordList = fopen("words.txt", "r"); 

    rules();

    int *play; 
    char starword[SIZE]; 
    char answer[SIZE]; 

    do
    {
        fscanf(wordList, "%s", answer); 
        int len = strlen(answer);
        answer[len] = '\0'; 

        maskWord(starword, len);

        int gameResult = playRound(starword, answer); 

        if(gameResult == 0)
        {
            printf("Sorry! YOU GUESSED THE INCORRECT WORD!\n");
            printf("The correct word is: %s\n", answer); 
        }

        else if(gameResult == 1)
        {
            printf("Congratulations! YOU GUESSED THE CORRECT WORD!\n");
        }
        playAgain(play);

    } while (*play != 2);

    fclose(wordList); 

    printf("Great Game!\n"); 
    printf("Play again soon!\n"); 
    
    return 0;
}


void rules(void)
{
    printf("Let's Play some Hangman!\n"); 
    printf("Here are the rules:\n"); 
    printf("-The * characters will show you the number of letters that are in the word.\n"); 
    printf("-You have to guess the letters of the mystery word.\n"); 
    printf("-Once you guess a correct letter, the * will be removed and reveal the letters' place in the word.\n"); 
    printf("-You are only allowed 6 strikes, once those 6 strikes are up you lose.\n"); 
    printf("Let's begin!\n"); 
}

void maskWord (char starword[], int size)
{
    for(int x = 0; x < size; x++)
    {
        starword[x] = '*'; 
    }
    starword[size] = '\0';
}

int playRound(char starword[], char answer[])
{
    int strike = 0; 
    int tries = 0; 
    char guess;
    int length = strlen(answer); 
    char letters[SIZE];

    letters[0] = '\0'; 

    printf("Welcome to the New Round!\n"); 
    printf("Number of letters in word: %d\n", length); 

    while(strike < STRIKES)
    {
        printf("Strikes used: %d\n", strike); 
        printf("Letters that you guessed: %s\n", letters); 
        printf("%s\n", starword); 

        printf("************************************************************************\n"); 

        printf("Enter the letter that you would like to guess: "); 
        scanf(" %c", &guess); 

        guess = tolower(guess); 
        
        int cast = (int)guess; 

        if(guess >= 97 && guess <= 122)
        {
            letters[tries + 1] = '\0'; 
            letters[tries] = guess; 
            tries++; 

            int occur = occurancesInWord(guess, answer);

            if(occur == 0)
            {
                printf(" %c isn't in the word. Try again!\n", guess); 
                strike++; 
            }

            else
            {
                updateStarWord(starword, answer, guess); 

                int gameResult = strcmp(starword, answer); 

                if(gameResult == 0)
                {
                    return 1; 
                }

                printf("%c is in the word. Great Job!\n", guess); 
            }  
        }

        else
        {
            printf("INVALID GUESS! Please enter a letter!\n");  
        }
    }

    return 0; 
}

int occurancesInWord(char userguess, char answer[])
{
    int occurs = 0; 

    for(int in = 0; in < SIZE; in++)
    {
        if(answer[in] == userguess)
        {
            occurs++; 
        }
    }

    return occurs; 
}

void updateStarWord(char starword[], char answer[], char userguess)
{
    int occurs = occurancesInWord(userguess, answer); 

    while(occurs > 0)
    {
        for(int update = 0; update < SIZE; update++)
        {
            if(answer[update] == userguess)
            {
                starword[update] = answer[update];
                occurs--;  
            }
        }
    }
}

void playAgain(int *play)
{

    printf("Do you want to play again?\n"); 
    printf("1 = YES\n");
    printf("2 = NO\n"); 
    printf("Enter you choice (1 or 2): ");
    scanf("%d", play); 

    while(*play > 2 || *play < 1)
    {
        printf("You have entered an invalid option!\n"); 
        printf("Enter another choice: "); 
        printf("Do you want to play again?\n"); 
        printf("1 = YES\n");
        printf("2 = NO\n"); 
        printf("Enter you choice (1 or 2): ");
        scanf("%d", play); 
    }
}
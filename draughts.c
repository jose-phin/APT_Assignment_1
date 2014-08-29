/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"
#define CHOICE 3

int main (int argc, char *argv[])
{
    struct result scoreboard[SCOREBOARDSIZE];

    int choice;
    char choice_char[CHOICE];
    char player1[MAX_NAME_LEN];
    char player2[MAX_NAME_LEN];

    char p1[MAX_NAME_LEN];
    char p2[MAX_NAME_LEN];


    while(choice != (1 || 2 || 3 || 4)){

        printf("English Draughts - Main Menu\n");
        printf("1) Play Game\n");
        printf("2) Display Winner\n");
        printf("3) Reset scoreboard\n");
        printf("4) Quit\n");

        printf("Enter your choice:");
        fgets(choice_char,CHOICE, stdin);

        if(choice_char[strlen(choice_char)-1]!='\n')
            read_rest_of_line();


        choice_char[strlen(choice_char)-1]='\0';
        choice = atoi(choice_char);

        switch(choice){

            case 1:{

                printf("Enter player1:");
                fgets(player1,MAX_NAME_LEN+1,stdin);

                while(player1[strlen(player1)-1] != '\n'){
                    read_rest_of_line();
                    printf("Name is too long, re-enter:");
                    fgets(player1,MAX_NAME_LEN+1,stdin);
                }

                player1[strlen(player1)-1]='\0';

                printf("Enter player2:");
                fgets(player2,MAX_NAME_LEN+1,stdin);

                while(player2[strlen(player2)-1] != '\n'){
                    read_rest_of_line();
                    printf("Name is too long, re-enter:");
                    fgets(player1,MAX_NAME_LEN+1,stdin);
                }

                player2[strlen(player2)-1]='\0';



                if((rand()%2+1)== 1){
                    strcpy(p1,player1);
                    strcpy(p2,player2);
                }
                else{
                    strcpy(p1,player2);
                    strcpy(p2,player1);
                }



                play_game( p1, p2, scoreboard );

            }
            break;

            case 2:{
                display_scoreboard(scoreboard);
                }
            break;

            case 3:{
                reset_scoreboard(scoreboard);
            }
            break;

            case 4:
                exit(1);
            break;

        }
    }



    return EXIT_SUCCESS;
}

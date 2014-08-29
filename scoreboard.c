/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"

/* Req 2 -Initialises the scoreboard and sets all the strings to be
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
    int i;

    for(i=0; i<sizeof(scoreboard) ;i++){
        strcpy(scoreboard[i].won,"");
        strcpy(scoreboard[i].lost,"");
    }
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, struct result * latest_game)
{
    int i;

    for(i=sizeof(scoreboard); i>0;i++){
        if(strcmp(scoreboard[i].won,"")==0){
            scoreboard[i] = *latest_game;
            break;
        }
    }

}

/* Req 11 - Initialises the scoreboard and sets all the strings to be
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
    int i;

    for(i=0; i<sizeof(scoreboard) ;i++){
        strcpy(scoreboard[i].won,"");
        strcpy(scoreboard[i].lost,"");
    }

    printf("Scoreboard is reset.\n\n");

}

/* Req 10 - Displays a formatted printout of the last 10 winners and
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
    int i;

    printf("APT English Draughts Tournament - History of Games Played.\n");
    printf("==========================================================\n");
    printf("| Winner               | Loser                |\n");
    printf("| ---------------------| ---------------------|\n");


    for(i=sizeof(scoreboard); i>0; i--){

        printf("| %s", scoreboard[i].won);
        printf("| %s",scoreboard[i].lost);
        printf("\n");
    }

}


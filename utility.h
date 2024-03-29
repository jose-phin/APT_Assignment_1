/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef enum
{
    FALSE, TRUE
} BOOLEAN;

/*Clears residual data from stdin*/
void read_rest_of_line(void);
int check_if_correct_token(char * coordinates);
int find_coordinates(char *coordinates, unsigned *start_x,
        unsigned *start_y, unsigned *end_x, unsigned *end_y);
#endif



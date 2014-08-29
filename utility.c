/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "utility.h"

/* Tidy up residual data in stdin when encountering an error. You will
 * need to use this when there is a possibility that there will be
 * leftover characters in the input buffer. */
void read_rest_of_line(void)
{
    int ch;
    /* remove all characters from the buffer */
    while(ch = getc(stdin), ch!='\n' && ch!=EOF)
        ;
    /* clear the error status of the input pointer */
    clearerr(stdin);
}


int check_if_correct_token(char * coordinates){

    int bool=0;

    if(coordinates[3]!= '-'){
        bool=1;
    }else if(coordinates[1]!= ','){
        bool=1;
    }else if(coordinates[5]!= ','){
        bool=1;
    }

         return bool;
}



int find_coordinates(char *coordinates, unsigned *start_x,
    unsigned *start_y, unsigned *end_x, unsigned *end_y)
{
    int k;
    char *token1,*token2, *token3;
    char *part1, *part2;

    char *endPtr1,*endPtr2,*endPtr3,*endPtr4;

    int bool=0;

	token1 = strtok(coordinates,"-");
	for(k=0;k<2;k++){
		if(k==0){
            part1 = token1;
            token1 = strtok(NULL,"-");
		}
		else
			part2 = token1;
	}

	token2 = strtok(part1,",");
	for(k=0;k<2;k++){
		if(k==0){
			*start_x = strtol(token2, &endPtr1, 10);
			if (strcmp(endPtr1, "") != 0)
				bool = 1;
			else if (*start_x < 0 || *start_x > 7)
				bool =1;
			token2 = strtok(NULL,",");
		}
		else{
			*start_y = (int) strtol(token2, &endPtr2, 10);
			if (strcmp(endPtr2, "") != 0)
  				bool = 1;
			else if (*start_y < 0 || *start_y > 7)
				bool =1;
			}
	}

	token3= strtok(part2,",");
    for(k=0;k<2;k++){
        if(k==0){
            *end_x = (int) strtol(token3, &endPtr3, 10);
            if (strcmp(endPtr3, "") != 0)
                bool = 1;
            else if (*start_y < 0 || *start_y > 7)
                bool =1;
            token3 = strtok(NULL,",");
        }
        else{
            *end_y = (int) strtol(token3, &endPtr4, 10);
            if (strcmp(endPtr4, "") != 0)
                bool = 1;
            else if (*start_y < 0 || *start_y > 7)
                bool =1;
        }
    }

	return bool;

}


/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Josephine Pramudia
 * Student Number   : s3491523
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"
#define USER_INPUT 3

/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two,
    struct result * outcome)

{
    struct player player1;
    struct player player2;

    struct result latest_game;



    struct player *playing;
    enum cell_contents gameboard[BOARDWIDTH][BOARDHEIGHT];


    enum str_result player_turn_result;

    BOOLEAN play;

    strcpy(latest_game.won, " ");
    strcpy(latest_game.lost, " ");



    /*player1 details*/
    strcpy(player1.name,player_one);
    player1.col = P_RED;

    /*player2 details*/
    strcpy(player2.name,player_two);
    player2.col = P_WHITE;

    init_gameboard(gameboard);

    playing = &player2;

   do{
        display_gameboard(gameboard);

        if(playing->col == player1.col)
            playing = &player2;
        else
            playing = &player1;

        player_turn_result = player_turn(playing,gameboard);

		while(player_turn_result == SUCCESS){
            display_gameboard(gameboard);

	        if(playing->col == player1.col)
    	        playing = &player2;
    	    else
       		    playing = &player1;

            player_turn_result = player_turn(playing,gameboard);

		}

		 if(play==FALSE){
			printf("you finished the game");

			strcpy(latest_game.won, playing->name);

			if(playing->col == player1.col)
				strcpy(latest_game.lost, player2.name);
			else
				strcpy(latest_game.lost, player1.name);

			add_to_scoreboard(outcome, &latest_game);
			display_scoreboard(outcome);
			break;
		}

        play = test_for_winner(playing,gameboard);


    } while(play==TRUE);
}



/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current,
    enum cell_contents board[BOARDWIDTH][BOARDHEIGHT])
{

    char coordinates[MOVE_LEN],coordinates2[MOVE_LEN];
    char choice[USER_INPUT];

    enum str_result result = FAILURE;
    struct move new_move;

    unsigned previous_x = 0, previous_y = 0;
    unsigned start_x,start_y,end_x,end_y;
    enum move_type is_attack =INVALID;
    int real_num=1;



            do{
                printf("It is %s's turn. Please enter a valid move[press enter or ctrl-D to quit the current game]:",current->name);
                fgets(coordinates,MOVE_LEN+1,stdin);

                /*scanf("%s", coordinates);*/
                /*printf("YAYYYYYYY %s\n", coordinates);*/
                if(coordinates[strlen(coordinates)-1]!='\n') {
                    printf("string too long\n");
                    read_rest_of_line();
                    continue;
                }
                if (coordinates[3] != '-' || coordinates[1] != ',' || coordinates[5] != ',') {
                    printf("Invalid move\n");
                    continue;
                }
                printf("Do whatever for valid move\n");

                    real_num = find_coordinates(coordinates,&start_x,&start_y,&end_x,&end_y);

                    if(real_num!=1){
                        new_move.start.x = start_x;
                        new_move.start.y = start_x;
                        new_move.end.x = end_x;
                        new_move.end.y = end_y;

                        is_attack = update_board(current,board,new_move,&previous_x,&previous_y);
                        break;
                    }

            }while(1);

                    /*if player is attacking again*/
            if(is_attack == ATTACK){
                is_attack =update_board(current,board,new_move,&previous_x,&previous_y);
                display_gameboard(board);

                if(coordinates[strlen(coordinates)-1]!='\n')
                    read_rest_of_line();

                printf("You attacked! Would you like to attempt a further attack move\n");
                printf("with this token? [y for yes, n for no or press enter or ctrl-Z\n");
                printf("to quit the current game]:");
                fgets(choice,USER_INPUT,stdin);

                choice[strlen(choice)-1] = '\0';

                if(strcmp(choice,"y")==0){

                    /*validate input*/
                        do{
                            result = SUCCESS;
                            printf("%s. Please enter a attack move [n to cancel attack move]: ",current->name);
                            fgets(coordinates2,MOVE_LEN+1,stdin);
                            if(coordinates2[strlen(coordinates2)-1]!='\n')
                                read_rest_of_line();

                            if(check_if_correct_token(coordinates2)){

                                real_num = find_coordinates(coordinates2,&start_x,&start_y,&end_x,&end_y);

                                if(strcmp(coordinates2,"n")==0)
                                    break;

                                if(real_num!=1){
                                    new_move.start.x = start_x;
                                    new_move.start.y = start_x;
                                    new_move.end.x = end_x;
                                    new_move.end.y = end_y;

                                    if(new_move.start.x == previous_x && new_move.start.y == previous_y){
                                        is_attack = update_board(current,board,new_move,&previous_x,&previous_y);
                                        if(is_attack == ATTACK)
                                            break;
                                    }

                                }
                            }
                        }while(1);
                }
            }




    return result;
}


enum move_type update_board(struct player * current, enum cell_contents board[BOARDWIDTH][BOARDHEIGHT],
                   struct move new_move , unsigned *previous_x, unsigned *previous_y)
{

    int side, length;
    enum cell_contents peices=EMPTY;

    enum move_type returning =INVALID;

	if(current->col == P_RED){
		peices = RED;
		/* colouring the K_RED peices*/
		if(new_move.end.y == 7){
			board[new_move.start.y][new_move.start.x] = K_RED;
			peices = K_RED;
		}
		if( board[new_move.start.y][new_move.start.x] == K_RED){
			board[new_move.start.y][new_move.start.x] = K_RED;
			peices = K_RED;
		}
	}else{
		peices = WHITE;
		/* colouring the K_WHITE peices*/
		if(new_move.end.y == 0){
			board[new_move.start.y][new_move.start.x] = K_WHITE;
			peices = K_WHITE;
		}
		if( board[new_move.start.y][new_move.start.x] == K_WHITE){
			board[new_move.start.y][new_move.start.x] = K_WHITE;
			peices = K_WHITE;
		}
	}


	/*Normal moves */
	if(is_valid_move(new_move, current, board) == NORMAL){

		board[new_move.start.y][new_move.start.x] = EMPTY;
		board[new_move.end.y][new_move.end.x] = peices;

		*previous_x = new_move.end.x;
		*previous_y = new_move.end.y;

		returning = NORMAL;


	/*attacking moves*/
	}else if(is_valid_move(new_move, current, board) == ATTACK){

		side = new_move.end.x - new_move.start.x;
		if(side >0)
			side = new_move.start.x+1;
		else
			side = new_move.start.x-1;

		length = new_move.end.y - new_move.start.y;
		if(length >0)
			length = new_move.start.y+1;
		else
			length = new_move.start.y-1;

		board[new_move.start.y][new_move.start.x] = EMPTY;
		board[new_move.end.y][new_move.end.x] = peices;
		printf("you attacted\n");

		/*taking away white and moving red */
		if (board[new_move.end.y][new_move.end.x] == RED){
			board[new_move.end.y-1][side] = EMPTY;
			returning = ATTACK;
		}else if(board[new_move.end.y][new_move.end.x] == WHITE){
			board[new_move.end.y+1][side] = EMPTY;
			returning = ATTACK;
        }else{
			board[length][side] = EMPTY;
			returning = ATTACK;
        }

		*previous_x = new_move.end.x;
		*previous_y = new_move.end.y;


	}else if(is_valid_move(new_move, current, board) == INVALID){
		printf("Invalid input, re-enter valid move please\n");
		returning = INVALID;

	}

	return returning;
}


/* Requirement 4-Tests to see whether a move is valid or not- have to edit due to repetitions*/
enum move_type is_valid_move(struct move next_move,
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{

	int side, length;
    enum move_type isValid = INVALID;

	/*there is a peice in start.y, start.x*/
	if(board[next_move.start.y][next_move.start.x] != EMPTY){
		printf("\nnot empty\n");

		/*place peice is going to is empty*/
		if(board[next_move.end.y][next_move.end.x]== EMPTY){
			printf("\n end place empty\n");

			/*normal move*/
			if(next_move.end.x == (next_move.start.x+1) ||next_move.end.x == (next_move.start.x-1)){
				printf("\nnormal move\n");

				if(current->col == P_WHITE){
					if(board[next_move.start.y][next_move.start.x]==K_WHITE){
						if (next_move.end.y  == (next_move.start.y +1) ||
                                next_move.end.y  == (next_move.start.y -1)){
                			printf("\n king normal move white\n");
							isValid=NORMAL;
						}
					}else if(board[next_move.start.y][next_move.start.x]==WHITE){
						if (next_move.end.y  == (next_move.start.y -1)){
	                		printf("\n white normal move\n");
							isValid=NORMAL;
						}
					}
				}else if(current->col == P_RED){
					if(board[next_move.start.y][next_move.start.x]==K_RED){
						if (next_move.end.y  == (next_move.start.y +1) ||
                                next_move.end.y  == (next_move.start.y -1)){
                			printf("\n king normal move white\n");
							isValid=NORMAL;
                        }
					}else if(board[next_move.start.y][next_move.start.x]==RED){
						if (next_move.end.y  == (next_move.start.y +1)){
                			printf("\n red normal move\n");
							isValid=NORMAL;
						}
					}
				}

			/*attacking move*/
			}else if(next_move.end.x == (next_move.start.x+2) ||
                    next_move.end.x == (next_move.start.x-2)){
                        printf("\nattack req 1 sides\n");

				side = next_move.end.x - next_move.start.x;
				if(side >0)
					side = next_move.start.x+1;
				else
					side = next_move.start.x-1;

				length = next_move.end.y - next_move.start.y;
				if(length >0)
					length = next_move.start.y+1;
				else
					length = next_move.start.y-1;

				if(current->col == P_RED){
					if(board[next_move.start.y][next_move.start.x]==K_RED){
						if(board[length][side] == WHITE || board[length][side] == K_WHITE){
							printf("\nattacked white K\n");
							isValid = ATTACK;
						}
					}else if (board[next_move.start.y][next_move.start.x]==RED){
						if(board[next_move.end.y-1][side] == WHITE || board[next_move.end.y-1][side] == K_WHITE){
							printf("\nattacked white\n");
							isValid = ATTACK;
                        }
					}
				}else if(current->col == P_WHITE){
					if(board[next_move.start.y][next_move.start.x] == K_WHITE){
                        if(board[length][side] == RED || board[length][side] == K_RED ){
							printf("\nattacked red K\n");
							isValid = ATTACK;
						}
					}else if (board[next_move.start.y][next_move.start.x]==WHITE){
						if(board[next_move.end.y+1][side] == RED || board[next_move.end.y+1][side] == K_RED){
							printf("\nattacked red\n");
							isValid = ATTACK;
						}
					}
				}
			}
		}
	}


	if(isValid == INVALID)
   		 return INVALID;
    return isValid;
}



/* Requirement  - Tests whether the next player has any valid moves*/
BOOLEAN test_for_winner(struct player * next_player,
    enum cell_contents board[][BOARDWIDTH])
{
    int i,j;
    BOOLEAN has_moves = FALSE;

    for(i=0; i<BOARDHEIGHT; i++){
        for(j=0; i<BOARDWIDTH; i++){
            if(next_player->col == P_RED){
                if(board[i][j] == WHITE){
                    has_moves = TRUE;
                    break;
                }
            }
            else{
                if(board[i][j]==RED){
                    has_moves = TRUE;
                    break;
                }
            }
        }
    }
    return has_moves;
}

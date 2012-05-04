#include "smiley.h"

#include <stdio.h>
#include <stdlib.h>

/* Define Error Messages' Case */
#define WRONG_USAGE 		1
#define FILE_READ_ERROR 	2
#define FILE_FORMAT_ERROR	3
#define PICKED_EMPTY		4
#define BLOCKED				5
#define INVALID_INPUT		6

/* Define Characters on The Ouput Screen */
#define SMILEY_N	'N'
#define SMILEY_S	'S'
#define SMILEY_W	'W'
#define SMILEY_E	'E'

#define WALL		'='
#define NWALL		'.'

#define EAST		0
#define NORTH		1
#define WEST		2
#define SOUTH		3

#define DELAY_TIME	1

/* Global Variables */
int M=0, N=0; //size of the map
int **Map, **RWall, **CWall;

int PosR=0, PosC=0;
int Facing=EAST;

/* 
 * Function: setup()
 * Setup the map from the file entered via argv.
 */
void setup(int argc, char *argv[]){

	// Chekc weather the user enter the right command
	if(argc!=2){
		printErrorAndExit(WRONG_USAGE);
	}

	// Scan in the size of the map
	printf("Read file map from: %s\n",argv[1]);
	FILE *fin = fopen(argv[1],"r");
	if(fin == NULL)	printErrorAndExit(FILE_READ_ERROR);
	if(fscanf(fin,"%d%d", &M, &N)!=2)
		printErrorAndExit(FILE_FORMAT_ERROR);

	// Setup Smiley's starting position on the bottom-left
	setSmileyPos();

	// Setup the map and the wall array
	Map = malloc2DArray(M,N);
	RWall = malloc2DArray(M-1,N);
	CWall = malloc2DArray(M,N-1);

	// Scan in the whole map
	readMap(fin);
	readWalls(fin);

	// Print out the map for debugging
	printMap();
	printWalls();

	// Function end here
}

/* 
 * Function: readMap
 * Read the map from input file and store in Map array
 */
void readMap(FILE *fin){
	int i,j;
	printf("\nMap:\n");
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			if(fscanf(fin,"%d",&Map[i][j])!=1)
				printErrorAndExit(FILE_FORMAT_ERROR);
		}
	}
}


/*
 * Function: readWalls
 * Read the wall setting of this map and store in the RWall
 * ans CWall arrays
 */
void readWalls(FILE *fin){
	int i,j;

	//read RWall
	for(i=0;i<M-1;i++){
		for(j=0;j<N;j++){
			if(fscanf(fin,"%d",&RWall[i][j])!=1)
				printErrorAndExit(FILE_FORMAT_ERROR);
		}
	}

	//read CWall
	for(i=0;i<M;i++){
		for(j=0;j<N-1;j++){
			if(fscanf(fin,"%d",&CWall[i][j])!=1)
				printErrorAndExit(FILE_FORMAT_ERROR);
		}
	}
}

/*
 * Function: printErrorAndExit()
 * Print out the usage of this program depend on different
 * cases and exit the program immediately.
 */
void printErrorAndExit(int errorCase){
	
	//Fine the correspond error message
	printf("[ERROR]");
	switch(errorCase){
		case WRONG_USAGE:
			printf("Wrong Usage!\n");	break;
		case FILE_READ_ERROR:
			printf("File can't be read!\n");
			printf("Please enter a map file as program argument.\nFor example: ./Smiley map.txt\n");
			break;
		case FILE_FORMAT_ERROR:
			printf("File is not in a right format!\n");	break;
		case PICKED_EMPTY:
			printf("This spot is already empty.\n");	break;
		case BLOCKED:
			printf("The wall has blocked Smiley's way, he's died on the wall :(\n");	break;
		case INVALID_INPUT:
			printf("Wrong input.\n");	break;
	}

	//Exit the program immediately
	printf("Exit Program.\n");
	exit(1); }


/*
 * Function: malloc2DArray
 * Initialize a 2D array by given row and col.
 * Exception: More error checking can be added.
 */
int** malloc2DArray(int row, int col){

	int i;
	int **arr;

	arr = (int **)malloc(row * sizeof(int *));
	for(i=0;i<row;i++){
		arr[i] = malloc(col * sizeof(int));
	}

	return arr;
}

/*
 * Function: printMap
 * Print out the current map for debugging usage or for user.
 */
void printMap(){
	int i,j;

	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%d ", Map[i][j]);
		}
		printf("\n");
	}

}

/*
 * Function: printWalls
 * Print out the wall setting which is same as input file for
 * debugging.
 */
void printWalls(){
	int i,j;

	printf("\nWalls\n");

	//Row Wall print
	printf("\nRow Wall:\n");
	for(i=0;i<M-1;i++){
		for(j=0;j<N;j++){
			printf("%d ", RWall[i][j]);
		}
		printf("\n");
	}


	//Col Wall print
	printf("\nCol Wall:\n");
	for(i=0;i<M;i++){
		for(j=0;j<N-1;j++){
			printf("%d ", CWall[i][j]);
		}
		printf("\n");
	}

}

/*
 * Function: printMapAndWalls
 * Print out the real scene for Smiley's world including Walls and Flashes
 */
void printMapAndWalls(){
	int i,j;
	printf("\n");

	//print out the top wall
	printRowWall();

	//middle part
	char nextWall;
	for(i=0;i<M-1;i++){

		//place can be stood by Smiley
		printf("%c",WALL);
		for(j=0;j<N-1;j++){
			nextWall=(CWall[i][j])?WALL:NWALL;
			if(isSmileyHere(i,j)){
				printf("%c%c",smileyFacing(),nextWall);
				continue;
			}
			printf("%d%c",Map[i][j],nextWall);
		}
		if(isSmileyHere(i,j)){
			printf("%c%c\n",smileyFacing(),WALL);
		}
		else{
			printf("%d%c\n",Map[i][j],WALL);
		}

		//print a row of WALL or NWALL
		printf("%c",WALL);
		for(j=0;j<N;j++){
			nextWall=(RWall[i][j])?WALL:NWALL;
			printf("%c%c",nextWall,WALL);
		}
		printf("\n");

	}
	
	//place can be stood by Smiley(last row)
	printf("%c",WALL);
	for(j=0;j<N-1;j++){
		nextWall=(CWall[i][j])?WALL:NWALL;
		if(isSmileyHere(i,j)){
			printf("%c%c",smileyFacing(),nextWall);
			continue;
		}
		printf("%d%c",Map[i][j],nextWall);
	}
	if(isSmileyHere(i,j)){
		printf("%c%c\n",smileyFacing(),WALL);
	}
	else{
		printf("%d%c\n",Map[i][j],WALL);
	}


	//print out the bottom wall
	printRowWall();

	//print out other informations
	printf("\n");
	printf("Number of the flashed that is under Smiley's current position : %d\n", Map[PosR][PosC]);

	//puase for a while
	//this function seems doesn't work well
	//sleep(DELAY_TIME);
}


/*
 * Function: printRowWall
 * Print out a row of wall
 */
void printRowWall(){
	int i;
	for(i=0;i<2*N+1;i++){
		printf("%c",WALL);
	}
	printf("\n");
}


/*
 * Function: isSmileyHere
 * Check whether the Smiley is here or not.
 */
int isSmileyHere(int r, int c){
	return (r==PosR && c==PosC);
}


/*
 * Function: smileyFacing
 * This function return the char which can be displayed 
 * on the screen corresponding to Smiley's current facing
 * direction.
 */
char smileyFacing(){
	if(Facing == EAST)	return SMILEY_E;
	if(Facing == NORTH)	return SMILEY_N;
	if(Facing == WEST)	return SMILEY_W;
	return SMILEY_S;
}


/*
 * Function: setSmileyPos
 * Setup Smiley's starting position to the bottom-left of
 * the map.
 */
void setSmileyPos(){
	PosR = M-1;
	PosC = 0;
}

/*
 * Function: blocked
 * To determine whether it is blocked or not before actually 
 * move on.
 */
int blocked(){

	//blocked by the outer wall
	if(Facing == EAST	&& PosC==N-1)	return 1;
	if(Facing == WEST	&& PosC==0)		return 1;
	if(Facing == NORTH	&& PosR==0)		return 1;
	if(Facing == SOUTH	&& PosR==M-1)	return 1;

	//blocked by the inner wall
	if(Facing == EAST	&& CWall[PosR][PosC])	return 1;
	if(Facing == WEST	&& CWall[PosR][PosC-1])	return 1;
	if(Facing == NORTH	&& RWall[PosR-1][PosC])	return 1;
	if(Facing == SOUTH	&& RWall[PosR][PosC])	return 1;

	return 0;
}


/*
 * Function: move (Smiley's Basic Function)
 * Walk one step depending on the current direction.
 */
void move(){
	printf("[Smiley] move\n");

	if(blocked())	printErrorAndExit(BLOCKED);
	switch(Facing){
		case EAST:	PosC++;	break;
		case NORTH:	PosR--;	break;
		case WEST:	PosC--;	break;
		case SOUTH:	PosR++;	break;
	}
	//print out the current status
	printMapAndWalls();
}

/*
 * Function: turnLeft (Smiley's Basic Function)
 * Let Smiley turn left!
 */
void turnLeft(){
	printf("[Smiley] turnLeft\n");
	Facing++;
	Facing %= 4;
	printMapAndWalls();
}

/*
 * Function: putFlash
 * Smiley is really cool, he can put flashes on his current spot.
 */
void putFlash(){
	printf("[Smiley] putFlash\n");
	Map[PosR][PosC] ++;
	printMapAndWalls();
}

/*
 * Function: pickFlash
 * Smiley can also pick up the flashes on his current spot.
 * Isn't it cool?
 */
void pickFlash(){
	printf("[Smiley] pickFlash\n");
	if(Map[PosR][PosC]<=0)	printErrorAndExit(PICKED_EMPTY);
	Map[PosR][PosC] --;
	printMapAndWalls();
}


/*
 * Functions: selectRunMode
 * Let user to select the program mode. Return 1 is the user chose 
 * "run mode".
 */
int selectRunMode(){

	printf("There are two modes to select, please pick one.\n");
	printf("[1] Run the script in the code.\n");
	printf("[2] Run the interactive mode to control smiley.\n");
	printf(">> ");

	int select=0;
	if(scanf("%d",&select)!=1){
		printErrorAndExit(INVALID_INPUT);
	}

	return (select==1)?1:0;
}

/*
 * Functions: interactiveMode
 * Interactive Mode of Smiley Program. User are allowed to control
 * Smiley by entering mothed which on the list interactively.
 */
int interactiveMode(){
	//output information
	printf("Next step for Smiley:\n");
	printf("[1] move();\n");
	printf("[2] turnLeft();\n");
	printf("[3] putFlash();\n");
	printf("[4] pickFlash();\n");
	printf("[0] Exit Smiley.\n");

	//let user choose
	int select=0;
	printf(">> ");
	while(scanf("%d",&select)!=1){
		printf("Invalid input, please try again.\n");
	}

	switch(select){
		case 1:
			move();	break;
		case 2:
			turnLeft();	break;
		case 3:
			putFlash();	break;
		case 4:
			pickFlash();	break;
		case 0:
			return 0;
			break;
		default:
			printf("Invalid input, please try agin.\n");
			interactiveMode();
	}
	return 1;
}

/*
 * Function: endProgram
 * End Program.
 */
void endProgram(){
	printf("Thank you for playing with Smiley :)\tGoodbye!\n");
}


//end

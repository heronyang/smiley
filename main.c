#include <stdio.h>
#include "smiley.h"

void run(); // the main part for user to control Smiley

/*
 * main
 */
int main(int argc, char** argv){

	setup(argc, argv);
	printMapAndWalls();

	if(selectRunMode()){
		//run script mode
		run();
	}else{
		//run interactive mode
		while(interactiveMode()){
		}
	}

	endProgram();

	return 0;
}

/* 
 * Function: run
 * Write your Smiley script here, and enjoy it!
 * Only use the Smiley Functions.
 */
void run(){
	move();
	turnLeft();
}


// end

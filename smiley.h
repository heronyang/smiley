/*
 * Program Name: Smiley
 *
 * Author : Heron Yang
 * Instructor: 
 *
 * Description:
 * This is a class project for "Introduce to Computer
 * Science and Programming Language" at NCTU.
 *
 */

/* Main Functions */
void setup();

/* Four Basic Smiley Function */
void move();
void turnLeft();
void putFlash();
void pickFlash();

/* Smiley Addition Function */
int frontIsClear();
int frontIsBlocked();
int leftIsClear();
int leftIsBlocked();
int rightIsClear();
int rightIsBlocked();

int flashPresent();
int noFlashPresent();
int flashInBag();
int noFlashInBag();

int facingNorth();
int facingEast();
int facingSouth();
int facingWest();

int notFacingNorth();
int notFacingEast();
int notFacingSouth();
int notFacingWest();

/* Output Functions */
void printMap();
void printWalls();
void printMapAndWalls();

void printRowWall();

/* Smiley Related Functions */
char smileyFacing();
int isSmileyHere();
void setSmileyPos();

/* Other Functions */
void printErrorAndExit();
void readMap();
void readWalls();
void endProgram();
int blocked();
int selectRunMode();
int interactiveMode();
int** malloc2DArray();

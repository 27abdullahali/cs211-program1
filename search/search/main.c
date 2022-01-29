
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define NROWS 11
#define NCOLS 11
#define START_R (NROWS/2)
#define START_C (NCOLS/2)


#define NORTH 'n'
#define SOUTH 's'
#define EAST  'e'
#define WEST  'w'
#define QUIT  'q'
#define BLANK 'b'
#define ERROR 'r'

/**
 * starter code for the 'search' program/game.
 *
 * The given code takes care of two of the tasks in the program:
 *
 *      - reading and interpreting a user command via the read_cmd
 *          function.  Read the banner comment and examine the example
 *          usage of the function in main for details.
 *
 *      - handling optional command line arguments which allow a
 *          the user (tester) to specify explicitly the location of
 *          the pot-o-gold instead of that location being randomized
 *          as in the default mode.
 *
 */

/**
 * func:  read_cmd
 * desc:  (attempts to) read a single line from standard input, and
 *          returns one of the following:
 *
 *          NORTH : if the first non-whitespace character is either
 *                  'n' or 'N'
 *          SOUTH : if the first non-whitespace character is either
 *                  's' or 'S'
 *          EAST  : if the first non-whitespace character is either
 *                  'e' or 'E'
 *          WEST  : if the first non-whitespace character is either
 *                  'w' or 'W'
 *          QUIT  : if the first non-whitespace character is either
 *                  'q' or 'Q' OR an input line cannot be read (this
 *                  happens if EOF is read terminating the input; from
 *                  the terminal, this happens if the user types ctrl-D
 *                  (in UNIX at least))
 *          BLANK : if the user entered a blank/empty line
 *          ERROR : if the user entered an invalid command
 *
 */
//------------------------------------------------------------------
int getRandSpot() {
    int random = 0;
    random = rand() % 120;
    printf("random number: %i\n", random);
    if (random == 60) {
        getRandSpot();
    }
    return random;
}
//------------------------------------------------------------------
char read_cmd() {

    char buf[128];

    // this happens when fgets reads 'EOF'.  This happens
    //   when the user types CTRL-D
    if(fgets(buf, 128, stdin) == NULL)
        return 'q';

    int n = strlen(buf);

    int i=0;

    while(i<n && isspace(buf[i]))
        i++;

    if(i==n)
        return BLANK;  // entire line is whitespace (incl newline)
    char c = buf[i];

    switch(c) {
        case 'n':
        case 'N': return NORTH;
        case 's':
        case 'S': return SOUTH;
        case 'e':
        case 'E': return EAST;
        case 'w':
        case 'W': return WEST;
        case 'q':
        case 'Q': return QUIT;
        default:
                  return ERROR;

    }
}
//------------------------------------------------------------------
int getRow(int position) {
    return (position / 11);
}
//------------------------------------------------------------------
int getCol(int position) {
    return (position - (getRow(position) * 11));
}
//------------------------------------------------------------------
/**
 * func: inrange
 * desc: simple predicate function determining whether a
 *          given coordinate (r,c) is within the boundaries
 *          of the "board" (if yes, returns true; if no,
 *          returns false).
 */
int inrange(int r, int c) {
    if(r < 0 || c < 0 || r >= NROWS || c >= NCOLS)
        return 0;
    else
        return 1;
}
//------------------------------------------------------------------
void makeMove(int row, int col, int *currPosition, int *numMoves, int nextSpot) {
    if (inrange(row, col)) {
        *currPosition = nextSpot;
        *numMoves = *numMoves + 1;
    }
    else {
        printf("  OUCH!");
        *numMoves = *numMoves + 1;
    }
}
//------------------------------------------------------------------
void moveNorth(int *currPosition, int *numMoves) {
    int nextSpot = *currPosition - 11;
    int row = getRow(nextSpot);
    int col = getCol(nextSpot);
    
    makeMove(row, col, currPosition, numMoves, nextSpot);
}
//------------------------------------------------------------------
void moveEast(int *currPosition, int *numMoves) {
    int row;
    int col;
    int nextSpot = *currPosition + 1;
    
    if( (nextSpot % 11) == 0) {
        row = -1;
        col = -1;
    }
    else {
        row = getRow(nextSpot);
        col = getCol(nextSpot);
    }
    makeMove(row, col, currPosition, numMoves, nextSpot);
}
//------------------------------------------------------------------
void moveSouth(int *currPosition, int *numMoves) {
    int nextSpot = *currPosition + 11;
    int row = getRow(nextSpot);
    int col = getCol(nextSpot);

    makeMove(row, col, currPosition, numMoves, nextSpot);
}
//------------------------------------------------------------------
void moveWest(int *currPosition, int *numMoves) {
    int row;
    int col;
    int nextSpot = *currPosition - 1;
    
    if( (nextSpot % 11) == 0) {
        row = -1;
        col = -1;
    }
    else {
        row = getRow(nextSpot);
        col = getCol(nextSpot);
    }
    makeMove(row, col, currPosition, numMoves, nextSpot);
}
//------------------------------------------------------------------
void hotOrCold(int goldRow, int goldCol, int oldPosition, int currPosition) {
    int oldDist = abs(goldRow - getRow(oldPosition)) + abs(goldCol - getCol(oldPosition));
    int currDist = abs(goldRow - getRow(currPosition)) + abs(goldCol - getCol(currPosition));
    
    if (currDist < oldDist) {
        printf("  GETTING WARMER!\n");
    }
    else {
        printf("  GETTING COLDER!\n");
    }
}
//------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int g_row, g_col;
    int randomize = 1;
    int randSpot;
    int currPosition = 60;
    int oldPosition;
    int numMoves = 0;
    srand(time(NULL));
    
    for(int i=0; i<argc; i++) {
        printf(" argv[%i] : '%s'\n", i, argv[i]);
    }
    if(argc == 3){
        int r1 = sscanf(argv[1], "%i", &g_row);  // row coord of gold
        int r2 = sscanf(argv[2], "%i", &g_col);  // row coord of gold
        if(r1==0 || r2==0 || !inrange(g_row, g_col) ||
                (g_row == START_R && g_col == START_C))
            printf("bad cmd-line args: using random location for gold\n");
        else
            randomize = 0;
    }
    else if(argc != 1)
            printf("bad cmd-line args: using random location for gold\n");
     
    if(randomize) {
        randSpot = getRandSpot();
        g_row = getRow(randSpot);
        g_col = getCol(randSpot);
    }
    
    

    //printf(stderr, "pot-o-gold location: (%i, %i)\n", g_row, g_col);

    int done = 0;

    // demo loop...
    while(!done) {
        printf("Direction: ");
        char c = read_cmd();
        oldPosition = currPosition;
        
        if (c == 'n') {
            moveNorth(&currPosition, &numMoves);
        }
        else if (c == 'e') {
            moveEast(&currPosition, &numMoves);
        }
        else if (c == 's') {
            moveSouth(&currPosition, &numMoves);
        }
        else if (c == 'w') {
            moveWest(&currPosition, &numMoves);
        }
        else if(c=='q') {
            done = 1;
        }
        else {
            printf("  Invalid input. Try again.\n");
            continue;
        }
        
        if ( (getRow(currPosition) == g_row) && (getCol(currPosition) == g_col) ) {
            printf("  HOORAY!");
            break;
        }
        else if(currPosition != oldPosition) {
            hotOrCold(g_row, g_col, oldPosition, currPosition);
        }
    }
    printf("\n\nTotal Moves: %i\nGoodbye!\n", numMoves);
    
    return 0;
    
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>

#define ROWS 15
#define COLS 15
#define OFF 0
#define ON 1

short number_of_neighbours(char ptarr[], short index);
void update_board(char ptarr[]);
void print_board(char ptarr[]);

int main(int argc, char* argv[]) {
    char board[ROWS * COLS];
    short num_neighbours;
    short generator;

    srand(time(NULL));
    memset((void*)board, OFF, ROWS*COLS); /* Set each cell to OFF. */
    print_board(board);
    for (short i = 0; i < (ROWS * COLS); i++) {
        generator = (short)rand() % 3;
        if (generator == 0)
            board[i] = ON;
    }
    printf("\n\n\n");
    print_board(board);
    for (short i = 0; i < 5; i++) {
        SDL_Delay(6000);
        update_board(board);
        print_board(board);
        printf("\n\n\n");
    }
    return EXIT_SUCCESS;
}

short number_of_neighbours(char ptarr[], short index) {
    short num_adj = 0;
    
    if (index < 0 || index > (ROWS * COLS))
        return -1;
    if (index - ROWS >= 0) {
        if (ptarr[index - ROWS] == ON) {
            num_adj++;
            printf("Found block on above index %d.\n", index);
        }
    }
    if (index + ROWS <= (ROWS * COLS)) {
        if (ptarr[index + ROWS] == ON) {
            num_adj++;
            printf("Found block on right of index %d.\n", index);
        }
    }
    if (index - 1 >= 0) {
        if (ptarr[index - 1] == ON) {
            num_adj++;
            printf("Found block on left of index %d.\n", index);
        }
    }
    if (index + 1 <= ROWS) {
        if (ptarr[index + 1] == ON) {
            num_adj++;
            printf("Found block on below index %d.\n", index);
        }
    }
    return num_adj;
}

void update_board(char ptarr[]) {
    short num_neighbours;

    for (int i = 0; i < (ROWS * COLS); i++) {
        num_neighbours = number_of_neighbours(ptarr, i);
        if (num_neighbours < 2 && ptarr[i] == ON) {
            ptarr[i] = OFF; /* Cell dies by underpopulation. */
            printf("Cell at index (%d, %d) dies.\n", (i / ROWS), (COLS - i));
        }
        else if (num_neighbours > 3 && ptarr[i] == ON) {
            ptarr[i] = OFF; /* Cell dies by overpopulation. */
            printf("Cell at index (%d, %d) dies.\n", (i / ROWS), (COLS - i));
        }
        else if (num_neighbours == 3 && ptarr[i] == OFF) {
            ptarr[i] = ON; /* Cell becomes alive by reproduction. */
            printf("Cell at index (%d, %d) becomes alive.\n", (i / ROWS), (COLS -i));
        }
        else if ((num_neighbours == 2 && ptarr[i] == ON) ||
                 (num_neighbours == 3 && ptarr[i] == ON)) {
            ptarr[i] = ON;
            printf("Cell at index (%d, %d) gets to live.\n", (i / ROWS), (COLS - i));
        }
    }
}

void print_board(char ptarr[]) {
    printf("|");
    for (short i = 0; i < (ROWS * COLS); i++) {
        if (ptarr[i] == ON)
            printf("X");
        else
            printf(" ");
        printf("|");
        if ((i % ROWS) == (COLS - 1))
            printf("\n|");
        /*else if ((i % ROWS) == 0)
            printf("|"); */
    }
}

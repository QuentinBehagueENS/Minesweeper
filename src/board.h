/**********************************************************************************************
 *                             Management of the 2048 board
 **********************************************************************************************/
#ifndef BOARD_H
#define BOARD_H

//________________________________________________________________________/ INCLUDES :
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

//________________________________________________________________________/ GLOBAL VARIABLES :
#define HEIGHT 4
#define WIDTH 4
#define PROBABILITY2 0.9
#define PROBABILITY4 0.1
#define MAX_UINT4 0b1111



//________________________________________________________________________/ MACROS :
#define IS_FILLED(b) (b->size == HEIGHT*WIDTH)
#define GET_RAND_INT(a, b) (rand()%(b-a) + a)
#define GET_RAND_FLOAT ((float)rand()/(float)RAND_MAX)
#define GET_2o4 (GET_RAND_FLOAT < PROBABILITY2 ? 1 : 2)
#define IS_EMPTY(b, i) (get(b, i) == 0)
#define TEST(condition) do {                                                    \
    if (!(condition)) {                                                         \
        fprintf(stderr, "Test failed (%s) - Line %d\n", #condition, __LINE__);  \
        exit(EXIT_FAILURE);                                                     \
    }                                                                           \
} while(0)

//________________________________________________________________________/ STRUCTURES :
typedef unsigned long long bitboard;
typedef struct {uint64_t bitboard; int value; int nb_free;} board;
typedef enum {UP, RIGHT, DOWN, LEFT,  __NB_OPERATION__} operation;

board* init_board();

int get(board* b, int index);

void set(board* b, int index, int value);

void display_board(board* b);

int random_free_square(board* b);

board* random_initial_board();

void swap(board* b, int i, int j);

bool is_empty_or_equal(board* b, int i, int value);

bool play_move(board* b, operation move);

#endif
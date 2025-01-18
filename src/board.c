#include "board.h"

board* init_board(){
    board* b = (board*)malloc(sizeof(board));
    b->bitboard = 0ULL;
    b->value = 0;
    b->nb_free = WIDTH*HEIGHT;
    return b;
}

int get(board* b, int index) {
    TEST(index >= 0 && index < HEIGHT * WIDTH);
    return (b->bitboard >> (index * 4)) & 0xF;
}

void set(board* b, int index, int value) {
    TEST(index >= 0 && index < HEIGHT * WIDTH && value <= MAX_UINT4);
    int old_value = (b->bitboard >> (index * 4)) & 0xF;
    if (old_value == 0 && value != 0){b->nb_free--;} 
    else if (old_value != 0 && value == 0) {b->nb_free++;}
    b->value += (value - old_value);
    b->bitboard &= ~(0xFULL << (index * 4));
    b->bitboard |= ((uint64_t)value << (index * 4));
}

void display_board(board* b){
    printf("\n>>> Content :    ");                        
    for(int i = HEIGHT - 1; i >= 0; i--){
        if(i != HEIGHT - 1) printf("                 ");
        for(int j = WIDTH - 1; j >= 0; j--){
            printf("|%2d", get(b, i*WIDTH+ j));
        }
        printf("|\n");
    }
    printf(">>> Evaluation : %d\n", b->value);
    printf(">>> Empty square : %d out of 16\n", b->nb_free);
}

int random_free_square(board* b){
    int index = GET_RAND_INT(0, b->nb_free);
    int count = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (((b->bitboard >> (i * 4)) & 0xFULL) == 0) {
            if (count == index) return i;
            count++;
        }
    }
    TEST(0);
    return -1;
}

board* random_initial_board(){
    board* b = init_board();
    int square1 = GET_2o4;
    int square2 = GET_2o4;
    set(b, GET_RAND_INT(0, WIDTH*HEIGHT), square1);
    set(b, random_free_square(b), square2);
    return b;
}

void swap(board* b, int i, int j){
    TEST(i >= 0 && i < HEIGHT * WIDTH && j >= 0 && j < HEIGHT * WIDTH);
    int i_value = get(b, i);
    int j_value = get(b, j);
    b->bitboard &= ~(0xFULL << (i * 4));
    b->bitboard |= ((uint64_t)j_value << (i * 4));
    b->bitboard &= ~(0xFULL << (j * 4));
    b->bitboard |= ((uint64_t)i_value << (j * 4));
}

bool is_empty(board* b, int i){
    return get(b, i) == 0;
}

bool play_move(board* b, operation move) {
    bool modified = false;
    switch (move) {
        case LEFT:
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 1; j < WIDTH; j++) {
                    int value = get(b, i * WIDTH + j);
                    if (value != 0) {
                        for (int k = j; k > 0; k--) {
                            if (is_empty(b, i * WIDTH + k - 1)) {
                                swap(b, i * WIDTH + k, i * WIDTH + k - 1);
                                modified = true;
                            } else if (get(b, i * WIDTH + k - 1) == value) {
                                set(b, i * WIDTH + k - 1, value + 1);
                                set(b, i * WIDTH + k, 0);
                                modified = true;
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case RIGHT:
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = WIDTH - 2; j >= 0; j--) {
                    int value = get(b, i * WIDTH + j);
                    if (value != 0) {
                        for (int k = j; k < WIDTH - 1; k++) {
                            if (is_empty(b, i * WIDTH + k + 1)) {
                                swap(b, i * WIDTH + k, i * WIDTH + k + 1);
                                modified = true;
                            } else if (get(b, i * WIDTH + k + 1) == value) {
                                set(b, i * WIDTH + k + 1, value + 1);
                                set(b, i * WIDTH + k, 0);
                                modified = true;
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case UP:
            for (int i = 1; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    int value = get(b, i * WIDTH + j);
                    if (value != 0) {
                        for (int k = i; k > 0; k--) {
                            if (is_empty(b, (k - 1) * WIDTH + j)) {
                                swap(b, k * WIDTH + j, (k - 1) * WIDTH + j);
                                modified = true;
                            } else if (get(b, (k - 1) * WIDTH + j) == value) {
                                set(b, (k - 1) * WIDTH + j, value + 1);
                                set(b, k * WIDTH + j, 0);
                                modified = true;
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case DOWN:
            for (int i = HEIGHT - 2; i >= 0; i--) {
                for (int j = 0; j < WIDTH; j++) {
                    int value = get(b, i * WIDTH + j);
                    if (value != 0) {
                        for (int k = i; k < HEIGHT - 1; k++) {
                            if (is_empty(b, (k + 1) * WIDTH + j)) {
                                swap(b, k * WIDTH + j, (k + 1) * WIDTH + j);
                                modified = true;
                            } else if (get(b, (k + 1) * WIDTH + j) == value) {
                                set(b, (k + 1) * WIDTH + j, value + 1);
                                set(b, k * WIDTH + j, 0);
                                modified = true;
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;

        default:
            TEST(0);
    }
    if(modified){set(b, random_free_square(b), GET_2o4);}
    return modified;
}

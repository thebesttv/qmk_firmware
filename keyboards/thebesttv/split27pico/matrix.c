#include "quantum.h"
#include "spi_master.h"
#include "matrix.h"

#include "split_common/split_util.h"
#include "split_common/transactions.h"

#ifndef SPLIT_KEYBOARD
#    error "not a split keyboard"
#endif

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

void matrix_init_custom(void) {
    // pin_t slavePin = GP5;
    // bool lsbFirst = true;
    // uint8_t mode = 1;
    // uint16_t divisor = 10;
    // spi_init();
    // spi_start(slavePin, lsbFirst, mode, divisor);
}

void readLocalKeyState(int n, uint8_t layout_map[][2], matrix_row_t result_matrix[]) {
    // writePinLow(PL);
    // wait_us(DELAY);

    // writePinHigh(PL);
    // wait_us(DELAY);

    // writePinLow(CE);

    // for (int i = 0; i < n; i++) {
    //     writePinHigh(CLK);
    //     wait_us(DELAY);

    //     if (readPin(MOUT) == PAL_LOW) {
    //         uint8_t row = layout_map[i][0];
    //         uint8_t col = layout_map[i][1];
    //         result_matrix[row] |= MATRIX_ROW_SHIFTER << col;
    //     }

    //     writePinLow(CLK);
    //     wait_us(DELAY);
    // }
    // writePinHigh(CE);
}

#define NUM 31

uint8_t LAYOUT_MAP_L[NUM][2] = {
    { 4,  3}, { 4,  4}, { 4,  5},           //  0  1  2 (thumb)
    { 3,  5}, { 2,  5}, { 1,  5}, { 0,  5}, //  3  4  5  6
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, //  7  8  9 10
    { 0,  4}, { 1,  4}, { 2,  4}, { 3,  4}, // 11 12 13 14
    { 3,  3}, { 2,  3}, { 1,  3}, { 0,  3}, // 15 16 17 18
    { 0,  2}, { 1,  2}, { 2,  2}, { 3,  2}, // 19 20 21 22
    { 3,  1}, { 2,  1}, { 1,  1}, { 0,  1}, // 23 24 25 26
    { 0,  0}, { 1,  0}, { 2,  0}, { 3,  0}  // 27 28 29 30
};

uint8_t LAYOUT_MAP_R[NUM][2] = {
    { 4,  2}, { 4,  1}, { 4,  0},           //  0  1  2 (thumb)
    { 3,  0}, { 2,  0}, { 1,  0}, { 0,  0}, //  3  4  5  6
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, //  7  8  9 10
    { 0,  1}, { 1,  1}, { 2,  1}, { 3,  1}, // 11 12 13 14
    { 3,  2}, { 2,  2}, { 1,  2}, { 0,  2}, // 15 16 17 18
    { 0,  3}, { 1,  3}, { 2,  3}, { 3,  3}, // 19 20 21 22
    { 3,  4}, { 2,  4}, { 1,  4}, { 0,  4}, // 23 24 25 26
    { 0,  5}, { 1,  5}, { 2,  5}, { 3,  5}  // 27 28 29 30
};

bool matrix_scan_custom(matrix_row_t raw_matrix[]) {
    // matrix_row_t current_matrix[MATRIX_ROWS] = {0};

    // readLocalKeyState(NUM, isLeftHand ? LAYOUT_MAP_L : LAYOUT_MAP_R, current_matrix);

    // bool changed = memcmp(raw_matrix, current_matrix, sizeof(current_matrix)) != 0;
    // if (changed) memcpy(raw_matrix, current_matrix, sizeof(current_matrix));

    // if (changed)
    //     println("!matrix changed");

    // return changed;
    return false;
}

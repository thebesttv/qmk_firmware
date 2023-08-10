#include "quantum.h"
#include "spi_master.h"
#include "matrix.h"

#include "split_common/split_util.h"

#ifndef SPLIT_KEYBOARD
#    error "not a split keyboard"
#endif

void matrix_init_custom(void) {
    pin_t slavePin = GP5;
    bool lsbFirst = false;
    uint8_t mode = 1;
    uint16_t divisor = 10;
    spi_init();
    spi_start(slavePin, lsbFirst, mode, divisor);
}

#define PL GP5
#define CE GP6
#define CLK GP2
#define MOUT GP4

#define DELAY 1

#define NUM 31
#define NUM_8 4

void readLocalKeyState(uint8_t layout_map[][2], matrix_row_t result_matrix[]) {
    writePinLow(PL);
    wait_us(DELAY);

    writePinHigh(PL);
    wait_us(DELAY);

    writePinLow(CE);

    static uint8_t data[NUM_8];
    spi_receive(data, 4);

    uint8_t *p = data;
    for (int i = 0; i < NUM;) {
        uint8_t x = *p++;
        for (int j = 0; j < 8 && i < NUM; i++, j++) {
            uint8_t currentBit = x & (1 << (7 - j));
            if (currentBit == 0) {
                uint8_t row = layout_map[i][0];
                uint8_t col = layout_map[i][1];
                result_matrix[row] |= MATRIX_ROW_SHIFTER << col;
            }
        }
    }

    writePinHigh(CE);
}

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
    matrix_row_t current_matrix[MATRIX_ROWS] = {0};

    readLocalKeyState(isLeftHand ? LAYOUT_MAP_L : LAYOUT_MAP_R, current_matrix);

    bool changed = memcmp(raw_matrix, current_matrix, sizeof(current_matrix)) != 0;
    if (changed) memcpy(raw_matrix, current_matrix, sizeof(current_matrix));

    return changed;
}

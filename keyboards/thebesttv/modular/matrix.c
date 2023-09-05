#include "quantum.h"
#include "spi_master.h"
#include "matrix.h"

#include "split_common/split_util.h"

#ifndef SPLIT_KEYBOARD
#    error "not a split keyboard"
#endif

#define PL GP5
#define CE GP6
#define CLK GP2
#define MOUT GP4

void matrix_init_custom(void) {
    pin_t slavePin = GP5;
    bool lsbFirst = false;
    uint8_t mode = 1;
    uint16_t divisor = 10;
    spi_init();
    spi_start(slavePin, lsbFirst, mode, divisor);

    setPinOutput(PL);
    setPinOutput(CE);
}

#define NUM 40
#define NUM_8 5

void readLocalKeyState(uint8_t layout_map[][2], matrix_row_t result_matrix[]) {
    static uint8_t data[NUM_8];

    writePinLow(PL);

    writePinHigh(PL);

    writePinLow(CE);

    spi_receive(data, NUM_8);

    uint8_t *p = data;
    for (uint8_t i = 0; i < NUM;) {
        uint8_t x = *p++;
        for (uint8_t j = 0; j < 8 && i < NUM; i++, j++) {
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

uint8_t LAYOUT_MAP[NUM][2] = {
    {-1, -1}, //  0
    {-1, -1}, //  1
    {-1, -1}, //  2
    {-1, -1}, //  3

    { 0,  6}, //  4
    { 1,  6}, //  5
    { 2,  6}, //  6

    { 0,  5}, //  7
    { 1,  5}, //  8
    { 2,  5}, //  9
    { 3,  5}, // 10

    { 0,  4}, // 11
    { 1,  4}, // 12
    { 2,  4}, // 13
    { 3,  4}, // 14

    { 0,  3}, // 15
    { 1,  3}, // 16
    { 2,  3}, // 17
    { 3,  3}, // 18

    { 0,  2}, // 19
    { 1,  2}, // 20
    { 2,  2}, // 21
    { 3,  2}, // 22

    { 0,  1}, // 23
    { 1,  1}, // 24
    { 2,  1}, // 25
    { 3,  1}, // 26

    { 0,  0}, // 27
    { 1,  0}, // 28
    { 2,  0}, // 29
    { 3,  0}, // 30

    {-1, -1}, // 31
    {-1, -1}, // 32

    { 4,  2}, // 33
    { 4,  3}, // 34
    { 4,  5}, // 35
    { 4,  4}, // 36
    { 4,  1}, // 37
    { 4,  0}, // 38

    {-1, -1} // 39
};

bool matrix_scan_custom(matrix_row_t raw_matrix[]) {
    matrix_row_t current_matrix[MATRIX_ROWS] = {0};

    readLocalKeyState(LAYOUT_MAP, current_matrix);

    bool changed = memcmp(raw_matrix, current_matrix, sizeof(current_matrix)) != 0;
    if (changed) memcpy(raw_matrix, current_matrix, sizeof(current_matrix));

    return changed;
}

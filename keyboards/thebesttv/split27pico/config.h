// Copyright 2023 thebesttv (@thebesttv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 10
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS 6

#define MATRIX_ONBOARD_ROW_PINS { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0 }

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define MASTER_LEFT // usb cable always connects to the left

#define SERIAL_USART_DRIVER SIOD0
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0     // USART TX pin
#define SERIAL_USART_RX_PIN GP1     // USART RX pin

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN  GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

#define I2C_DRIVER   I2CD0
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13

// pressing both left & right shift turns on caps word feature
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

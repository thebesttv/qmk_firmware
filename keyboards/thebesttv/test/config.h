// Copyright 2023 thebesttv (@thebesttv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_DRIVER SIOD0
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0     // USART TX pin
#define SERIAL_USART_RX_PIN GP1     // USART RX pin

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN  GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

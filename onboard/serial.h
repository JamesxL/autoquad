/*
    This file is part of AutoQuad.

    AutoQuad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AutoQuad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with AutoQuad.  If not, see <http://www.gnu.org/licenses/>.

    Copyright © 2011, 2012  Bill Nesbitt
*/

#ifndef _serial_h
#define _serial_h

#include "stm32f4xx.h"
#include <CoOS.h>

#define SERIAL_DEFAULT_BUFSIZE	128

typedef struct {
    unsigned int baudRate;
    unsigned int flowControl;

    unsigned int txBufSize;
    volatile unsigned char *txBuf;
    volatile unsigned int txHead, txTail;

    unsigned int rxBufSize;
    volatile unsigned char *rxBuf;
    volatile unsigned int rxHead, rxTail;
    volatile unsigned int rxPos;

    USART_TypeDef *USARTx;
    DMA_Stream_TypeDef *rxDMAStream;
    DMA_Stream_TypeDef *txDMAStream;
    uint32_t rxDMAChannel;
    uint32_t txDMAChannel;
    uint32_t rxDmaFlags, txDmaFlags;
    volatile unsigned char txDmaRunning;

    OS_FlagID waitFlag;
} serialPort_t;

extern serialPort_t *serialOpen(USART_TypeDef *USARTx, unsigned int baud, unsigned int flowControl, unsigned int rxBufSize, unsigned int txBufSize);
extern void serialChangeBaud(serialPort_t *s, unsigned int baud);
extern void serialSetSTDIO(serialPort_t *s);
extern void serialWrite(serialPort_t *s, unsigned char ch);
extern void serialWatch(void);
extern unsigned char serialAvailable(serialPort_t *s);
extern int serialRead(serialPort_t *s);
extern void serialPrint(serialPort_t *s, const char *str);
extern int __putchar(int ch);
extern int __getchar(void);

extern serialPort_t *serialSTDIO;

#endif
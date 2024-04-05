/*
    2023.04.17
    Keil / Options for Target / Code Generation - Use MicroLIB == ON
*/

#ifndef _PRINTF_UART_H
#define _PRINTF_UART_H

#include "usart.h"
#include "stdio.h"

int fputc(int ch, FILE *f);

#endif

/*******************************************************************************
  * @file    uart.h
  * @author  shilov.av@gmail.com  
  * @version V1.0
  * @date    15/09/2015
  * @brief   uart
  *****************************************************************************/

#ifndef _UART_H_
#define _UART_H_

// инициализация UART
void UartInit(void);

// Отправляем данные по UART
void  UartTransmite(unsigned char *data, unsigned char count);

// Вызываем эту функцию при приеме данных
unsigned char UartRecive(unsigned char *data);
//  готовность принятых данных 
unsigned char  UartComplete(void);

#endif /* #define _ANALOG_H_  */
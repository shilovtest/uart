/*******************************************************************************
  * @file    uart.h
  * @author  shilov.av@gmail.com  
  * @version V1.0
  * @date    15/09/2015
  * @brief   uart
  *****************************************************************************/

#ifndef _UART_H_
#define _UART_H_

// ������������� UART
void UartInit(void);

// ���������� ������ �� UART
void  UartTransmite(unsigned char *data, unsigned char count);

// �������� ��� ������� ��� ������ ������
unsigned char UartRecive(unsigned char *data);
//  ���������� �������� ������ 
unsigned char  UartComplete(void);

#endif /* #define _ANALOG_H_  */
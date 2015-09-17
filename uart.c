/*******************************************************************************
  * @file    uart.c
  * @author  shilov.av@gmail.com  
  * @version V1.0
  * @date    15/09/2015
  * @brief   uart
  *****************************************************************************/




#include "htc.h"



#define _sizeBufferUart  64
unsigned char UartReciveBuffer[_sizeBufferUart];
unsigned char UartTransmiteBuffer[_sizeBufferUart];

unsigned char UartTransmiteIndex;  //индекс текущего отправляемого байта
unsigned char UartTransmiteCount;  //всего сколько отправлено байт

unsigned char UartReciveIndex;     //индекс текущего принимаемого байта
unsigned char UartReciveTimeOut;       //тайм аут приема 

unsigned char UartReciveComplete=0;     //флаг готовности приема


// инициализация UART
void UartInit(void)
{
T0CON=0;
T0CONbits.T08BIT=1;
T0CONbits.TMR0ON=1;

TMR0IE=1;


RC1STAbits.SPEN=1;  // разрешение работы последовательного порта (1 - порт включен)
RC1STAbits.CREN=1;  // разрешение приема (1 - прием разрешен)

SPBRG1 = 103;		//  9600

RCIE = 1;           //разрешаем прерывания
TX1IE=1;				//разрешаем прерывание

};


// Отправляем данные по UART
void  UartTransmite(unsigned char *data, unsigned char count)
{
    for(unsigned char i=0;i<count;i++) UartTransmiteBuffer[i]=data[i];
    UartTransmiteCount=count;
    UartTransmiteIndex=0;
    TXEN1 = 1;
}

// Вызываем эту функцию при приеме данных
unsigned char UartRecive(unsigned char *data)
{
    unsigned char count;
    
    count=UartReciveIndex;
    for(unsigned char i=0;i<count;i++) data[i]=UartReciveBuffer[i];
    UartReciveIndex=0;
    UartReciveComplete=0;
    
    return(count);
}

//  готовность принятых данных 
unsigned char  UartComplete(void)
{
    return(UartReciveComplete);
};




// вызываем периодически примерно каждые 256мкс 
void UartTimeOut(void)
{
TMR0IF=0;
if(UartReciveTimeOut)
    if(--UartReciveTimeOut==0) UartReciveComplete=1;
    
}

//  вызываем по прерыванию передачи байта по UART 
void UartTxByte(void)
{

    if (UartTransmiteIndex == UartTransmiteCount) TXEN1 = 0;  // все передали
    else TXREG1 = UartTransmiteBuffer[UartTransmiteIndex++];     // передаем
    
}


//  вызываем по прерыванию приема байта по UART 
void UartRxByte(void)
{

    if(UartReciveIndex<_sizeBufferUart) UartReciveBuffer[UartReciveIndex++] = RCREG1;

    UartReciveComplete=10;
    
    if(OERR1)  {  CREN1 = 0; CREN1 = 1; };  	//сброс ошибки
    
}

//Прерывание от UART
void interrupt  HI_ISR(void)
//void interrupt  low_priority LOW_ISR(void)
{

    if(TMR0IF) UartTimeOut();
    
	if(RCIF) UartRxByte();

	if(TXIF) UartTxByte();


}



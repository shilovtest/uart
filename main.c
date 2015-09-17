/*******************************************************************************
  * @file    main.c
  * @author  shilov.av@gmail.com  
  * @version V1.0
  * @date    15/09/2015
  * @brief   test uart for pic18
  *****************************************************************************/



#include "htc.h"
#include "string.h"
#include "uart.h"



int main(void)
{
    char buffer[256]="Hello World!\r\n";
    unsigned char length;
    
    	/*Настройка портов*/
	LATA = LATB = LATC = 0;
	PORTA = PORTB = PORTC = 0;
	ANSELA = ANSELB = ANSELC = 0;	// все входы цифровые
    TRISA = TRISB = TRISC =  0;		//все входа

	TRISC6=1;	//TX 
	TRISC7=0;   //RX

    UartInit();	

    GIE=1;
    PEIE=1;
    

    UartTransmite(buffer,strlen(buffer));
    
   
    while(1)
    {
        if(UartComplete())
        {
        length=UartRecive(buffer);
        UartTransmite(buffer,length);
        };
    };
    
  
};

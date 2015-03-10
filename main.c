/*
 * File: main.c
 *
 * Copyright (c) 2015, karfes@gmail.com
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 *
 */
#include <ctype.h>
#include <stdlib.h>
#include"gpio.h"
#include"uart.h"
#include "led_blinker.h"

void delay(void);
int char_convert_int(char byte);



int main(void){	
	//temporally UART data holder
	uint8_t byte = 01;
	char reply;

	//initialize system
	SystemInit();

	//initialize UART5 with 8-N-1 settings, 57600 baudrate
	init_uart(UART5_BASE_PTR,periph_clk_khz,57600);

	//clear all interrupts and enable interrupts
	nvic->ICPR[2] |= 1 << (87 & 0x1F); //Clear Pending Interrupts
	nvic->ISER[2] |= 1 << (87 & 0x1F); //Enable Interrupts
	
	//initialize GPIO ports
	gpio_init();

	//Loop forever
	while(1)
	{
		//toggle_LED1();
		delay();
		LOOP:if(data_available()){
			byte = uart_read();
			reply = byte;
			 led_blinker(char_convert_int(reply));}
			 else {
					goto LOOP;}
		}
		delay();
	}
/*
	brief  Silly delay
*/
void delay(void)
{
  volatile unsigned int i,j;

  for(i=0; i<25000; i++)
  {
	for(j=0; j<300; j++)
      __asm__("nop");
  }
}
int char_convert_int(char byte){
	switch (byte){
	case '0':
			return 0;
			break;

	case '1':
		return 1;
		break;

	case '2':
			return 2;
			break;

	case '3':
			return 3;
			break;

	case '4':
			return 4;
			break;

	case '5':
			return 5;
			break;

	case '6':
			return 6;
			break;

	case '7':
			return 7;
			break;

	case '8':
			return 8;
			break;
	case '9':
			return 9;
			break;

	default :
		main();
	        break;
	};
return 0;
}

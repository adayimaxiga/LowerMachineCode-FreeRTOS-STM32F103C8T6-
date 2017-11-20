#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  
/***************************************************************
		@ChipType:	STM32F103C8T6
		@Author: 		LD
		@Date:			2017.11.20
		@OS:				FreeRTOS
		@Email:			adayimaxiga@hotmail.com
***************************************************************/
void delay_init(void);
void delay_ms(u32 nms);
void delay_us(u32 nus);
void delay_xms(u32 nms);

#endif






























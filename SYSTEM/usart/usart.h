#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
/***************************************************************
		@ChipType:	STM32F103C8T6
		@Author: 		LD
		@Date:			2017.11.20
		@OS:				FreeRTOS
		@Email:			adayimaxiga@hotmail.com
***************************************************************/
//如果想串口中断接收，请不要注释以下宏定义
void Uart2Init(u32 bound);
#endif



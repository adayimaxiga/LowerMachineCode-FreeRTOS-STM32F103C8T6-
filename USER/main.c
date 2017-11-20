/***************************************************************
		@ChipType:	STM32F103C8T6
		@Author: 		LD
		@Date:			2017.11.20
		@OS:				FreeRTOS
		@Email:			adayimaxiga@hotmail.com
		@LED:				LED0			LED1
								PB5				PB6
								
		@TIMER:			TIM1			CH1				CH2
													PA8				PA9
													
		@CAN:				CAN1			RX				
		
Total RAM Size = RW Data + ZI Data
Total ROM Size = Code + RO Data + RW Data
***************************************************************/
#include "task_create.h"

//任务优先级
#define START_TASK_PRIO			1
//任务堆栈大小	
#define START_STK_SIZE 			128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

int main(void)
{
		BspInit();
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}




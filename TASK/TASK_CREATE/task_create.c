#include "task_create.h"
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "can.h"
#include "adc.h"
#include "usart.h"
//任务优先级
#define LED_TASK_PRIO			1
//任务堆栈大小	
#define LED_STK_SIZE 			50  
//任务句柄
TaskHandle_t LEDTask_Handler;
//任务函数
void LED_task(void *pvParameters);

//任务优先级
#define MOTOR_TASK_PRIO			25
//任务堆栈大小	
#define MOTOR_STK_SIZE 			256  
//任务句柄
TaskHandle_t MotorTask_Handler;
//任务函数
void Motor_task(void *pvParameters);

//任务优先级
#define CURRENT_TASK_PRIO			26
//任务堆栈大小	
#define CURRENT_STK_SIZE 			256  
//任务句柄
TaskHandle_t CurrentTask_Handler;
//任务函数
void Current_task(void *pvParameters);

void BspInit()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	delay_init();	    				//延时函数初始化	 
	Uart2Init(115200);
	LED_Init();
	TIM1Init();
	CAN_Mode_Init();
	ADCConfig();
}

extern TaskHandle_t StartTask_Handler;

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	//创建开始任务
    xTaskCreate((TaskFunction_t )LED_task,            //任务函数
                (const char*    )"LED_task",          //任务名称
                (uint16_t       )LED_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )LED_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&LEDTask_Handler);   //任务句柄     
    xTaskCreate((TaskFunction_t )Motor_task,            //任务函数
                (const char*    )"LED_task",          //任务名称
                (uint16_t       )MOTOR_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )MOTOR_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&MotorTask_Handler);   //任务句柄     							
    xTaskCreate((TaskFunction_t )Current_task,            //任务函数
                (const char*    )"LED_task",          //任务名称
                (uint16_t       )CURRENT_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )CURRENT_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&CurrentTask_Handler);   //任务句柄  							
		vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();            //退出临界区
}


void LED_task(void *pvParameters)
{
	while(1)
	{
		LED0=!LED0;
		vTaskDelay(500);
	}
}

void Motor_task(void *pvParameters)
{
	portTickType xLastWakeTime;		//给定控制节奏
	/* 变量xLastWakeTime唯一一次显式更新
	*/
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime,5);								//精准控制时间离散节奏
	}
}
int Current;
void Current_task(void *pvParameters)
{
	portTickType xLastWakeTime;		//给定控制节奏
	/* 变量xLastWakeTime唯一一次显式更新
	*/
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		Current = GetCurrent();
		vTaskDelayUntil(&xLastWakeTime,1);								//精准控制时间离散节奏
	}
}


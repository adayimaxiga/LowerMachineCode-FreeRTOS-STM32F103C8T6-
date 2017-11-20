#include "task_create.h"
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "can.h"
#include "adc.h"
#include "usart.h"
//�������ȼ�
#define LED_TASK_PRIO			1
//�����ջ��С	
#define LED_STK_SIZE 			50  
//������
TaskHandle_t LEDTask_Handler;
//������
void LED_task(void *pvParameters);

//�������ȼ�
#define MOTOR_TASK_PRIO			25
//�����ջ��С	
#define MOTOR_STK_SIZE 			256  
//������
TaskHandle_t MotorTask_Handler;
//������
void Motor_task(void *pvParameters);

//�������ȼ�
#define CURRENT_TASK_PRIO			26
//�����ջ��С	
#define CURRENT_STK_SIZE 			256  
//������
TaskHandle_t CurrentTask_Handler;
//������
void Current_task(void *pvParameters);

void BspInit()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    				//��ʱ������ʼ��	 
	Uart2Init(115200);
	LED_Init();
	TIM1Init();
	CAN_Mode_Init();
	ADCConfig();
}

extern TaskHandle_t StartTask_Handler;

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	//������ʼ����
    xTaskCreate((TaskFunction_t )LED_task,            //������
                (const char*    )"LED_task",          //��������
                (uint16_t       )LED_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )LED_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&LEDTask_Handler);   //������     
    xTaskCreate((TaskFunction_t )Motor_task,            //������
                (const char*    )"LED_task",          //��������
                (uint16_t       )MOTOR_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )MOTOR_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&MotorTask_Handler);   //������     							
    xTaskCreate((TaskFunction_t )Current_task,            //������
                (const char*    )"LED_task",          //��������
                (uint16_t       )CURRENT_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )CURRENT_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&CurrentTask_Handler);   //������  							
		vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();            //�˳��ٽ���
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
	portTickType xLastWakeTime;		//�������ƽ���
	/* ����xLastWakeTimeΨһһ����ʽ����
	*/
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime,5);								//��׼����ʱ����ɢ����
	}
}
int Current;
void Current_task(void *pvParameters)
{
	portTickType xLastWakeTime;		//�������ƽ���
	/* ����xLastWakeTimeΨһһ����ʽ����
	*/
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		Current = GetCurrent();
		vTaskDelayUntil(&xLastWakeTime,1);								//��׼����ʱ����ɢ����
	}
}


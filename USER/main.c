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

//�������ȼ�
#define START_TASK_PRIO			1
//�����ջ��С	
#define START_STK_SIZE 			128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

int main(void)
{
		BspInit();
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}




#ifndef _CAN_H
#define _CAN_H
#include "sys.h"
										 							 				    
u8 CAN_Mode_Init(void);//CAN��ʼ��
 
u8 Can_Send_Msg(u8* msg,u8 len);						//��������

u8 Can_Receive_Msg(u8 *buf);							//��������


#endif

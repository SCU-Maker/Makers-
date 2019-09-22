#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOB,GPIO_InitStructure.GPIO_Pin);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_10;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOC,GPIO_InitStructure.GPIO_Pin); 						 //PA.5 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOA,GPIO_InitStructure.GPIO_Pin); 						 //PA.5 ����� 
}
 

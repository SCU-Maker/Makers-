/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include"led.h"
extern volatile u16 times[21],time,i,j,k,l;

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);    
  	//	 time++;  i++;   j++;  k++;  l++;
		//  for(  i=0; i<22; i++  )
			{					
       	times[0]++;      if ( times[0] == 255 )   times[0] = 0;			 /* 500ms ʱ�䵽 */
		 	  times[1]++;      if ( times[1] == 255 )   times[1] = 0;
				times[2]++;      if ( times[2] == 255 )   times[2] = 0;
				times[3]++;      if ( times[3] == 255 )   times[3] = 0;
				times[4]++;      if ( times[4] == 255 )   times[4] = 0;
				times[5]++;      if ( times[5] == 255 )   times[5] = 0;
				times[6]++;      if ( times[6] == 255 )   times[6] = 0;
				times[7]++;      if ( times[7] == 255 )   times[7] = 0;
				times[8]++;      if ( times[8] == 255 )   times[8] = 0;
				times[9]++;      if ( times[9] == 255 )   times[9] = 0;
				times[10]++;      if ( times[10] == 255 )   times[10] = 0;
				times[11]++;      if ( times[11] == 255 )   times[11] = 0;
				times[12]++;      if ( times[12] == 255 )   times[12] = 0;
				times[13]++;      if ( times[13] == 255 )   times[13] = 0;
				times[14]++;      if ( times[14] == 255 )   times[14] = 0;
				times[15]++;      if ( times[15] == 255 )   times[15] = 0;
				times[16]++;      if ( times[16] == 255 )   times[16] = 0;
				times[17]++;      if ( times[17] == 255 )   times[17] = 0;
				times[18]++;      if ( times[18] == 255 )   times[18] = 0;
				times[19]++;      if ( times[19] == 255 )   times[19] = 0;
				times[20]++;      if ( times[20] == 255 )   times[20] = 0;
			}    			        
	}		 	
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

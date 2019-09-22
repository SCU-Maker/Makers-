/*********************************************************************************************************
*
* File                : arm_cortex_m.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.74
* Version             : V1.0
* By                  : V
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/
#include "arm_cortex_m.h"

/*
Private var
*/
static vu32 _CountPerUS;
static vu32 _CountPerMS;








/*******************************************************************************
* Function Name  : void cm3_systick_init(u32 sysclk, u32 xms)
* Description    : SysTick init
                   1. Clock source HCLK
									 2. Interrupt disable
									 3. Counter disable
* Input          : SysClk: current system clock, unit: Hz
* Output         : None
* Return         : ADC value
* Attention		   : None
*******************************************************************************/
void cm3_systick_init(u32 sysclk, u32 xms)
{
	u32 Count_ms;
	Count_ms = ((sysclk/8)*1000); 							//延时1ms需要的计数值
	Count_ms *= xms;										        //Xms需要的计数值
	SysTick->LOAD = Count_ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x03;									    //使能定时器，并使能中断
	return ;
}
/*******************************************************************************
* Function Name  : void CM3_SysTickInit(vu32 SysClk)
* Description    : SysTick init
                   1. Clock source HCLK
									 2. Interrupt disable
									 3. Counter disable
* Input          : SysClk: current system clock, unit: Hz
* Output         : None
* Return         : ADC value
* Attention		   : None
*******************************************************************************/
void CM3_SysTickInit(vu32 SysClk)
{
	SysTick->CTRL = 0x00;
	SysTick->CTRL |= 0x01 << 2;                                                //clock source HCLK
	
	CM3_SysTickCalculate(SysClk);
}
/*******************************************************************************
* Function Name  : void CM3_SysTickCalculate(vu32 SysClk)
* Description    : SysTick init
* Input          : SysClk: current system clock, unit: Hz
* Output         : None
* Return         : ADC value
* Attention		   : None
*******************************************************************************/
void CM3_SysTickCalculate(vu32 SysClk)
{
	_CountPerUS = SysClk / 1000000.0;
	_CountPerMS = SysClk / 1000.0;	
}
/*******************************************************************************
* Function Name  : void CM3_SysTickDelayUS(vu32 Count)
* Description    : delay
* Input          : xus
* Output         : None
* Return         : ADC value
* Attention		   : None
*******************************************************************************/
void CM3_SysTickDelayUS(vu32 Count)
{
	SysTick->LOAD = Count * _CountPerUS;
	SysTick->VAL = 0;
	
	SysTick->CTRL  |= 0x01;
	
	while( !(SysTick->CTRL & (0x01 << 16)) )
		;
	SysTick->CTRL &= ~(0x01 << 16);
	SysTick->CTRL &= ~0x01;
}
/*******************************************************************************
* Function Name  : void CM3_SysTickDelayMS(vu32 Count)
* Description    : delay xms
* Input          : xms
* Output         : None
* Return         : ADC value
* Attention		   : None
*******************************************************************************/
void CM3_SysTickDelayMS(vu32 Count)
{
	vu32 i;
	
	Count *= 2;
	
	for(i = 0; i < Count; i++)
	{
		CM3_SysTickDelayUS(500);
	}
}





/*========================================================
*函数名  ：__asm void sys_reset(void) 
*功能描述：系统复位
*参数    ：
*返回值  ：
*作者    ：阎文来, 20140922
========================================================*/
__asm void sys_reset(void)         
{
	MOV R0, #1          
	MSR FAULTMASK, R0  
	LDR R0, =0xE000ED0C  
	LDR R1, =0x05FA0004  
	STR R1, [R0]      
deadloop
	B deadloop         
}

	






































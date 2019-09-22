/*********************************************************************************************************
*
* File                : arm_cortex_m.h
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
#ifndef    ARM_CORTEX_M_H
  #define  ARM_CORTEX_M_H
#include "stm32f10x.h"


void cm3_systick_init(u32 sysclk, u32 xms);
void CM3_SysTickInit(vu32 SysClk);
void CM3_SysTickCalculate(vu32 SysClk);
void CM3_SysTickDelayUS(vu32 Count);
void CM3_SysTickDelayMS(vu32 Count);


__asm void sys_reset(void);
	
	
	
#endif




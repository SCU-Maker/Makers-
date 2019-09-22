#include "stm32f10x.h"
#include "Uart.h"
#include "arm_cortex_m.h"
#include "epd.h"

/*******************************************************************************
* Function Name  : NVIC_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
* Function Name  : void led_init(void)
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
}
/*******************************************************************************
* Function Name  : void base_draw(void)
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void base_draw(void)
{
	int i, j;
	
	
	/*
	draw pixel
	*/
	epd_clear();
	for(j = 0; j < 600; j += 50)
	{
		for(i = 0; i < 800; i += 50)
		{
			epd_draw_pixel(i, j);
			epd_draw_pixel(i, j + 1);
			epd_draw_pixel(i + 1, j);
			epd_draw_pixel(i + 1, j + 1);
		}
	}
  epd_udpate();
	
	CM3_SysTickDelayMS(3000);
	
  /*
	draw line
  */	
	epd_clear();
  for(i = 0; i < 800; i += 100)
	{
		epd_draw_line(0, 0, i, 599);
		epd_draw_line(799, 0, i, 599);
	}
	epd_udpate();
  CM3_SysTickDelayMS(3000);	
	
	/*
	fill rect
	*/
	epd_clear();
	epd_set_color(BLACK, WHITE);
	epd_fill_rect(10, 10, 100, 100);
	
	epd_set_color(DARK_GRAY, WHITE);
	epd_fill_rect(110, 10, 200, 100);
	
	epd_set_color(GRAY, WHITE);
	epd_fill_rect(210, 10, 300, 100);	
	
	epd_udpate();
  CM3_SysTickDelayMS(3000);		
	
	/*
	draw circle
	*/
	epd_set_color(BLACK, WHITE);
	epd_clear();
	for(i = 0; i < 300; i += 40)
	{
		epd_draw_circle(399, 299, i);
	}
	epd_udpate();
  CM3_SysTickDelayMS(3000);
	
	/*
	fill circle
	*/
	epd_clear();
	for(j = 0; j < 6; j++)
	{
		for(i = 0; i < 8; i++)
		{
			epd_fill_circle(50 + i * 100, 50 + j * 100, 50);
		}
	}
	epd_udpate();
  CM3_SysTickDelayMS(3000);

  /*
	draw triangle
	*/
	epd_clear();
	for(i = 1; i < 5; i++)
	{
		epd_draw_triangle(399, 249 - i * 50, 349 - i * 50, 349 + i * 50, 449 + i * 50, 349 + i * 50);
	}
	epd_udpate();
  CM3_SysTickDelayMS(3000);	
}
void draw_text_demo(void)
{
	epd_set_color(BLACK, WHITE);
	epd_clear();
	epd_set_ch_font(GBK32);
	epd_disp_string("ＧＢＫ３２：你好世界", 0, 50);
	epd_set_ch_font(GBK48);
	epd_disp_string("ＧＢＫ４８：你好世界", 0, 100);
	epd_set_ch_font(GBK64);
	epd_disp_string("ＧＢＫ６４：你好世界", 0, 160);
	
	epd_set_en_font(ASCII32);
	epd_disp_string("ASCII32: Hello, World!", 0, 300);
	epd_set_en_font(ASCII48);
	epd_disp_string("ASCII48: Hello, World!", 0, 350);	
	epd_set_en_font(ASCII64);
	epd_disp_string("ASCII64: Hello, World!", 0, 450);
	epd_udpate();	
	CM3_SysTickDelayMS(3000);	
}
void draw_bitmap_demo(void)
{
	epd_clear();
	epd_disp_bitmap("PIC4.BMP", 0, 0);
	epd_udpate();	
	CM3_SysTickDelayMS(5000);
	
	epd_clear();
  epd_disp_bitmap("PIC2.BMP", 0, 100);
	epd_disp_bitmap("PIC3.BMP", 400, 100);
	epd_udpate();	
  CM3_SysTickDelayMS(5000);

  epd_clear();
	epd_disp_bitmap("PIC7.BMP", 0, 0);
	epd_udpate();			
}


int main(void)
{ 
	int flash_flag = 0;
	
  SystemInit();
	CM3_SysTickInit(72000000);
	COM1_Init();
	
	led_init();
	
	epd_init();
	epd_wakeup();	                                                                 //唤醒
	
	epd_set_memory(MEM_NAND);                                                      //设置存储区为外部 TFCard
	
	/*
	base Draw demo
	*/
  base_draw();
		
	/*
	Draw text demo
	*/
  draw_text_demo();
	
	/*
	Draw bitmap
	*/
	draw_bitmap_demo();
	
  epd_enter_stopmode();                                                         //睡眠
  while(1)
	{
		CM3_SysTickDelayMS(500);
		if(flash_flag)
		{
			flash_flag = 0;
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		}
		else
		{
			flash_flag = 1;
			GPIO_SetBits(GPIOF, GPIO_Pin_9);
		}
	}
}




























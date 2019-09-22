#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24l01.h" 	 
#include "adc.h"
#include "bsp_ds18b20.h"
#include "stm32f10x.h"
#include "Time_test.h"
#include "oled.h"
#include "bmp.h"
volatile u16 times[21]={0}, time,i,j,k,l;	 

 int main(void)
 {	 
    u16 chanl,chanl1,chanl2,chanl3,chanl4;  
	  int requ;	  u16 len;	
	  u16 col=0,tl=0,t=0;   int a[27]; // u16 adcx,adcx2;			 
    SystemInit();	    
	  delay_init();	    	 //延时函数初始化	  
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
    TIM2_NVIC_Configuration();  /* TIM2 定时配置 */
    TIM2_Configuration(); 
    START_TIME;	
    LED_Init();		  			//初始化与LED连接的硬件接口   	   
	if(1)//RX模式 mode
	{  
		while(1)
		{	 	                        		   			 
		if(USART_RX_STA&0x8000)
		{					              
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度          
			for(t=0;t<len;t++)
			{  
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){}//等待发送结束  00 123 123 123 123 0
                USART_RX_BUF[t]-=48; 						//printf("ERROR");	00    54321  000     0\n
			}      			
		if(USART_RX_BUF[len-15]==0&&USART_RX_BUF[len-1]==0&&USART_RX_BUF[len-14]==0){ 
          tl=( USART_RX_BUF[len-13]*100+USART_RX_BUF[len-12]*10+USART_RX_BUF[len-11] );   
				 a[3*tl-3] = ( USART_RX_BUF[len-10]*100+USART_RX_BUF[len-9]*10+USART_RX_BUF[len-8]);//00 123 255 255 255 0
				 a[3*tl-2] = ( USART_RX_BUF[len-7]*100+USART_RX_BUF[len-6]*10+USART_RX_BUF[len-5]);
				 a[3*tl-1] = ( USART_RX_BUF[len-4]*100+USART_RX_BUF[len-3]*10+USART_RX_BUF[len-2]);	
//				 if( tl==0 )  { 
//					 a[24] = ( USART_RX_BUF[len-10]*100+USART_RX_BUF[len-9]*10+USART_RX_BUF[len-8]);//00 123 255 255 255 0
//					 a[25] = ( USART_RX_BUF[len-7]*100+USART_RX_BUF[len-6]*10+USART_RX_BUF[len-5]);
//					 a[26] = ( USART_RX_BUF[len-4]*100+USART_RX_BUF[len-3]*10+USART_RX_BUF[len-2]);	
//				 }
		}
		USART_RX_STA=0;     
	  }
			if( tl==11){  	LED0 = 1;	LED1 = 1;	LED2 = 1;	LED3 = 1;	LED4 = 1;	
							LED5 = 1;	LED6 = 1;	LED7 = 1;	LED8 = 1;	LED9 = 1;	
							LED10 = 1;	LED11 = 1;	LED12 = 1;	LED13 = 1;	LED14 = 1;	LED15 = 1;	
							LED16 = 1;	LED17 = 1;	LED18 = 1;	LED19 = 1;	LED20 = 1;	
					  }		
			if( tl==0){  	LED0 = 0;	LED1 = 0;	LED2 = 0;	LED3 = 0;	LED4 = 0;	
							LED5 = 0;	LED6 = 0;	LED7 = 0;	LED8 = 0;	LED9 = 0;	
							LED10 = 0;	LED11 = 0;	LED12 = 0;	LED13 = 0;	LED14 = 0;	LED15 = 0;	
							LED16 = 0;	LED17 = 0;	LED18 = 0;	LED19 = 0;	LED20 = 0;	
					  }	
//			if( tl==0){  if( times[0]<=a[24]){   LED0 = 1;	LED3 = 1;	LED6 = 1;	LED9 = 1;	LED12 = 1;	LED15 = 1;	LED18 = 1;	 }
//                            else {  LED0 = 0;	LED3 = 0;	LED6 = 0;	LED9 = 0;	LED12 = 0;	LED15 = 0;	LED18 = 0; }    
//                    if( times[1]<=a[25]  ){  LED1 = 1;	LED4 = 1; LED7 = 1;	LED10 = 1;	LED13 = 1;	LED16 = 1;	LED19 = 1;	 }
//                            else {  LED1 = 0;	LED4 = 0; LED7 = 0;	LED10 = 0;	LED13 = 0;	LED16 = 0;	LED19 = 0;	}		
//                    if( times[2]<=a[26] ){ 	LED2 = 1;	LED5 = 1;	LED8 = 1;  LED11 = 1;  LED14 = 1;	LED17 = 1;	LED20 = 1;	 }
//                            else { LED2 = 0;	LED5 = 0;LED8 = 0;LED11 = 0;	LED14 = 0;	LED17 = 0;	LED20 = 0; }
//					}			
		    if( tl==1){  if( times[0]<=a[3*tl-3]){  chanl=0;  LED0=1;  }
                            else {  LED0=0;	 if(chanl==0)  {  chanl=1;  } }    
                    if( times[1]<=a[3*tl-2]  ){  chanl1=0;  LED1=1; }
                            else {  LED1=0;  if(chanl1==0){  chanl1=0;  } }		
                    if( times[2]<=a[3*tl-1] ){  chanl2=0;  LED2=1; }
                            else {  LED2=0;   if(chanl2==0){  chanl2=1;  } }
					}
            if( tl==2){  if( times[3]<=a[3*tl-3]){  chanl=0;  LED3=1; }
                            else {  LED3=0;	 if(chanl==0)  {  chanl=1;  } }    
                         if( times[4]<=a[3*tl-2]  ){  chanl1=0;  LED4=1; }
                            else {  LED4=0;  if(chanl1==0){  chanl1=0;  } }		
                         if( times[5]<=a[3*tl-1] ){  chanl2=0;  LED5=1; }
                            else {  LED5=0;   if(chanl2==0){  chanl2=1;  } }
						}
            if( tl==3){  if( times[6]<=a[3*tl-3]){  chanl=0;  LED6=1; }
                            else {  LED6=0;	 if(chanl==0)  {  chanl=1;  } }    
                         if( times[7]<=a[3*tl-2]  ){  chanl1=0;  LED7=1;}
                            else {  LED7=0;  if(chanl1==0){  chanl1=0; } }		
                         if( times[8]<=a[3*tl-1] ){  chanl2=0;  LED8=1; }
                            else {  LED8=0;   if(chanl2==0){  chanl2=1;  } }
						}
            if( tl==4){  if( times[9]<=a[3*tl-3]){  chanl=0;  LED9=1; }
                            else {  LED9=0;	 if(chanl==0)  {  chanl=1; } }    
                         if( times[10]<=a[3*tl-2]  ){  chanl1=0;  LED10=1; }
                            else {  LED10=0;  if(chanl1==0){  chanl1=0; } }		
                         if( times[11]<=a[3*tl-1] ){  chanl2=0;  LED11=1; }
                            else {  LED11=0;   if(chanl2==0){  chanl2=1; } }
						}
            if( tl==5){  if( times[12]<=a[3*tl-3]){  chanl=0;  LED12=1; }
                            else {  LED12=0;	 if(chanl==0)  {  chanl=1; } }    
                         if( times[13]<=a[3*tl-2]  ){  chanl1=0;  LED13=1; }
                            else {  LED13=0;  if(chanl1==0){  chanl1=0;} }		
                         if( times[14]<=a[3*tl-1] ){  chanl2=0;  LED14=1; }
                            else {  LED14=0;   if(chanl2==0){  chanl2=1;  } }
						}
            if( tl==6){  if( times[15]<=a[3*tl-3]){  chanl=0;  LED15=1; }
                            else {  LED15=0;	 if(chanl==0)  {  chanl=1;  } }    
                         if( times[16]<=a[3*tl-2]  ){  chanl1=0;  LED16=1; }
                            else {  LED16=0;  if(chanl1==0){  chanl1=0;  } }		
                         if( times[17]<=a[3*tl-1] ){  chanl2=0;  LED17=1; }
                            else {  LED17=0;   if(chanl2==0){  chanl2=1; } }
						}
            if( tl==7){  if( times[18]<=a[3*tl-3]){  chanl=0;  LED18=1; }
                            else {  LED18=0;	 if(chanl==0)  {  chanl=1;  } }    
                         if( times[19]<=a[3*tl-2]  ){  chanl1=0;  LED19=1; }
                            else {  LED19=0;  if(chanl1==0){  chanl1=0;  } }		
                         if( times[20]<=a[3*tl-1] ){  chanl2=0;  LED20=1; }
                            else {  LED20=0;   if(chanl2==0){  chanl2=1;  } }
						}			
   }
  }
}



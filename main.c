#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "sys.h"

#define wsChipNum   50 


#define WsDat_Dark  0x000000
#define WsDat_Blue  0xff0000
#define WsDat_Green 0x0000ff   
#define WsDat_Red   0x00ff00 
#define WsDat_White 0xffffff 

void WS_Init()
{
    GPIO_InitTypeDef  GPIO_InitStructure;        
        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE );         

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
                                  | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7	;                               
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

}

void TX0(unsigned char channel) 
{ 
	  switch(channel)
		{
			  case 1 :PAout(0) = 1; break;
			  case 2 :PAout(1) = 1; break;
			  case 3 :PAout(2) = 1; break;
			  case 4 :PAout(3) = 1; break;
			  case 5 :PAout(4) = 1; break;
			  case 6 :PAout(5) = 1; break;
			  case 7 :PAout(6) = 1; break;
			  case 8 :PAout(7) = 1; break;
			  case 9 :PBout(5) = 1; break;
			  case 10 :PBout(6) = 1; break;
			  default :PAout(0) = 1; break;
		}
	  __NOP();__NOP();__NOP();
	  __NOP();__NOP();__NOP();
	  switch(channel)
		{
			  case 1 :PAout(0) = 0; break;
			  case 2 :PAout(1) = 0; break;
			  case 3 :PAout(2) = 0; break;
			  case 4 :PAout(3) = 0; break;
			  case 5 :PAout(4) = 0; break;
			  case 6 :PAout(5) = 0; break;
			  case 7 :PAout(6) = 0; break;
			  case 8 :PAout(7) = 0; break;
			  case 9 :PBout(5) = 0; break;
			  case 10 :PBout(6) = 0; break;
			  default :PAout(0) = 0; break;
		}
	  __NOP();__NOP();__NOP();__NOP();__NOP();
	  __NOP();__NOP();__NOP();__NOP();__NOP();
	  __NOP();__NOP();__NOP();__NOP();__NOP();
	  __NOP();__NOP();__NOP();__NOP();__NOP();
	  __NOP();__NOP();__NOP();__NOP();__NOP(); 
} 
void TX1(unsigned char channel)         
{ 
	 switch(channel)
		{
			  case 1 :PAout(0) = 1; break;
			  case 2 :PAout(1) = 1; break;
			  case 3 :PAout(2) = 1; break;
			  case 4 :PAout(3) = 1; break;
			  case 5 :PAout(4) = 1; break;
			  case 6 :PAout(5) = 1; break;
			  case 7 :PAout(6) = 1; break;
			  case 8 :PAout(7) = 1; break;
			  case 9 :PBout(5) = 1; break;
			  case 10 :PBout(6) = 1; break;
			  default :PAout(0) = 1; break;
		}
	  __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();  
	  switch(channel)
		{
			  case 1 :PAout(0) = 0; break;
			  case 2 :PAout(1) = 0; break;
			  case 3 :PAout(2) = 0; break;
			  case 4 :PAout(3) = 0; break;
			  case 5 :PAout(4) = 0; break;
			  case 6 :PAout(5) = 0; break;
			  case 7 :PAout(6) = 0; break;
			  case 8 :PAout(7) = 0; break;
			  case 9 :PBout(5) = 0; break;
			  case 10 :PBout(6) = 0; break;
			  default :PAout(0) = 0; break;
		}
} 

void wsSetOneChip(unsigned char channel,unsigned long dat)
{
    unsigned char i;
        
    for(i=0; i < 24; i++)
    {
        if(0x800000 == (dat & 0x800000) )        
            TX1(channel);
        else     
					  TX0(channel);
        dat<<=1;                                                       
     }
}

void wsSetAllChip(unsigned char channel,unsigned long dat)
{
    unsigned char j;
    for(j=0; j < wsChipNum; j++)
    {
        wsSetOneChip(channel,dat);  // j / 0
    }
       
}

void wsSetWaterExtinguish(unsigned char channel,unsigned char speed)
{ 
	  unsigned char i;
	  unsigned char j;
	  unsigned char k;
    for( i = 1 ; i < wsChipNum; i++)
    {
        for( j=0; j <= i; j++)
        {
             wsSetOneChip(channel,WsDat_Dark);   
        }
				for( k=0; k <=speed; k++)
				{
				    delay_ms(1);
				}
	  }			
}	

void wsSetWaterLight(unsigned char channel,unsigned long dat,unsigned char speed)
{ 
	  unsigned char i;
	  unsigned char j;
	  unsigned char k;
    for( i = 1 ; i < wsChipNum; i++)
    {
        for( j=0; j <= i; j++)
        {
             wsSetOneChip(channel,dat);   
        }
				for( k=0; k <=speed; k++)
				{
				    delay_ms(1);
				}
	  }			
}	

int main(void)
{ 
 
	delay_init();		  //初始化延时函数
  WS_Init();///

  wsSetAllChip(1,WsDat_Green);
	wsSetAllChip(2,WsDat_Green);
	wsSetAllChip(3,WsDat_Green);
	wsSetAllChip(4,WsDat_Green);
	wsSetAllChip(5,WsDat_Green);
	wsSetAllChip(6,WsDat_Green);
	wsSetAllChip(7,WsDat_Green);
  wsSetAllChip(8,WsDat_Green);
	wsSetAllChip(9,WsDat_Green);
	wsSetAllChip(10,WsDat_Green);
	delay_ms(100);  
	delay_ms(100);  
	delay_ms(100); 
	delay_ms(100);  
	delay_ms(100);  
	delay_ms(100); 
	delay_ms(100);  
	delay_ms(100);  
	delay_ms(100); 
	delay_ms(100);  
	delay_ms(100);  
	delay_ms(100); 
	delay_ms(100);  
	delay_ms(100);  
	delay_ms(100); 	
	
	
//	delay_ms(100);  
//               
//	wsSetOneChip(WsDat_Dark);  // j / 0
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//  wsSetOneChip(WsDat_Blue);  // j / 0
//  wsSetOneChip(WsDat_Blue);  // j / 0
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//  wsSetOneChip(WsDat_Green);  // j / 0
//  wsSetOneChip(WsDat_Green);  // j / 0
//  wsSetOneChip(WsDat_Green);  // j / 0
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//	delay_ms(100);
//  wsSetOneChip(WsDat_Red);  // j / 0
//  wsSetOneChip(WsDat_Red);  // j / 0
//  wsSetOneChip(WsDat_Red);  // j / 0
//  wsSetOneChip(WsDat_Red);  // j / 0
			
	while(1)
	{
		//wsSetAllChip(WsDat_Red);
		//wsSetWaterExtinguish(100);
		wsSetAllChip(1,WsDat_Red);
		wsSetWaterLight(1,WsDat_Blue ,10);
		
		wsSetAllChip(2,WsDat_Red);
		wsSetWaterLight(2,WsDat_Blue ,10);
		
		wsSetAllChip(3,WsDat_Red);
		wsSetWaterLight(3,WsDat_Blue ,10);
		
		wsSetAllChip(4,WsDat_Red);
		wsSetWaterLight(4,WsDat_Blue ,10);
		
		wsSetAllChip(5,WsDat_Red);
		wsSetWaterLight(5,WsDat_Blue ,10);
		
		wsSetAllChip(6,WsDat_Red);
		wsSetWaterLight(6,WsDat_Blue ,10);
		
		wsSetAllChip(7,WsDat_Red);
		wsSetWaterLight(7,WsDat_Blue ,10);
		
		wsSetAllChip(8,WsDat_Red);
		wsSetWaterLight(8,WsDat_Blue ,10);
		
		wsSetAllChip(9,WsDat_Red);
		wsSetWaterLight(9,WsDat_Blue ,10);
		
		wsSetAllChip(10,WsDat_Red);
		wsSetWaterLight(10,WsDat_Blue ,10);
		
	}
	return 0;
	
}



 





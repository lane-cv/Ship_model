#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;
	if(mode)key_up=1; 	  
	if(key_up&&(WK_UP==0))
	{
		delay_ms(10);
		key_up=0;
		if(WK_UP==0)return WKUP_PRES;
	}else if(WK_UP==1)key_up=1; 	    
 	return 0;
}

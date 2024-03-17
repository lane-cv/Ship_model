//#include "timer.h"
//#include "led.h"
#include "usart.h"
#include "time.h"


const u16 DGo=900;
const u16 CGo=700;
const u16 BGo=650;
const u16 AGo=600;
const u16 stop=500;
const u16 ABack=450;
const u16 BBack=420;
const u16 CBack=400;
const u16 DBack=350;

void MainDGo(void)
{
  TIM_SetCompare1(TIM3 , DGo);
}

void MainCGo(void)
{
  TIM_SetCompare1(TIM3 , CGo);
}

void MainBGo(void)
{
  TIM_SetCompare1(TIM3 , BGo);
}
void MainAGo(void)
{
  TIM_SetCompare1(TIM3 , AGo);
}

void MainStop(void)
{
  TIM_SetCompare1(TIM3 , stop);

}

void MainDBack(void)
{
  TIM_SetCompare1(TIM3 , DBack);
}

void MainCBack(void)
{
  TIM_SetCompare1(TIM3 , CBack);
}

void MainBBack(void)
{
  TIM_SetCompare1(TIM3 , BBack);
}

void MainABack(void)
{
  TIM_SetCompare1(TIM3 , ABack);
}



void Left(void)
{
  TIM_SetCompare1(TIM4 , 1950);

}

void MidLeft(void)
{
  TIM_SetCompare1(TIM4 , 1880);

}

void Right(void)
{
  TIM_SetCompare1(TIM4 , 1800);

}

void MidRight(void)
{
  TIM_SetCompare1(TIM4 , 1820);

}

void Mid(void)
{
  TIM_SetCompare1(TIM4 , 1850);

}



void TIM3_CH1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	//要开启复用功能的时钟才能重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE);

	
	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OC1Init(TIM3,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM3_CH1

	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
}


void TIM4_CH1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//要开启复用功能的时钟才能重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);

	
	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);

	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1

	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	//使能定时器
	TIM_Cmd(TIM4,ENABLE);
}



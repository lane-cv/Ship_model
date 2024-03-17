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

	//Ҫ�������ù��ܵ�ʱ�Ӳ�����ӳ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE);

	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//��ʼ��TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//��װ��ֵ
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//Ԥ��Ƶֵ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //ʱ�ӷ�Ƶ1��2��4��Ƶ
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ü���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	//��ʼ������Ƚϲ���
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�������
	TIM_OC1Init(TIM3,&TIM_OCInitTypeStruct); //ѡ��ʱ�����ͨ�� TIM3_CH1

	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
}


void TIM4_CH1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//Ҫ�������ù��ܵ�ʱ�Ӳ�����ӳ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);

	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//��ʼ��TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//��װ��ֵ
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//Ԥ��Ƶֵ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //ʱ�ӷ�Ƶ1��2��4��Ƶ
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ü���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);

	//��ʼ������Ƚϲ���
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�������
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //ѡ��ʱ�����ͨ�� TIM4_CH1

	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE);
}



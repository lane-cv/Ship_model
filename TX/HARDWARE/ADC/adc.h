#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
/*
��ӭ��ע���ںţ�����ԱС��

���ں����������ѧ�������Ӱ����ߣ���ģ�飬ѧӲ���������Ҵ�0�ߵ�1��
ÿ���»���һ����ҵ����Ѷȵ�DIY���ݣ���ѧ�ڴ��ĵ����ѿ��Թ�עһ�£�
��ʱ������Ͳ�������������ӭѧ��ѧ������ע����
*/


void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 

#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
/*
欢迎关注公众号：程序员小哈

公众号内容面向大学生，电子爱好者，玩模块，学硬件，带领大家从0走到1，
每个月会做一个毕业设计难度的DIY内容，下学期大四的朋友可以关注一下，
到时做毕设就不用找人啦，欢迎学弟学妹来关注哈。
*/


void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 

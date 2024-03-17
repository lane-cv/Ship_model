#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "nRF24L01_API.h"
#include "adc.h"
#include "time.h"
/************************************************
 ALIENTEK精英STM32开发板实验31
 MPU6050六轴传感器 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司
 作者：正点原子 @ALIENTEK
************************************************/


const u8 TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};
const u16 Dmax=4000;
const u16 Cmax=3800;
const u16 Bmax=3400;
const u16 Amax=2800;
const u16 Amin=1200;
const u16 Bmin=700;
const u16 Cmin=200;
const u16 Dmin=50;
const u16 bigleft=50;
const u16 midleft=1500;
const u16 midright=2500;
const u16 bigright=4000;



u8 indexw=0,inde=0;
int main(void)
{
    u8 key=0,t;
    u16 VRX=0,VRZ=0;
    u8 tmp_buf[33]= {0};
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
    LED_Init();		  			//初始化与LED连接的硬件接口
    KEY_Init();
    NRF24L01_Init();    		//初始化NRF24L01 			//设置字体为红色
    Adc_Init();


    while(NRF24L01_Check())
    {
        delay_ms(500);
        LED0=!LED0;
    }


    NRF24L01_TX_Mode((u8*)TX_ADDRESS);

    for(t=0; t<5; t++)
    {

        tmp_buf[t]='0';

    }
    while(1)
    {
        if(KEY_Scan(0)>0)
            key=!key;
        if(key==1)
        {

            tmp_buf[0]='1';
            tmp_buf[1]='1';
            tmp_buf[2]='1';
            tmp_buf[3]='1';
            NRF24L01_TxPacket(tmp_buf);
            break;
        }//最大油门
    }

    while(1)
    {
        if(KEY_Scan(0)>0)
            key=!key;
        if(key==0)
        {

            tmp_buf[0]='2';
            tmp_buf[1]='2';
            tmp_buf[2]='2';
            tmp_buf[3]='2';
            NRF24L01_TxPacket(tmp_buf);
            break;
        }//最大油门
    }
		
    while(1)
    {
        VRX = Get_Adc(5);
        VRZ = Get_Adc(7);
        if(tmp_buf[4]<'9')
        {
            tmp_buf[4]+=1;
        }
        else
            tmp_buf[4]='0';
   


        if(VRZ>=Dmax)
        {
            if(inde!=3)
            {
                tmp_buf[0]='3';
                tmp_buf[1]='3';
                tmp_buf[2]='3';
                tmp_buf[3]='3';
                NRF24L01_TxPacket(tmp_buf);              
                inde=3;
            }
        }//主电机D速前进
        else if(VRZ>=Cmax&&VRZ<Dmax)
        {
            if(inde!=4)
            {
                tmp_buf[0]='3';
                tmp_buf[1]='3';
                tmp_buf[2]='2';
                tmp_buf[3]='2';
                NRF24L01_TxPacket(tmp_buf);           
                inde=4;
            }
        }//主电机C速前进
        else if(VRZ>=Bmax&&VRZ<Cmax)
        {
            if(inde!=5)
            {
                tmp_buf[0]='4';
                tmp_buf[1]='4';
                tmp_buf[2]='4';
                tmp_buf[3]='4';
                NRF24L01_TxPacket(tmp_buf);             
                inde=5;
            }
        }//主电机B速前进
				
        else if(VRZ>=Amax&&VRZ<Bmax)
        {
            if(inde!=6)
            {

                tmp_buf[0]='4';
                tmp_buf[1]='4';
                tmp_buf[2]='2';
                tmp_buf[3]='2';
                NRF24L01_TxPacket(tmp_buf);
                inde=6;             
            }
        }//主电机A速前进
				
        else if(VRZ>=Bmin&&VRZ<Amin)
        {
            if(inde!=7)
            {
                tmp_buf[0]='5';
                tmp_buf[1]='5';
                tmp_buf[2]='5';
                tmp_buf[3]='5';
                NRF24L01_TxPacket(tmp_buf);            
                inde=7;
            }
        }//主电机A速后退

        else if(VRZ>=Cmin&&VRZ<Bmin)
        {
            if(inde!=8)
            {
                tmp_buf[0]='5';
                tmp_buf[1]='5';
                tmp_buf[2]='2';
                tmp_buf[3]='2';
                NRF24L01_TxPacket(tmp_buf);              
                inde=8;          
            }
        }//主电机B速后退

        else if(VRZ>=Dmin&&VRZ<Cmin)
        {
            if(inde!=9)
            {
                tmp_buf[0]='6';
                tmp_buf[1]='6';
                tmp_buf[2]='6';
                tmp_buf[3]='6';
                NRF24L01_TxPacket(tmp_buf);           
                inde=9;
            }
        }//主电机C速后退

        else if(VRZ<Dmin)
        {
            if(inde!=10)
            {
                tmp_buf[0]='6';
                tmp_buf[1]='6';
                tmp_buf[2]='2';
                tmp_buf[3]='2';
                NRF24L01_TxPacket(tmp_buf);
                inde=10;
            }
        }//主电机D速后退

        else if(VRZ>=Amin&&VRZ<Amax)
        {
            if(inde!=11)
            {
                tmp_buf[0]='7';
                tmp_buf[1]='7';
                tmp_buf[2]='7';
                tmp_buf[3]='7';
                NRF24L01_TxPacket(tmp_buf);               
                inde=11;
            }
        }//主电机停


        if(VRX<bigleft)
        {
            if(indexw!=1)
            {
                tmp_buf[0]='1';
                tmp_buf[1]='1';
                tmp_buf[2]='2';
                tmp_buf[3]='2';
                NRF24L01_TxPacket(tmp_buf);             
                indexw=1;
            }
        }//大左转
				
        else if(VRX>=bigleft&&VRX<midleft)
        {
            if(indexw!=9)
            {
                tmp_buf[0]='1';
                tmp_buf[1]='1';
                tmp_buf[2]='3';
                tmp_buf[3]='3';
                NRF24L01_TxPacket(tmp_buf);               
                indexw=9;
            }
        }//中左转
				
        else if(VRX>=midright&&VRX<bigright)
        {
            if(indexw!=10)
            {
                tmp_buf[0]='1';
                tmp_buf[1]='1';
                tmp_buf[2]='4';
                tmp_buf[3]='4';
                NRF24L01_TxPacket(tmp_buf);              
                indexw=10;
            }
        }//中右转
				
        else if(VRX>=bigright)
        {
            if(indexw!=11)
            {
                tmp_buf[0]='1';
                tmp_buf[1]='1';
                tmp_buf[2]='5';
                tmp_buf[3]='5';
                NRF24L01_TxPacket(tmp_buf);            
                indexw=11;
            }
        }//大右转

        else if(VRX>=midleft&&VRX<midright)
        {
            if(indexw!=16)
            {
                tmp_buf[0]='2';
                tmp_buf[1]='2';
                tmp_buf[2]='6';
                tmp_buf[3]='6';
                NRF24L01_TxPacket(tmp_buf);             
                indexw=16;
            }
        }//舵机回中			
    }
}



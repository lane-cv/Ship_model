#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "nRF24L01_API.h"
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

int main(void)
{

    u16 index=0,index1=0,index2=0,t=0;
    int decode=0;
    u8 tmp_buf[33]= {0};
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
   TIM3_CH1_PWM_Init(1999,71);
		TIM4_CH1_PWM_Init(1999,719);
    LED_Init();		  			//初始化与LED连接的硬件接口
    NRF24L01_Init();    		//初始化NRF24L01 

    while(NRF24L01_Check())
    {
        delay_ms(500);
        LED0=0;
    }


    NRF24L01_RX_Mode((u8*)RX_ADDRESS);
		
//		 MainDGo();
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		MainStop();
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
		
    while (1)
    {
        if (NRF24L01_RxPacket(tmp_buf) == 0)
        {
            tmp_buf[32] = 0;//加入字符串结束符
            decode= (tmp_buf[0]-48)*1000+(tmp_buf[1]-48)*100+(tmp_buf[2]-48)*10+(tmp_buf[3]-48);
            switch (decode)
            {

            case 1111://最大油门
                if(index1!=1)
                {
									 MainDGo();
                    index1=1;
                }
                break;

            case 2222://最小油门
                if(index1!=2)
                {
									MainStop();
                    index1=2;
                }
                break;

            case 3333://主电机D速前进

                if(index2!=3)
                {
                    MainDGo();
                    index2=3;
                }
                break;
								
								case 3322://主电机C速前进

                if(index2!=4)
                {
                    MainCGo();
                    index2=4;
                }
                break;

            case 4444://主电机B速前进

                if(index2!=5)
                {
                    MainBGo();
                    index2=5;
                }
                break;
								
					  case 4422://主电机A速前进

                if(index2!=6)
                {
                    MainAGo();
                    index2=6;
                }
                break;

            case 5555://主电机A速后退

                if(index2!=7)
                {
                    MainABack();
                    index2=7;
                }
                break;
								case 5522://主电机B速后退

                if(index2!=8)
                {
                    MainBBack();
                    index2=8;
                }
                break;

            case 6666://主电机C速后退

                if(index2!=9)
                {
                    MainCBack();
                    index2=9;;
                }
                break;
						case 6622://主电机D速后退

                if(index2!=10)
                {
                    MainDBack();
                    index2=10;
                }
                break;

            case 7777://主电机停

                if(index2!=11)
                {
                    MainStop();
                    index2=11;
                }
                break;

            case 1122://大左转

                if(index!=8)
                {
                    
									Left();
                    index=8;
                }
                break;

            case 1133://中左转

                if(index!=9)
                {
             MidLeft();
                    index=9;
                }
                break;

            case 1144://中右转

                if(index!=10)
                {
              MidRight();
                    index=10;
                }
                break;

            case 1155://大右转

                if(index!=11)
                {
             
									Right();
                    index=11;
                }
                break;  
            case 2266://舵机回中

                if(index!=16)
                {
                  
									Mid();
                    index=16;
                }
                break;

          
            }

        }
        else
        {

            delay_us(5);
            t++;
            if (t == 20000)//大约1s钟改变一次状态
            {
                t = 0;
                LED0 = !LED0;
            }

        }
    }
}


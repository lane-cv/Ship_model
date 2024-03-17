#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "nRF24L01_API.h"
/************************************************
 ALIENTEK��ӢSTM32������ʵ��31
 MPU6050���ᴫ���� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

const u8 TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};

int main(void)
{

    u16 index=0,index1=0,index2=0,t=0;
    int decode=0;
    u8 tmp_buf[33]= {0};
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
   TIM3_CH1_PWM_Init(1999,71);
		TIM4_CH1_PWM_Init(1999,719);
    LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
    NRF24L01_Init();    		//��ʼ��NRF24L01 

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
            tmp_buf[32] = 0;//�����ַ���������
            decode= (tmp_buf[0]-48)*1000+(tmp_buf[1]-48)*100+(tmp_buf[2]-48)*10+(tmp_buf[3]-48);
            switch (decode)
            {

            case 1111://�������
                if(index1!=1)
                {
									 MainDGo();
                    index1=1;
                }
                break;

            case 2222://��С����
                if(index1!=2)
                {
									MainStop();
                    index1=2;
                }
                break;

            case 3333://�����D��ǰ��

                if(index2!=3)
                {
                    MainDGo();
                    index2=3;
                }
                break;
								
								case 3322://�����C��ǰ��

                if(index2!=4)
                {
                    MainCGo();
                    index2=4;
                }
                break;

            case 4444://�����B��ǰ��

                if(index2!=5)
                {
                    MainBGo();
                    index2=5;
                }
                break;
								
					  case 4422://�����A��ǰ��

                if(index2!=6)
                {
                    MainAGo();
                    index2=6;
                }
                break;

            case 5555://�����A�ٺ���

                if(index2!=7)
                {
                    MainABack();
                    index2=7;
                }
                break;
								case 5522://�����B�ٺ���

                if(index2!=8)
                {
                    MainBBack();
                    index2=8;
                }
                break;

            case 6666://�����C�ٺ���

                if(index2!=9)
                {
                    MainCBack();
                    index2=9;;
                }
                break;
						case 6622://�����D�ٺ���

                if(index2!=10)
                {
                    MainDBack();
                    index2=10;
                }
                break;

            case 7777://�����ͣ

                if(index2!=11)
                {
                    MainStop();
                    index2=11;
                }
                break;

            case 1122://����ת

                if(index!=8)
                {
                    
									Left();
                    index=8;
                }
                break;

            case 1133://����ת

                if(index!=9)
                {
             MidLeft();
                    index=9;
                }
                break;

            case 1144://����ת

                if(index!=10)
                {
              MidRight();
                    index=10;
                }
                break;

            case 1155://����ת

                if(index!=11)
                {
             
									Right();
                    index=11;
                }
                break;  
            case 2266://�������

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
            if (t == 20000)//��Լ1s�Ӹı�һ��״̬
            {
                t = 0;
                LED0 = !LED0;
            }

        }
    }
}


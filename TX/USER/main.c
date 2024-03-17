#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "nRF24L01_API.h"
#include "adc.h"
#include "time.h"
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
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
    LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
    KEY_Init();
    NRF24L01_Init();    		//��ʼ��NRF24L01 			//��������Ϊ��ɫ
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
        }//�������
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
        }//�������
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
        }//�����D��ǰ��
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
        }//�����C��ǰ��
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
        }//�����B��ǰ��
				
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
        }//�����A��ǰ��
				
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
        }//�����A�ٺ���

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
        }//�����B�ٺ���

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
        }//�����C�ٺ���

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
        }//�����D�ٺ���

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
        }//�����ͣ


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
        }//����ת
				
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
        }//����ת
				
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
        }//����ת
				
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
        }//����ת

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
        }//�������			
    }
}



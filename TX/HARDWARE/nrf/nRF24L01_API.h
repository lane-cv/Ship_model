#ifndef __nRF24L01_API_H
#define __nRF24L01_API_H

#include "nRF24L01.h"
#include "stm32f10x.h"


//nrf24l01����
#define NRF24L01_CE   PAout(2) //24L01Ƭѡ�ź�
#define NRF24L01_CSN  PAout(4) //SPIƬѡ�ź�      
#define NRF24L01_IRQ  PAin(1)  //IRQ������������

//24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5       //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5       //5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32      //32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32      //32�ֽڵ��û����ݿ��

void NRF24L01_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
u8 NRF24L01_Write_Reg(u8 reg,u8 value);
u8 NRF24L01_Read_Reg(u8 reg);
void NRF24L01_RX_Mode(u8* Address);
void NRF24L01_TX_Mode(u8* Address);
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len);
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);
u8 NRF24L01_TxPacket(u8 *txbuf);
u8 NRF24L01_RxPacket(u8 *rxbuf);
u8 NRF24L01_Check(void);

#endif

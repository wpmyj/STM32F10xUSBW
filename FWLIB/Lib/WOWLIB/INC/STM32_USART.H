/******************************** User_library *********************************
* �ļ��� 	: STM32_SDCard.H
* ����   	: wegam@sina.com
* �汾   	: V
* ����   	: 2016/01/01
* ˵��   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#ifndef __STM32_USART_H
#define __STM32_USART_H

#include	"stdio.h"			//����printf
#include	"string.h"			//����printf
#include	"stdarg.h"			//���ڻ�ȡ��ȷ�������Ĳ���
#include	"stdlib.h"			//malloc��̬�����ڴ�ռ�

//#include "stm32f10x_dma.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_usart.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_rcc.h"
//#include "STM32_WOW.H"
//#include "STM32_GPIO.H"

#include "stm32f10x_type.h"
#include "stm32f10x_usart.h"

//#define	USART1_ENABLE			//��������1
//#define	USART1_IDLE				//��������1���տ����ж�

//#ifdef	USART1_IDLE				//��������1���տ����ж�
//	#define	USART1_DMA				//��������1 DMA�շ�
//	#define	DMA1_BufferSize 1024		//DMA1�����С
//#endif

//#define	USE_USART1 1
//#define	USE_USART2 2
//#define	USE_USART3 3
//#define	USE_UART4 4
//#define	USE_UART5 5


extern char *USART_BUFFER;
extern u32	USART_BUFFERSIZE;
//typedef struct
//{
//	u32	USART_BUFFERSIZE;
//}USART_BUFFERSIZE_TypeDef;
//typedef enum USARTSELECT
//{
//	USE_USART1=1,
//	USE_USART2,
//	USE_USART3,
//	USE_UART4,
//	USE_UART5
//}USARTSELECT_TypeDef;
//EXAMPLE
//USART_Configuration(USART1,19200,8,1,0);


void USART_BASIC_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority);	//��������
void USART_DMA_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority,u32 *RXDBuffer,u32 *TXDBuffer,u32 BufferSize);	//USART_DMA����
void USART_Set(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority);				//���ݴ��ں�����������źͷ����ж��ź�Դ
int USART_DMAPrintf(USART_TypeDef* USARTx,const char *format,...);		//��ߵ�ʡ�Ժž��ǿɱ����
int USART_DMASend(USART_TypeDef* USARTx,u32 *tx_buffer,u16 BufferSize);		//�Զ���printf����DMA���ͳ���
u32 USART_RX_FlagClearADDR(USART_TypeDef* USARTx,u32 *RXDBuffer);				//������ڽ����жϱ�־--����ַ
u32 USART_RX_FlagClear(USART_TypeDef* USARTx);											//������ڽ����жϱ�־--���ض�ȡ�����ݸ���
ErrorStatus USART_TX_DMAFlagClear(USART_TypeDef* USARTx);						//�������DMA����ȫ���жϱ�־

void USART_RX_Server(void);		//���ڽ��շ������	



#endif

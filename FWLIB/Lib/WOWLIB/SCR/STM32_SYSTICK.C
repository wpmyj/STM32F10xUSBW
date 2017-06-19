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


#include "STM32_SYSTICK.H"
#include "STM32_WOW.H"
//#include "STM32F10x_BitBand.H"


/*******************************************************************************
* ������		:	SysTick_Configuration
* ��������	:	ϵͳ���ʱ������72MHz,��λΪuS
* ����		:	0<Time<= 1C71C7(1864135)
* ���		:
* ���� 		:
*******************************************************************************/
void SysTick_Configuration(unsigned long Time)	//ϵͳ���ʱ������72MHz,��λΪuS
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);					//ϵͳʱ�� 72MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//ϵͳʱ��/8==9MHz
//	SysTick_SetReload(9);			//1uS
	SysTick_SetReload(9*Time);				//Time--uS
	SysTick_ITConfig(ENABLE);
	SysTick_CounterCmd(SysTick_Counter_Enable);	//ʹ�ܼ���
	SysTick_ITConfig(ENABLE);
}
/*******************************************************************************
* ������		:	SysTick_Server
* ��������	:	���ʱ�ӷ���
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SysTick_Server(void)				//���ʱ�ӷ���
{
	WOW_Server();	
}



/******************************** User_library *********************************
* �ļ��� 	: SPI_FLASH.C
* ����   	: wegam@sina.com
* �汾   	: V
* ����   	: 2017/04/16
* ˵��   	: 
********************************************************************************
SPI_FLASHʹ�ù��ܲ���
1����Ҫ�궨�� SPI_FLASH
2��ʹ��USB_TEST �����
3����Ҫ�궨��SPI����

*******************************************************************************/
#include "STM32_A3987.H"

//#define USB_TEST_BD				//USB_TEST��
//#define CMSIS_CDC_BD			//CMSIS-CDC��

//#include "stm32f10x_spi.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_dma.h"
////#include "stm32f10x_nvic.h"

////#include "STM32_WOW.H"
//#include "STM32_PWM.H"
//#include "STM32_SYS.H"

/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void A3987_GPIO_Configuration(void)
{
	//�ṹ�嶨��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����Ӧ�ܽ�ʱ��
	A3987_EN_CLOCK(ENABLE);		//A3987_EN
	A3987_PUL_CLOCK(ENABLE);	//A3987_PUL
	A3987_DIR_CLOCK(ENABLE);	//A3987_DIR
	A3987_MS1_CLOCK(ENABLE);	//A3987_MS1
	A3987_MS2_CLOCK(ENABLE);	//A3987_MS2
	
	//A3987_EN�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=A3987_EN_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(A3987_EN_PORT,&GPIO_InitStructure);
	//A3987_PUL�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=A3987_PUL_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;					//GPIO_Mode_IPU			//GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(A3987_PUL_PORT,&GPIO_InitStructure);
	//A3987_DIR�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=A3987_DIR_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(A3987_DIR_PORT,&GPIO_InitStructure);
	//A3987_MS1�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=A3987_MS1_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//GPIO_Mode_Out_PP  //GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(A3987_MS1_PORT,&GPIO_InitStructure);
	//A3987_MS2�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=A3987_MS2_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//GPIO_Mode_Out_PP  //GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(A3987_MS2_PORT,&GPIO_InitStructure);
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void A3987_SETUP(void)
{
	A3987_EN_ENABLE();
	A3987_DIR_HIGH();
	A3987_MS1_LOW();
	A3987_MS2_LOW();
}







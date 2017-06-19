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
#ifdef SPI_FLASH							//���������SPI_FLASH �˹�����Ч
#include "SPI_FLASH.H"

//#define USB_TEST_BD				//USB_TEST��
#define CMSIS_CDC_BD			//CMSIS-CDC��

#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
//#include "stm32f10x_nvic.h"

//#include "STM32_WOW.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"



#if	defined(USB_TEST_BD)
	//SPI�ӿڶ���
	#define SPI_FLASH_RCC													RCC_APB1Periph_SPI2
	#define SPI_FLASH_SPI_PORT										SPI2
	#define SPI_FLASH_CLOCK(FunctionalState)			RCC_APB1PeriphClockCmd(SPI_FLASH_RCC, FunctionalState)

	//MOSI�ܽŶ���
	#define SPI_FLASH_MOSI_RCC			RCC_APB2Periph_GPIOB
	#define	SPI_FLASH_MOSI_PORT			GPIOB
	#define	SPI_FLASH_MOSI_PIN			GPIO_Pin_15
	#define SPI_FLASH_MOSI_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MOSI_RCC, FunctionalState)
	//MISO�ܽŶ���
	#define SPI_FLASH_MISO_RCC			RCC_APB2Periph_GPIOB
	#define	SPI_FLASH_MISO_PORT			GPIOB
	#define	SPI_FLASH_MISO_PIN			GPIO_Pin_14
	#define SPI_FLASH_MISO_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MISO_RCC, FunctionalState)
	//SCLK�ܽŶ���
	#define SPI_FLASH_SCLK_RCC			RCC_APB2Periph_GPIOB
	#define	SPI_FLASH_SCLK_PORT			GPIOB
	#define	SPI_FLASH_SCLK_PIN			GPIO_Pin_13
	#define SPI_FLASH_SCLK_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_SCLK_RCC, FunctionalState)
	//NSS�ܽŶ���
	#define SPI_FLASH_NSS_RCC				RCC_APB2Periph_GPIOC
	#define	SPI_FLASH_NSS_PORT			GPIOC
	#define	SPI_FLASH_NSS_PIN				GPIO_Pin_8
	#define SPI_FLASH_NSS_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_NSS_RCC, FunctionalState)

	#define	SPI_FLASH_CS_ENABLE		PC8=0
	#define	SPI_FLASH_CS_DISABLE	PC8=1
	
#elif	defined(CMSIS_CDC_BD)

	//SPI�ӿڶ���
	#define SPI_FLASH_RCC													RCC_APB2Periph_SPI1
	#define SPI_FLASH_SPI_PORT										SPI1
	#define SPI_FLASH_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_RCC, FunctionalState)

	//MOSI�ܽŶ���
	#define SPI_FLASH_MOSI_RCC			RCC_APB2Periph_GPIOA
	#define	SPI_FLASH_MOSI_PORT			GPIOA
	#define	SPI_FLASH_MOSI_PIN			GPIO_Pin_7
	#define SPI_FLASH_MOSI_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MOSI_RCC, FunctionalState)
	//MISO�ܽŶ���
	#define SPI_FLASH_MISO_RCC			RCC_APB2Periph_GPIOA
	#define	SPI_FLASH_MISO_PORT			GPIOA
	#define	SPI_FLASH_MISO_PIN			GPIO_Pin_6
	#define SPI_FLASH_MISO_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MISO_RCC, FunctionalState)
	//SCLK�ܽŶ���
	#define SPI_FLASH_SCLK_RCC			RCC_APB2Periph_GPIOA
	#define	SPI_FLASH_SCLK_PORT			GPIOA
	#define	SPI_FLASH_SCLK_PIN			GPIO_Pin_5
	#define SPI_FLASH_SCLK_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_SCLK_RCC, FunctionalState)
	//NSS�ܽŶ���
	#define SPI_FLASH_NSS_RCC				RCC_APB2Periph_GPIOA
	#define	SPI_FLASH_NSS_PORT			GPIOA
	#define	SPI_FLASH_NSS_PIN				GPIO_Pin_4
	#define SPI_FLASH_NSS_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_NSS_RCC, FunctionalState)

	#define	SPI_FLASH_CS_ENABLE		PA4=0
	#define	SPI_FLASH_CS_DISABLE	PA4=1	
#else
	#error "Board undefined"
#endif

u32 Temp = 0;

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SPI_FLASH_Configuration(void)
{
	SYS_Configuration();											//ϵͳ���� STM32_SYS.H	
	PWM_Configuration(TIM2,7200,10000,50);		//����ָʾ������
	SPI_FLASH_GPIO_Configuration();						//��Ӧ�ܽ�����
	SPI_FLASH_SpiPort_Configuration();				//SPI�ӿ�����	
	SysTick_Configuration(5000);							//ϵͳ���ʱ������72MHz,��λΪuS
}

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SPI_FLASH_Server(void)
{
	if(Temp!=0)
	{
		Temp=0;
//		SPI_FLASH_CS_ENABLE;
//		SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
		SPI_FLASH_ReadID();
	}
	else
	{
		Temp=1;
//		SPI_FLASH_CS_DISABLE;
//		SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
	}
//	Temp=0;
//	Temp=SPI_FLASH_ReadID();
	
//	SPI_FLASH_CS_ENABLE;
//	SPI_FLASH_SendByte(0x9F);
//	SPI_FLASH_CS_DISABLE;
//	u16 num=0xFFFE;
//	SPI_Cmd(SPI1, ENABLE);
	/*
	//1��********SPI����
	if(SPI1_NSS==SPI_NSS_Hard)		//1��**********NSSƬѡ��ʽΪӲ����ʽ��SPI_NSS_Hard��ʱ��������
	{
		SPI_Cmd(SPI1, ENABLE);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1,0X55);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
		SPI_Cmd(SPI1, DISABLE);
	}
	else				//2��**********NSSƬѡ��ʽΪ��������ʽ��SPI_NSS_Soft��ʱ��������
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1,0X55);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
	//1.2��********SPI2����
	if(SPI2_NSS==SPI_NSS_Hard)		//1��**********NSSƬѡ��ʽΪӲ����ʽ��SPI_NSS_Hard��ʱ��������
	{	
		SPI_Cmd(SPI2, ENABLE);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2,0XAA);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);
		SPI_Cmd(SPI2, DISABLE);
	}
	else													//2��**********NSSƬѡ��ʽΪ��������ʽ��SPI_NSS_Soft��ʱ��������
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2,0XAA);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	*/


//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//		SPI_I2S_SendData(SPI1,0X55);
//		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
//		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		
		
//	SPI_TX_DMAFlagClear(SPI1);
	//2��********SPI_DMA����

//		SPI_Buffer
//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		SPI_Cmd(SPI1, ENABLE);
////		SPI_DMAPrintf(SPI1,"%d",num);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		//SPI_DMAPrintf(SPI1,"%s",SPI_Buffer);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		SPI_DMA_BufferWrite(SPI1,(u32*)SPI_Buffer,10);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		while(SPI_TX_DMAFlagClear(SPI1)==ERROR);
//		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//		SPI_Cmd(SPI1, DISABLE);
//		free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
//		GPIO_SetBits(GPIOA,GPIO_Pin_4);
//		
////		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
//		SPI_Cmd(SPI2, ENABLE);
////		SPI_DMAPrintf(SPI1,"%d",num);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		//SPI_DMAPrintf(SPI1,"%s",SPI_Buffer);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		SPI_DMA_BufferWrite(SPI2,(u32*)SPI_Buffer,10);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//		while(SPI_TX_DMAFlagClear(SPI2)==ERROR);
//		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
//		SPI_Cmd(SPI2, DISABLE);
//		free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
//		GPIO_SetBits(GPIOB,GPIO_Pin_12);


//	free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void SPI_FLASH_GPIO_Configuration(void)
{
	//�ṹ�嶨��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����Ӧ�ܽ�ʱ��
	SPI_FLASH_MOSI_CLOCK(ENABLE);
	SPI_FLASH_MISO_CLOCK(ENABLE);
	SPI_FLASH_SCLK_CLOCK(ENABLE);
	SPI_FLASH_NSS_CLOCK(ENABLE);
	
	//MOSI�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_MOSI_PORT,&GPIO_InitStructure);
	//MISO�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//GPIO_Mode_IPU			//GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_MISO_PORT,&GPIO_InitStructure);
	//SCLK�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_SCLK_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_SCLK_PORT,&GPIO_InitStructure);
	//NSS�ܽŶ���
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_NSS_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//GPIO_Mode_Out_PP  //GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_NSS_PORT,&GPIO_InitStructure);
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void SPI_FLASH_SpiPort_Configuration(void)
{
	//�ṹ�嶨��
	SPI_InitTypeDef	SPI_InitStructure;
	//��SPIʱ��
	SPI_FLASH_CLOCK(ENABLE);
	SPI_Cmd(SPI_FLASH_SPI_PORT,DISABLE);
	//����SPI����
	SPI_InitStructure.SPI_Direction						=		SPI_Direction_2Lines_FullDuplex;	//���÷���				��2��ȫ˫����2��ֻ���ա�һ�߷��͡�һ�߽��գ�
	SPI_InitStructure.SPI_Mode								=		SPI_Mode_Master;									//ģʽ         	���ӻ����豸��
	SPI_InitStructure.SPI_DataSize						=		SPI_DataSize_8b;									//����         	��8��16λ��
	SPI_InitStructure.SPI_CPOL								=		SPI_CPOL_High;										//ʱ�Ӽ���     	���ͻ�ߣ�
	SPI_InitStructure.SPI_CPHA								=		SPI_CPHA_2Edge;					 					//ʱ����λ     	����һ����ڶ��������أ�
	SPI_InitStructure.SPI_NSS									=		SPI_NSS_Hard;											//Ƭѡ��ʽ     	��Ӳ����������ʽ��
	SPI_InitStructure.SPI_BaudRatePrescaler		=		SPI_BaudRatePrescaler_8;					//������Ԥ��Ƶ 	����2---256��Ƶ��
	SPI_InitStructure.SPI_FirstBit						=		SPI_FirstBit_MSB;									//���ȷ��͵�λ 	�����λ���������λ���ȣ�
	SPI_InitStructure.SPI_CRCPolynomial				=		0X07;															//����crc����ʽ �����֣���7
	//��ʼ��SPI
	SPI_Init(SPI_FLASH_SPI_PORT,&SPI_InitStructure);
	//���������ģʽ�µ�Ƭѡ��ʽΪӲ����SPI_NSS_Hard����ʽ���˴�����򿪣�����NSS���ź�
	SPI_SSOutputCmd(SPI_FLASH_SPI_PORT, ENABLE);		
	//ʹ��SPI
	SPI_Cmd(SPI_FLASH_SPI_PORT,ENABLE);
	
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
u8 SPI_FLASH_SendByte(u8 byte)
{
  /* �ȴ�DR�Ĵ����� */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);
	 
  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH_SPI_PORT, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI_FLASH_SPI_PORT);
}

/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
u32 SPI_FLASH_ReadID(void)
{
	u32 Temp = 0,Temp0=0,Temp1=0,Temp2=0;

  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	SPI_FLASH_CS_ENABLE;
	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
  /* Send "RDID " instruction */
  SPI_FLASH_SendByte(0x9F);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
  /* Read a byte from the FLASH */
  Temp0 = SPI_FLASH_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp1 = SPI_FLASH_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp2 = SPI_FLASH_SendByte(0X01);

  /* Deselect the FLASH: Chip Select high */
//  SPI_FLASH_CS_HIGH();
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
	SPI_FLASH_CS_DISABLE;
  return Temp;	
}







































#endif
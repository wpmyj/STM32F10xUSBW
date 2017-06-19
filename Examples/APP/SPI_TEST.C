#ifdef SPI_TEST
#include "SPI_TEST.H"



#define SPI_BufferSize 16
u8 SPI_Buffer[SPI_BufferSize]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A};
SPI_InitTypeDef  SPI_InitStructure;
u16 SPI1_NSS=0;
u16 SPI2_NSS=0;
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SPI_TEST_Configuration(void)
{
//	TIM_Configuration(TIM3,7200,500);						//��ʱʱ���趨
	PWM_Configuration(TIM2,7200,10000,50);
	SPI_StructConf(&SPI_InitStructure);
//	SPI_BASIC_Configuration(SPI1,&SPI_InitStructure);						//SPI����
	
	SPI_DMA_Configuration(SPI1,&SPI_InitStructure,(u32*)SPI_Buffer,(u32*)SPI_Buffer,SPI_BUFFERSIZE);		//SPI_DMA����
	SPI_DMA_Configuration(SPI2,&SPI_InitStructure,(u32*)SPI_Buffer,(u32*)SPI_Buffer,SPI_BUFFERSIZE);		//SPI_DMA����

	if((SPI1->CR1&0X0200)==SPI_NSS_Soft)						//���������ģʽ�µ�Ƭѡ��ʽΪӲ����SPI_NSS_Hard����ʽ���˴�����򿪣�����NSS���ź�
	{
		SPI1_NSS=SPI_NSS_Soft;
	}
	else
	{
		SPI1_NSS=SPI_NSS_Hard;
	}
	if((SPI2->CR1&0X0200)==SPI_NSS_Soft)						//���������ģʽ�µ�Ƭѡ��ʽΪӲ����SPI_NSS_Hard����ʽ���˴�����򿪣�����NSS���ź�
	{
		SPI2_NSS=SPI_NSS_Soft;
	}
	else
	{
		SPI2_NSS=SPI_NSS_Hard;
	}
//	SPI1_NSS=SPI_NSS_Soft;

}

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SPI_TEST_Server(void)
{
	u16 num=0xFFFE;
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
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		SPI_Cmd(SPI1, ENABLE);
//		SPI_DMAPrintf(SPI1,"%d",num);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		//SPI_DMAPrintf(SPI1,"%s",SPI_Buffer);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		SPI_DMA_BufferWrite(SPI1,(u32*)SPI_Buffer,10);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		while(SPI_TX_DMAFlagClear(SPI1)==ERROR);
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_Cmd(SPI1, DISABLE);
		free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		SPI_Cmd(SPI2, ENABLE);
//		SPI_DMAPrintf(SPI1,"%d",num);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		//SPI_DMAPrintf(SPI1,"%s",SPI_Buffer);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		SPI_DMA_BufferWrite(SPI2,(u32*)SPI_Buffer,10);		//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
		while(SPI_TX_DMAFlagClear(SPI2)==ERROR);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_Cmd(SPI2, DISABLE);
		free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
//		GPIO_SetBits(GPIOB,GPIO_Pin_12);


//	free(SPI_BUFFER);						//�ͷŶ�̬�ռ�
}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SPI_StructConf(SPI_InitTypeDef* SPI_InitStruct)
{
//	SPI4->GPIO_NSS	=	GPIOA;
//	SPI4->SPI_NSSP	=	GPIO_Pin_4;
//	SPI4->GPIO_SCK	=	GPIOA;
//	SPI4->SPI_SCKP	=	GPIO_Pin_5;
//	SPI4->GPIO_MISO	=	GPIOA;
//	SPI4->SPI_MISOP	=	GPIO_Pin_6;
//	SPI4->GPIO_MOSI	=	GPIOA;
//	SPI4->SPI_MOSIP	=	GPIO_Pin_71;	
	
	SPI_InitStruct->SPI_Direction=SPI_Direction_2Lines_FullDuplex;			//���÷���				��2��ȫ˫����2��ֻ���ա�һ�߷��͡�һ�߽��գ�
	SPI_InitStruct->SPI_Mode=SPI_Mode_Master;														//ģʽ         	���ӻ����豸��
	SPI_InitStruct->SPI_DataSize=SPI_DataSize_8b;												//����         	��8��16λ��
	SPI_InitStruct->SPI_CPOL=SPI_CPOL_High;															//ʱ�Ӽ���     	���ͻ�ߣ�
	SPI_InitStruct->SPI_CPHA=SPI_CPHA_2Edge;														//ʱ����λ     	����һ����ڶ��������أ�
//	SPI_InitStruct->SPI_NSS=SPI_NSS_Soft;																//Ƭѡ��ʽ     	��Ӳ����������ʽ��
	SPI_InitStruct->SPI_NSS=SPI_NSS_Hard;																//Ƭѡ��ʽ     	��Ӳ����������ʽ��
	SPI_InitStruct->SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;			//������Ԥ��Ƶ 	����2---256��Ƶ��
	SPI_InitStruct->SPI_FirstBit=SPI_FirstBit_MSB;											//���ȷ��͵�λ 	�����λ���������λ���ȣ�
	SPI_InitStruct->SPI_CRCPolynomial=0X07;															//����crc����ʽ	���临λֵΪ0x0007������Ӧ�ÿ�������������ֵ����
}




#endif
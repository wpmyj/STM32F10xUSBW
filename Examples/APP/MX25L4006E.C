#ifdef MX25L4006E

#include "MX25L4006E.H"




/*##############################################################################
################################################################################

********************************************************************************

################################################################################
##############################################################################*/


/******************************MX25L4006E�����*******************************/
#define	MX25L4006E_WREN		(unsigned char)0x06				//дʹ��
#define	MX25L4006E_WRDI		(unsigned char)0x04				//дʧ��
#define	MX25L4006E_WRSR		(unsigned char)0x01				//д״̬�Ĵ���
#define	MX25L4006E_RDID		(unsigned char)0x9F				//���豸��Ϣ��3byte����һ�ֽ�Ϊ�����̴��룬�ڶ������ֽ�ΪоƬ����
#define	MX25L4006E_RDSR		(unsigned char)0x05				//��״̬�Ĵ���
#define	MX25L4006E_READ		(unsigned char)0x06				//������
#define	MX25L4006E_FREAD	(unsigned char)0x06				//���ٶ�ȡ����
#define	MX25L4006E_RDSFDP	(unsigned char)0x5A				//
#define	MX25L4006E_RES		(unsigned char)0xAB				//��������ַ
#define	MX25L4006E_REMS		(unsigned char)0x90				//�������̴���Ͳ�Ʒ����
#define	MX25L4006E_DREAD	(unsigned char)0x3B				//
#define	MX25L4006E_SE			(unsigned char)0x20				//��������
#define	MX25L4006E_BE			(unsigned char)0x52				//�����		Ҳ������0XD8
#define	MX25L4006E_CE			(unsigned char)0x60				//оƬ����; ��Ƭ����; Ҳ������0XC7
#define	MX25L4006E_PP			(unsigned char)0x02				//дҳ��
#define	MX25L4006E_DP			(unsigned char)0xB9				//���ʡ��״̬
#define	MX25L4006E_RDP		(unsigned char)0xAB				//�˳���ȵ���

		



//SPI_ConfTypeDef *SPI4;

//#define	SPI4_NSSP GPIO_Pin_4


#define	SPI_BUFFERSIZE	10

char SPI_TX_Buffer[SPI_BUFFERSIZE]={0X90,0X0F,0X0A,0X00};
char SPI_RX_Buffer[SPI_BUFFERSIZE]={0};

SPI_InitTypeDef  SPI_InitStructure;


vu32 FLASH_ID = 0;

u32 Temp = 0,Temp0=0,Temp1=0,Temp2=0;		//����

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void MX25L4006E_Configuration(void)
{
	SPI_StructConf(&SPI_InitStructure);										//���ò���
	
//	SPI_BASIC_Configuration(SPI1,&SPI_InitStructure);			//SPI��������
	
	SPI_DMA_Configuration(SPI1,&SPI_InitStructure,(u32*)SPI_TX_Buffer,(u32*)SPI_RX_Buffer,SPI_BUFFERSIZE);				//SPI_DMA����
	
	PWM_Configuration(TIM2,7200,5000,50);	
	
//	SPIT_Configuration(SPI1);							//SPI����ʹ�÷�ʽ����
//	SPI_Cmd(SPI1, ENABLE);
//	SPI_I2S_ReceiveData(SPI1);


}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void MX25L4006E_Server(void)
{
//	if(Temp==0)
//		MX25L4006E_ReadID();
//	SPI_DMA_BufferRead((u32*)SPI_RX_Buffer);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	SPI_DMASend(SPI1,(u32*)SPI_TX_Buffer,(u32*)SPI_RX_Buffer,SPI_BUFFERSIZE);	//SPI_DMA���ͺ���----��ߵ�ʡ�Ժž��ǿɱ����
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);	
//	SPI_Cmd(SPI1, ENABLE);
	SPI_DMA_ReceiveSendByte(SPI1,8);		//DMA�շ�����
//	SPI_Cmd(SPI1, DISABLE);
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
	SPI_InitStruct->SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;			//������Ԥ��Ƶ 	����2---256��Ƶ��
	SPI_InitStruct->SPI_FirstBit=SPI_FirstBit_MSB;											//���ȷ��͵�λ 	�����λ���������λ���ȣ�
	SPI_InitStruct->SPI_CRCPolynomial=0X07;															//����crc����ʽ	���临λֵΪ0x0007������Ӧ�ÿ�������������ֵ����
}
/*******************************************************************************
*������			:	MX25L4006E_WriteEnable
*��������		:	дʹ��
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
*******************************************************************************/
void MX25L4006E_WriteEnable(void)		//MX25L4006Eдʹ������
{
	SPI_Cmd(SPI1, ENABLE);
	SPI_I2S_SendData(SPI1,MX25L4006E_WREN);
	SPI_Cmd(SPI1, DISABLE);
}
/*******************************************************************************
*������			:	function
*��������		:	�ȴ�����ִ�н���
							ִ��дʹ�ܻ�ֵλ״̬�Ĵ����е�BUSYλ��ֻ��BUSYλ��Ϊ0ʱ˵��дʹ������ִ�����
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
*******************************************************************************/
void MX25L4006E_WaitForWriteEnd(void)		//�ȴ�����ִ�н���
{
	u8  FLASH_Status = 0;
  //1)**********ʹ��оƬ
	SPI_Cmd(SPI1, ENABLE);
  //2)**********���Ͷ�ȡ״̬�Ĵ�������
	SPI_SendByte(0X05);
  //3)**********��ȡ״̬�Ĵ���ֱ�����
	do
	{
    //3.0)**********�������⣨���⣩���ݣ���ȡ״̬
		FLASH_Status = SPI_SendByte(0x00);
	}
  while ((FLASH_Status & 0X01) == SET); 
	SPI_Cmd(SPI1, DISABLE);
}
/*******************************************************************************
*������			:	function
*��������		:	��������//��д������ǰ��Ҫ��оƬ���в�����
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
*******************************************************************************/
void MX25L4006E_SectorErase(void)		//��������
{
	//1)**********����дʹ������
	MX25L4006E_WriteEnable();				//MX25L4006Eдʹ������
	//2)**********ʹ��д������һ��д״̬�Ĵ������������Ҫ�ȴ�������ִ���꣬����д��������
	MX25L4006E_WaitForWriteEnd();		//�ȴ�����ִ�н���
	//3)**********��������
	//3.1)**********����дʹ������
	SPI_Cmd(SPI1, ENABLE);
	//3.2)**********���Ͳ�����������
	SPI_SendByte(0X20);
	//3.3)**********����Ҫ��������ʼ��ַ

}

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void MX25L4006E_COMMAND(unsigned char Command)
{

}

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
u32 MX25L4006E_ReadID(void)
{
//	u32 Temp = 0,Temp0=0,Temp1=0,Temp2=0;

  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);

	SPI_Cmd(SPI1, ENABLE);
  /* Send "RDID " instruction */
  SPI_SendByte(0x9F);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
  /* Read a byte from the FLASH */
  Temp0 = SPI_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp1 = SPI_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp2 = SPI_SendByte(0X01);

  /* Deselect the FLASH: Chip Select high */
//  SPI_FLASH_CS_HIGH();
	GPIO_SetBits(GPIOA,GPIO_Pin_4);

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	SPI_Cmd(SPI1, DISABLE);
  return Temp;	
}

#endif


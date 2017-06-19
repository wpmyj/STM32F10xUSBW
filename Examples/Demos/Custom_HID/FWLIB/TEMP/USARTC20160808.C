#include "USARTH20160808.H"

//u8 Usart_Buffer[32]={0};
//ѡ�񴮿ڿ���

/*****************************USART DMA��ʽ�շ������ù���*******************************/
//****1.RCC����λ��ʱ�ӿ��ƼĴ�������ʼ��������GPIO��DMA��USARTʱ�ӡ�********************/ 
//****2.NVIC��Ƕ�������жϿ��ƼĴ�������ʼ������ɸ���Ӳ���жϵ����á�********************/
//****3.USART��ʼ�������ô��ڣ�����DMAͨ���ȡ�********************/ 
//****4.DMA��ʼ�������DMA�����á�********************/

//#define USE_USART USARTSELECT_TypeDef*;
/*****************************USART DMA��ʽ�շ������ù���*******************************/
/*******************************************************************************
*������		: USART_Configuration
*��������	:��������
*����			:���ں�	--USARTx��USART1/USART2/USART3/UART4/UART5
					������	--USART_BaudRate
					�ֳ�		--USART_WordLength
					ֹͣλ	--USART_StopBits
					��żУ��-USART_Parity
*���			:��
*����ֵ		:��
*����			��USART_Configuration(USART1,19200,8,1,0);
*******************************************************************************/
void USART_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u16 USART_WordLength,u16 USART_StopBits,u16 USART_Parity)	//��������
{
	GPIO_InitTypeDef GPIO_InitStructure;				//GPIO�ṹ��
	USART_InitTypeDef USART_InitStructure;				//USART�ṹ��
	NVIC_InitTypeDef NVIC_InitStructure; 				//NVIC�ṹ��
	
	u16 TXD_Pin=0;																//���ڷ��ͽ�
	u16 RXD_Pin=0;																//���ڽ��ս�
	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
	u8 USARTx_IRQChannel=0;
//	USART_TypeDef* USARTx=0;
//	USART=USART1;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1ʱ�ӿ���
//	u32 RCC_USART_GPIO_Periph;
//	DMA_InitTypeDefDMA_Initstructure;
//>>>>>>>>>>>>>>>>>>>>>��ʼ������-��ʼ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//	switch(USART)
//	{
//(*(u32*)&USARTx);
//	}
	if(USARTx==USART1)
	{
		TXD_Pin=GPIO_Pin_9;		//USART1-TX>PA9
		RXD_Pin=GPIO_Pin_10;	//USART1-RX>PA10
		
		GPIO_TX=GPIOA;
		GPIO_RX=GPIOA;
		
		USARTx_IRQChannel=USART1_IRQChannel;		//�ж�
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1ʱ�ӿ���

	}
	else if(USARTx==USART2)
	{
		TXD_Pin=GPIO_Pin_2;		//USART2-TX>PA2
		RXD_Pin=GPIO_Pin_3;		//USART2-RX>PA3
		
		GPIO_TX=GPIOA;
		GPIO_RX=GPIOA;
		
		USARTx_IRQChannel=USART2_IRQChannel;		//�ж�
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//USART1ʱ�ӿ���

	}
	else if(USARTx==USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//�ر�AFIOʱ��,Ϊ�ر�JTAG����
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //�ر�JTAG����
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  		//�ر�SWD����
		
		
		TXD_Pin=GPIO_Pin_10;	//USART3-TX>PB10
		RXD_Pin=GPIO_Pin_11;	//USART3-RX>PB11
		
		GPIO_TX=GPIOB;
		GPIO_RX=GPIOB;
		
		USARTx_IRQChannel=USART3_IRQChannel;		//�ж�
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//USART1ʱ�ӿ���
		

	}
	else if(USARTx==UART4)
	{
		TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC10
		RXD_Pin=GPIO_Pin_11;	//USART1-RX>PC11
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOC;
		
		USARTx_IRQChannel=UART4_IRQChannel;		//�ж�
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//USART1ʱ�ӿ���

	}
	else if(USARTx==UART5)
	{
		TXD_Pin=GPIO_Pin_12;	//USART1-TX>PC12
		RXD_Pin=GPIO_Pin_2;		//USART1-RX>PD2
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOD;
		
		USARTx_IRQChannel=UART5_IRQChannel;		//�ж�
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//USART1ʱ�ӿ���
	}

//<<<<<<<<<<<<<<<<<<<<<��ʼ������-����<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//////////////GPIO����
	//����ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1ʱ�ӿ���
	//����TX�˿�
//	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TX,&GPIO_InitStructure);
	//����RX�˿�
//	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//��������
	GPIO_Init(GPIO_RX,&GPIO_InitStructure);

/////////////USART����////////////////////////////////////////////////
	//���ò���
	USART_InitStructure.USART_BaudRate = USART_BaudRate; 					//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ; 					//��żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����
	USART_Init(USARTx, &USART_InitStructure);											//��ʼ������
/////////////NVIC����////////////////////////////////////////////////

	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE);
//////////////����USART////////////
//	/* ʹ�ܴ���*/
//	USART_Cmd(USART1, ENABLE);

	/* �����߿��У������ж� */
	//���߿����ж����ڼ�⵽�ڽ������ݺ�����������һ���ֽڵ�ʱ���ڣ�û���ٽӵ����ݺ�����
	//Ҳ����RXNEλ����λ֮�󣬲ſ�ʼ��⣬ֻ����λһ�Σ������ٴμ�⵽RXNEλ����λ��Ȼ��ſ�ʼ�����һ�ε����߿���
	USART_ITConfig(USARTx,USART_IT_IDLE, ENABLE);

	/* �򿪴��ڽ����ж�*/
//	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);	//ʹ�ÿ����жϣ���˹��ܲ���

	/* ����DMA��ʽ����*/
	USART_DMACmd(USARTx,USART_DMAReq_Rx,ENABLE);
	/* ����DMA��ʽ����*/
	USART_DMACmd(USARTx,USART_DMAReq_Tx,ENABLE);

	/* ʹ�ܴ���*/
	USART_Cmd(USARTx, ENABLE);
}

/*******************************************************************************
*������		:USART_RX_Server
*��������	:���ڽ��շ�����
*����			: 
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/

void USART_RX_Server(void)		//���ڽ��շ������	
{
//	u16 num=0;
	WOW_Server(); 
//    if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)
//    {
////#ifdef	USART1_DMA
////		u16 num=0;
//		USART_ClearITPendingBit(USART1,USART_IT_IDLE); 				//������д��ڱ�־λ
////		USART_ClearITPendingBit(USART1,USART_IT_RXNE); 				//������д��ڱ�־λ
//		num = USART1->DR; 																		//������������������־
//		DMA_Cmd(DMA1_Channel5,DISABLE);    										//�رս���DMA
//		num = DMA1_BufferSize -  DMA_GetCurrDataCounter(DMA1_Channel5);  	//�õ������������ݸ���
//		DMA1_Channel4->CNDTR =num;														//�趨���������ݸ���
////		temp =num;   
////		data_uart1[num] = '\0';
//		DMA1_Channel5->CNDTR=DMA1_BufferSize;       				//�������ý������ݸ���
//			
//		DMA_Cmd(DMA1_Channel5,ENABLE);  										//��������DMA
//		DMA_Cmd(DMA1_Channel4,ENABLE);											//DMA���Ϳ���
////#endif
//		}
//			
//	if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)
//    {
//		USART_ClearITPendingBit(USART2,USART_IT_IDLE); 				//������д��ڱ�־λ
//		num = USART2->DR; 																		//������������������־
//		DMA_Cmd(DMA1_Channel6,DISABLE);    										//�رս���DMA
//		num = DMA1_BufferSize -  DMA_GetCurrDataCounter(DMA1_Channel6);  	//�õ������������ݸ���
//		DMA1_Channel7->CNDTR =num;														//�趨���������ݸ���
//		DMA1_Channel6->CNDTR=DMA1_BufferSize;       				//�������ý������ݸ���
//			
//		DMA_Cmd(DMA1_Channel6,ENABLE);  										//��������DMA			
//		DMA_Cmd(DMA1_Channel7,ENABLE);											//DMA���Ϳ���
//		}
}



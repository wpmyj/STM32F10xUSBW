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



#include "STM32_CAN.H"
//#include "STM32F10x_BitBand.H"

/*##############################################################################
################################################################################
# ģ����		:	STM32_CAN	
# ��������	:	CAN����ʹ��

-------------------------------------------------------------------------------	
********bxCAN��������:********
�ڵ����CANӦ���У�CAN����Ľڵ��ڲ������ӣ����Ҷ��CAN����ͨ�����������������������CAN���еı�������(ÿ���ڵ㶼��Ҫ����)�������ӡ�����Ӧ�ò㱨���⣬�����������ϱ���Ҳ�����롣
�� ��Ҫһ����ǿ�Ĺ��˻����������������͵ı���
���⣬Ӧ�ò�������Ҫ����CPUʱ�䣬��˱��Ľ��������ʵʱ��Ӧ�̶���Ҫ���ᡣ
�� ����FIFO�ķ���������CPU���ܳ�ʱ�䴦��Ӧ�ò���������ᶪʧ���ġ�
�����ڵײ�CAN���������ϵĸ߲�Э��������Ҫ���CAN������֮���и�Ч�Ľӿڡ�

********ǰ��:********
�� ��CANЭ������ĵı�ʶ���������ڵ�ĵ�ַ�����Ǹ����ĵ�������صġ���ˣ��������Թ㲥����ʽ�ѱ��ķ��͸����еĽ����ߡ��ڵ��ڽ��ձ���ʱ,���ݱ�ʶ��(CAN ID)��ֵ���������Ƿ���Ҫ�ñ��ģ������Ҫ���Ϳ�����SRAM��������Ҫ�����ľͱ����������������ĸ�Ԥ��
Ϊ������һ����bxCANΪӦ�ó����ṩ��14��λ���ɱ�ġ������õĹ�������(13~0)���Ա�ֻ������Щ������Ҫ�ı��ġ�Ӳ�����˵�������ʡ��CPU����������ͱ������������˴Ӷ�ռ��һ����CPU������ÿ����������x��2��32λ�Ĵ�����CAN_FxR0��CAN_FxR1��ɡ�
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------	
********bxCAN��Ҫ�ص�:********
bxCAN�ǻ�����չCAN(Basic Extended CAN)����д����֧��CANЭ��2.0A��2.0B���������Ŀ���ǣ�����С��CPU��������Ч���������յ��ı��ġ�
��Ҳ֧�ֱ��ķ��͵����ȼ�Ҫ��(���ȼ����Կ���������)��
���ڰ�ȫ��Ҫ��Ӧ�ã�bxCAN�ṩ����֧��ʱ�䴥��ͨ��ģʽ�����Ӳ�����ܡ�
-------------------------------------------------------------------------------
********CAN��Ҫ����:********
�� ֧��CANЭ��2.0A��2.0B����ģʽ
�� ��������߿ɴ�1��λ/��
�� ֧��ʱ�䴥��ͨ�Ź���
�����͡�
�� 3����������
�� ���ͱ��ĵ����ȼ����Կ���������
�� ��¼����SOFʱ�̵�ʱ���
�����ա�
�� 3����ȵ�2������FIFO
�� �ɱ�Ĺ������飺
	�� �ڻ����Ͳ�Ʒ�У�CAN1��CAN2����28����������
	�� ����STM32F103xxϵ�в�Ʒ����14����������
�� ��ʶ���б�
�� FIFO���������ʽ������
�� ��¼����SOFʱ�̵�ʱ���
��ʱ�䴥��ͨ��ģʽ��
�� ��ֹ�Զ��ش�ģʽ
�� 16λ�������ж�ʱ��
�� �������2�������ֽڷ���ʱ���
��������
�� �жϿ�����
�� ����ռ�õ���1���ַ�ռ䣬�����������Ч��
��˫CAN��
�� CAN1������bxCAN������������ڴ�bxCAN��512�ֽڵ�SRAM�洢��֮���ͨ��
�� CAN2���Ǵ�bxCAN��������ֱ�ӷ���SRAM�洢��
�� ��2��bxCANģ�鹲��512�ֽڵ�SRAM�洢��


ע��	���������ʹ�������Ʒ�У�USB��CAN����һ��ר�õ�512�ֽڵ�SRAM�洢���������ݵķ��ͺͽ��գ�
			��˲�ͬͬʱʹ��USB��CAN(������SRAM��USB��CANģ�黥��ط���)��USB��CAN����ͬʱ����һ��Ӧ���е�������ͬһ��ʱ��ʹ�á�

*************************************************************************************************************************

################################################################################
###############################################################################*/

//CanRxMsg *RxMessage;

/*******************************************************************************
*������		:	DMA_Configuration
*��������	:	��������
*����			:	MemoryAddr--�ڴ��ַ,
						BufferSize--�����С
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void CAN_Configuration(void)	//CAN����
{
	CAN_INIT();
}
/*******************************************************************************
*������		:DMA_Server
*��������	:DMA�жϷ�����
*����			: 
*���			:��
*����ֵ		:��
*����			:
*******************************************************************************/
void CAN_Server(void)
{
//	CAN_RX_DATA();
	WOW_Server();
//	CAN_RX_DATA(RxMessage);
}
/*******************************************************************************
*������		:	CAN_PinSet
*��������	:	CAN�������ú���
*����			:	CANRemap_TypeDef CANRemap_Status:
						CANRemapNone:	Ĭ�����ţ�δ�ض���
						CANRemap1:	CAN�ض����ַ1ģʽ
						CANRemap2:	CAN�ض����ַ1ģʽ
*���			:	��
*����ֵ		:	��������״̬
						SUCCESS:	�������óɹ�
						ERROR:	��������ʧ��
*����			:
*******************************************************************************/
ErrorStatus CAN_PinSet(CANRemap_TypeDef CANRemap_Status)						//
{
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO�ṹ��	
	
	assert_param(IS_CANRemap_Status(CANRemap_Status));
//*****************************CANĬ����������**********************************
	if(CANRemap_Status==CANRemapNone)
	{
		//1.1)**********CAN_RXĬ�Ͻ����������ã�PA11
		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//1.2)**********CAN_TXĬ�Ϸ����������ã�PA12
		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//1.3)**********��������״̬
		return SUCCESS;				//�������óɹ�
	}
	
//*****************************CAN�ض����ַ1ģʽ��������**********************************
	else if(CANRemap_Status==CANRemap1)
	{
		//1.1)**********CAN_RX�ض����ַ1ģʽ�����������ã�PB8 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
		//1.2)**********CAN_RX�ض����ַ1ģʽ�����������ã�PB9  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//1.3)********** Configure CAN Remap ��Ӱ��
		GPIO_PinRemapConfig(GPIO_Remap1_CAN, ENABLE);
		//1.4)**********��������״̬
		return SUCCESS;				//�������óɹ�
		
	}

//*****************************CAN�ض����ַ2ģʽ��������**********************************
	else if(CANRemap_Status==CANRemap2)
	{
		//1.1)**********CAN_RX�ض����ַ2ģʽ�����������ã�PD0 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOD, &GPIO_InitStructure); 
		//1.2)**********CAN_RX�ض����ַ2ģʽ�����������ã�PD1  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		//1.3)********** Configure CAN Remap ��Ӱ��
		GPIO_PinRemapConfig(GPIO_Remap2_CAN, ENABLE);
		//1.4)**********��������״̬
		return SUCCESS;				//�������óɹ�
	}
	else
		return ERROR;			//��������ʧ��
}
/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void CAN_INIT(void)
{
	CAN_InitTypeDef        	CAN_InitStructure;
  
	NVIC_InitTypeDef 				NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO |RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);

	CAN_PinSet(CANRemapNone);
	
	//1.1)**********CAN��ʼ�� 
  CAN_InitStructure.CAN_TTCM=DISABLE;		//CAN_TTCM����ʹ�ܻ���ʧ��ʱ�䴥��ͨѶģʽ�������������������ֵΪENABLE����DISABLE��
																				//->0����ֹʱ�䴥��ͨ��ģʽ��
																				//->1������ʱ�䴥��ͨ��ģʽ��
																				//->�ڸ�ģʽ�£�CANӲ�����ڲ���ʱ����������ұ����ڲ���(��������������)ʱ������ֱ�洢��CAN_RDTxR/CAN_TDTxR�Ĵ����С�
																				//->�ڲ���ʱ����ÿ��CANλʱ���ۼӡ��ڲ���ʱ���ڽ��պͷ��͵�֡��ʼλ�Ĳ�����λ�ñ�������������ʱ���
	
  CAN_InitStructure.CAN_ABOM=DISABLE;		//CAN_ABOM����ʹ�ܻ���ʧ���Զ����߹����������������������ֵΪENABLE����DISABLE��
																				//��λ����CANӲ����ʲô�����¿����˳�����״̬��
																				//->���ABOMλΪ��1����bxCAN��������״̬�󣬾��Զ������ָ����̡�
																				//->���ABOMλΪ��0������������������bxCAN����Ȼ�����˳���ʼ��ģʽ�����ָ����̲ű�������
																				//->��TEC����255ʱ��bxCAN�ͽ�������״̬��ͬʱCAN_ESR�Ĵ�����BOFFλ���á�1����������״̬�£�bxCAN�޷����պͷ��ͱ��ġ�
	
  CAN_InitStructure.CAN_AWUM=DISABLE;		//CAN_AWUM����ʹ�ܻ���ʧ���Զ�����ģʽ�������������������ֵΪENABLE����DISABLE��
																				//��λ����CAN����˯��ģʽʱ��Ӳ��������������
																				//->0��˯��ģʽͨ�����CAN_MCR�Ĵ�����SLEEPλ�����������ѣ�
																				//->1��˯��ģʽͨ�����CAN���ģ���Ӳ���Զ����ѡ����ѵ�ͬʱ��Ӳ���Զ���CAN_MSR�Ĵ�����SLEEP��SLAKλ�塯0�� ��
	
  CAN_InitStructure.CAN_NART=DISABLE;		//CAN_NARM����ʹ�ܻ���ʧ�ܷ��Զ��ش���ģʽ�������������������ֵΪENABLE����DISABLE��
																				//->0������CAN��׼��CANӲ���ڷ��ͱ���ʧ��ʱ��һֱ�Զ��ش�ֱ�����ͳɹ���
																				//->1��CAN����ֻ������1�Σ����ܷ��͵Ľ�����(�ɹ����������ٲö�ʧ)��
	
  CAN_InitStructure.CAN_RFLM=DISABLE;		//CAN_RFLM����ʹ�ܻ���ʧ�ܽ���FIFO����ģʽ�������������������ֵΪENABLE����DISABLE��
																				//->0���ڽ������ʱFIFOδ��������������FIFO�ı���δ����������һ���յ��ı��ĻḲ��ԭ�еı��ģ�
																				//->1���ڽ������ʱFIFO��������������FIFO�ı���δ����������һ���յ��ı��Ļᱻ������
	
  CAN_InitStructure.CAN_TXFP=DISABLE;		//CAN_TXFP����ʹ�ܻ���ʧ�ܷ���FIFO���ȼ��������������������ֵΪENABLE����DISABLE��
																				//���ж������ͬʱ�ڵȴ�����ʱ����λ������Щ���ĵķ���˳��
																				//->0�����ȼ��ɱ��ĵı�ʶ����������
																				//->1�����ȼ��ɷ��������˳����������
	
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;		//CAN_Mode������CAN�Ĺ���ģʽ��<CAN operating mode>.�����˸ò�����ȡ��ֵ
																									//CAN_Mode_Normal:CANӲ������������ģʽ
																									//CAN_Mode_LoopBack:CANӲ�������ڻ���ģʽ
																																		//�ڻ���ģʽ�£�bxCAN�ѷ��͵ı��ĵ������յı��Ĳ�����(�������ͨ�����չ���)�ڽ��������
																																		//����ģʽ�������Բ��ԡ�Ϊ�˱����ⲿ��Ӱ�죬�ڻ���ģʽ��CAN�ں˺���ȷ�ϴ���(������/Զ��֡��ȷ��λʱ�̣�������Ƿ�������λ)��
																																		//�ڻ���ģʽ�£�bxCAN���ڲ���Tx���������Rx�����ϣ�����ȫ����CANRX���ŵ�ʵ��״̬�����͵ı��Ŀ�����CANTX�����ϼ�⵽��
																									//CAN_Mode_Silent:CANӲ�������ھ�Ĭģʽ
																																		//->�ھ�Ĭģʽ�£�bxCAN���������ؽ�������֡��Զ��֡����ֻ�ܷ�������λ���������������ͱ��ġ�
																																		//->���bxCAN��Ҫ��������λ(ȷ��λ�����ر�־�����������־)����ô����������λ���ڲ����ӻ����Ӷ����Ա�CAN�ں˼�⵽��
																																		//->ͬʱCAN���߲����ܵ�Ӱ�����Ȼά��������λ״̬����ˣ���Ĭģʽͨ�����ڷ���CAN���ߵĻ��
																																		//->��������������Ӱ�죭����λ(ȷ��λ������֡)�����������͵������ϡ�
																									//CAN_Mode_Silent_LoopBack:CANӲ�������ھ�Ĭ����ģʽ
																																		//->����ѡ�񻷻ؾ�Ĭģʽ����ģʽ�����ڡ����Բ��ԡ����������񻷻�ģʽ��������bxCAN����ȴ����Ӱ��CANTX��CANRX�����ӵ�����CANϵͳ��
																																		//->�ڻ��ؾ�Ĭģʽ�£�CANRX������CAN���߶Ͽ���ͬʱCANTX���ű�����������λ״̬��
																																		
			//1.2)**********CAN������
	/* Configure the CAN Baud Rate -------------------------------------------*/
//  RCC_GetClocksFreq(&RCC_ClocksStatus);
//  if (usartxbase == USART1_BASE)
//  {
//    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
//  }
//  else
//  {
//    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
//  }
	/*
	CANʱ����RCC_APB1PeriphClock����Ҫע��CANʱ��Ƶ�� 
	CAN������ = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler; 
	���CANʱ��Ϊ8M�� CAN_SJW = 1��CAN_BS1 = 8��CAN_BS2 = 7��CAN_Prescaler = 2 
	��ô�����ʾ���=8M/(1+8+7)/2=250K 
	*/
//******************CAN������50K
//  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//CAN_SJW����������ͬ����Ծ����(SJW)������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥λ�����ޣ�<CAN synchronisation jump width>�����˸ò�����ȡ��ֵ
//																					//CAN_SJW_1tq:����ͬ����Ծ����1��ʱ�䵥λ
//																					//CAN_SJW_2tq:����ͬ����Ծ����2��ʱ�䵥λ
//																					//CAN_SJW_3tq:����ͬ����Ծ����3��ʱ�䵥λ
//																					//CAN_SJW_4tq:����ͬ����Ծ����4��ʱ�䵥λ
//  CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;	//CAN_BS1�趨��ʱ���1��ʱ�䵥λ��Ŀ��<time quantum in bit segment 1>�����˸ò�����ȡ��ֵ
//	
//  CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;	//CAN_BS2�趨��ʱ���1��ʱ�䵥λ��Ŀ��<time quantum in bit segment 2>�����˸ò�����ȡ��ֵ
//	
//  CAN_InitStructure.CAN_Prescaler=45;			//CAN_Prescaler�趨��һ��ʱ�䵥λ�ĳ��ȣ����ķ�Χ��1��1024��


//******************CAN������100K
	
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//CAN_SJW����������ͬ����Ծ����(SJW)������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥λ�����ޣ�<CAN synchronisation jump width>�����˸ò�����ȡ��ֵ
																					//CAN_SJW_1tq:����ͬ����Ծ����1��ʱ�䵥λ
																					//CAN_SJW_2tq:����ͬ����Ծ����2��ʱ�䵥λ
																					//CAN_SJW_3tq:����ͬ����Ծ����3��ʱ�䵥λ
																					//CAN_SJW_4tq:����ͬ����Ծ����4��ʱ�䵥λ
  CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;	//CAN_BS1�趨��ʱ���1��ʱ�䵥λ��Ŀ��<time quantum in bit segment 1>�����˸ò�����ȡ��ֵ
	
  CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;	//CAN_BS2�趨��ʱ���1��ʱ�䵥λ��Ŀ��<time quantum in bit segment 2>�����˸ò�����ȡ��ֵ
	
  CAN_InitStructure.CAN_Prescaler=30;			//CAN_Prescaler�趨��һ��ʱ�䵥λ�ĳ��ȣ����ķ�Χ��1��1024��
	
  CAN_Init(&CAN_InitStructure);
	
//	CAN_FilterInitConfiguration(0,0X316);		//CAN�˲�������
	
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN_TX_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	CAN_ITConfig(CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0, ENABLE);  // fifo0�ж�
	CAN_ITConfig(CAN_IT_FMP1 | CAN_IT_FF1 | CAN_IT_FOV1, DISABLE);  // fifo1�ж�
	CAN_ITConfig(CAN_IT_TME, DISABLE); 
	
	              // �����ж�
		 
	/* Enable CAN FIFO 0 overrun interrupt */
//	CAN_ITConfig(CAN_IT_FOV0, ENABLE);	
}
/*******************************************************************************
* ������		:
* ��������	: 
* ����			: ��
* ���			: ��
* ����			: ��
*******************************************************************************/
void CAN_FilterInitConfiguration(u8 CAN_GROUP,u16 CAN_ID,u16 MaskId)		//CAN�˲�������
{
	CAN_FilterInitTypeDef		CAN_FilterInitStructure;
//	CAN_ID=0X317;

  //1.3)**********CAN�˲�����ʼ��
	//1.3.1---------��������
  CAN_FilterInitStructure.CAN_FilterNumber=CAN_GROUP;										//���ù�������0����ΧΪ0~13
	//1.3.2---------�������Ĺ���ģʽ
	//�� ��������Ϊ����ģʽʱ����ʶ���Ĵ�����Ӧ��ID���ݿ�Ϊ����һ������յ�IDֵ��
	//�� ��ͬʱҪ���ձ�׼֡����չ֡ʱ����ʶ���Ĵ�����ӦIDEλҲ�������ã�
	//�� ���μĴ�����IDEλ����Ϊ0����ʾ�����ı�׼֡������չ֡��
	//�� �����μĴ�����Ӧ��ID����Ϊ��������յ�IDֵ�������Ľ����ȡ����
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	//����������ʼ������ģʽ
																																//->CAN_FilterMode_IdMask����ʶ������λģʽ
																																//-->A,Ϊ�˹��˳�һ���ʶ����Ӧ�����ù������鹤��������λģʽ��
																																//-->B,������λģʽ�£���ʶ���Ĵ��������μĴ���һ��ָ�����ı�ʶ�����κ�һλ��Ӧ�ð��ա�����ƥ�䡱�򡰲��ù��ġ�������
																																
																																//->CAN_FilterMode_IdList����ʶ���б�ģʽ
																																//-->A,Ϊ�˹��˳�һ����ʶ����Ӧ�����ù������鹤���ڱ�ʶ���б�ģʽ��
																																//-->B, �ڱ�ʶ���б�ģʽ�£����μĴ���Ҳ��������ʶ���Ĵ����á���ˣ����ǲ���һ����ʶ����һ������λ�ķ�ʽ��
																																//------����ʹ��2����ʶ���Ĵ��������ձ��ı�ʶ����ÿһλ���������������ʶ����ͬ��
	//1.3.3---------������λ��																															
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//������λ��
																																//->CAN_FilterScale_Two16bit��2��16λ������	
																																//->CAN_FilterScale_One32bit��1��32λ������
	//1.3.4---------��ʶλ�Ĵ��������� 																															
  CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID<<5;							//�趨��������ʶ����32λλ��ʱΪ��߶�λ��16λλ��ʱΪ��һ���������ķ�Χ��0x0000��0xFFFF��																																
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;								//�趨��������ʶ����32λλ��ʱΪ��Ͷ�λ��16λλ��ʱΪ�ڶ����������ķ�Χ��0x0000��0xFFFF��
	//1.3.5---------���μĴ��������� 
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=MaskId<<5;					//�趨���������α�ʶ�����߹�������ʶ����32λλ��ʱΪ��߶�λ��16λλ��ʱΪ��һ���������ķ�Χ��0x0000��0xFFFF��
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;						//�趨���������α�ʶ�����߹�������ʶ����32λλ��ʱΪ��Ͷ�λ��16λλ��ʱΪ�ڶ����������ķ�Χ��0x0000��0xFFFF��
	//1.3.6---------�����������
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;						//�趨ָ���������FIFO��0��1���˹����������������FIFO0
																																//->CAN_FilterFIFO0��������FIFO0ָ�������x
																																//->CAN_FilterFIFO1��������FIFO1ָ�������x
	//1.3.7---------����˹�������																															
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;					//ʹ�ܻ���ʧ�ܹ��������ò�����ȡ��ֵΪENABLE����DISABLE��
	//1.3.7---------���ù�����
  CAN_FilterInit(&CAN_FilterInitStructure);


}

/*******************************************************************************
* ������		:
* ��������	: 
* ����			: ��
* ���			: ��
* ����			: ��
*******************************************************************************/
void CAN_TX_DATA(u16 CAN_ID,u16 data)
{
	CanTxMsg TxMessage;
	u8	TransmitMailbox = 0;
	u32	i;

	TxMessage.StdId=CAN_ID;
//	TxMessage.ExtId=0XFF;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.DLC=3;
	TxMessage.Data[0]=0X08;
	TxMessage.Data[1]=(data>>8)&0XFF;
	TxMessage.Data[2]=data&0XFF;
	TxMessage.Data[3]=0x08;
	TxMessage.Data[4]=0x16;
	TxMessage.Data[5]=0x32;
	TxMessage.Data[6]=(data>>8)&0XFF;
	TxMessage.Data[7]=data&0XFF;
	TransmitMailbox = CAN_Transmit(&TxMessage);
	i = 0;
	// ���ڼ����Ϣ�����Ƿ�����
	while((CAN_TransmitStatus(TransmitMailbox) != CANTXOK) && (i != 0xFF))
	{
		i++;
	}
	i = 0;
	// ��鷵�صĹҺŵ���Ϣ��Ŀ
	while((CAN_MessagePending(CAN_FIFO0) < 1) && (i != 0xFF))
	{
		i++;
	}

}
/*******************************************************************************
* ������		:
* ��������	: 
* ����			: ��
* ���			: ��
* ����			: ��
*******************************************************************************/
void CAN_RX_DATA(CanRxMsg *RxMessage)
{
	if(SET == CAN_GetITStatus(CAN_IT_FF0))
	{
		CAN_ClearITPendingBit(CAN_IT_FF0);
	}
	else if(SET == CAN_GetITStatus(CAN_IT_FOV0))
	{
		CAN_ClearITPendingBit(CAN_IT_FOV0);
	}
	else
	{
			CAN_Receive(CAN_FIFO0, RxMessage);
	}
}
















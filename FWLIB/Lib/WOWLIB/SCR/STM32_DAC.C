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


#include "STM32_DAC.H"
//#include "STM32F10x_BitBand.H"

/*******************************************************************************
��������
STM32��DAC��һ��12λ����ѹ�����DAC���ɱ�����Ϊ12λ����8λ��Ҳ�ܺ�DMA����ʹ�á�
DAC������������ת��ͨ������˫DACģʽ�£�DAץ���ɱ����óɶ���ģʽ����ͬ������ģʽ��
��·DAC�ο���ѹ�Լ�ADC����VREF
����Ҫ���ԡ�
1����·
2��12bitʱ���ݿɱ����ó��������Ҷ���
3������ͬ����������
4����������
5�����ǲ�����
6������ͨ������ת����ͬ��ת��
7��ÿ��ͨ������DMA����
8��DMA�������
9�����ⲿ����
�������ѹ���㹫ʽ��
Vout = VREF��DOR/4095 = �ο���ѹ��DAC���ݼĴ���ֵ/4095

*******************************************************************************/

//#define DAC_DHR8R1_Address		0x40007410
//#define DAC_DHR8R1_Address		DAC_BASE + DHR12R1_Offset + DAC_Align_8b_R		//CH1_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ

#define DAC_DHR8R1_Address		DAC_BASE + 0x00000008 + DAC_Align_8b_R		//CH1_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ
#define DAC_DHR8R2_Address		DAC_BASE + 0x00000014 + DAC_Align_8b_R		//CH2_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ


#define DAC_DHR12R1_Address		DAC_BASE + 0x00000008 + DAC_Align_12b_R		//CH1_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ
#define DAC_DHR12R2_Address		DAC_BASE + 0x00000014 + DAC_Align_12b_R		//CH2_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ

#define DAC_DHR12L1_Address		DAC_BASE + 0x00000008 + DAC_Align_12b_L		//CH1_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ
#define DAC_DHR12L2_Address		DAC_BASE + 0x00000014 + DAC_Align_12b_L		//CH2_12λ�Ҷ������ݸ�ʽ�Ĵ�����ַ

uc8 Escalator8bit[6] = {0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF};
uc16 Escalator16bit[9] = {0x0, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00,0x0C00,0X0E00,0X0FFF};

/*******************************************************************************
*������		:DAC_Configuration
*��������	:DAC����
*����			:
*���			:��
*����ֵ		:��
*˵��			:����DAC���ָ���ĵ�ѹ����������DACת����
					 STM32 DAC�ܽ�ΪDAC1-PA4,DAC2-PA5 12Bit 
*******************************************************************************/
void DAC_Configuration(void)
{
	DAC_GPIO_Configuration();
	DAC_MODE_Configuration();
}

/*******************************************************************************
*������		:DAC_GPIO_Configuration
*��������	:DAC�ܽ�����
*����			:
*���			:��
*����ֵ		:��
*˵��			:����DAC���ָ���ĵ�ѹ����������DACת����
					 STM32 DAC�ܽ�ΪDAC1-PA4,DAC2-PA5 12Bit 
*******************************************************************************/
void DAC_GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//GPIO�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);				//ʹ��GPIOAʱ��
	
	//1)**********����DAC�ܽ�	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								//ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure);												//��������
	
}
/*******************************************************************************
*������		:DAC_MODE_Configuration
*��������	:DAC��������
*����			:
*���			:��
*����ֵ		:��
*˵��			:����DAC���ָ���ĵ�ѹ����������DACת����
					 STM32 DAC�ܽ�ΪDAC1-PA4,DAC2-PA5 12Bit 
*******************************************************************************/
void DAC_MODE_Configuration(void)
{
	DAC_InitTypeDef		DAC_InitStructure; 				//DAC�ṹ��
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//1)**********��DAC����Ϊȱʡֵ	
	DAC_DeInit();																//��DAC����Ϊȱʡֵ

	//2)**********��DACʱ�ӣ������÷�Ƶ����	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);					//ʹ��DACʱ��

//////////////////��ʱ��
	

//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);   
//     TIM_TimeBaseStructure.TIM_Period =0x19;    
//     TIM_TimeBaseStructure.TIM_Prescaler = 0;    
//     TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
//     TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

// TIM_ARRPreloadConfig(TIM6 , ENABLE);

//    /* TIM6 TRGO selection */
//     TIM_SelectOutputTrigger(TIM6 , TIM_TRGOSource_Update);

// TIM_ITConfig(TIM6 , TIM_IT_Update , ENABLE);
//////////////////////////////////

	//3)**********����DACģʽ	
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_Software;													//DAC����Դ----��������	
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_Noise;								//���η�����----��ʹ���ڲ����η�����
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;		//���η�����----������Σ���Ϊ�����
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Enable;									//���������---���������ʱ���������ǿЩ
	//	DAC_Init(DAC_Channel_1|DAC_Channel_2,&DAC_InitStructure);									//DAC1--PA4
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);									//DAC1--PA4
	DAC_Init(DAC_Channel_2,&DAC_InitStructure);									//DAC2--PA5

	//4)**********ʹ��DAC
	DAC_Cmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_2,ENABLE);
	//5)**********������Ĵ���д���ݣ����ݿɸ����ϱ߹�ʽ�õ�
	//Vout = VREF��DOR/4095 = �ο���ѹ��DAC���ݼĴ���ֵ/4095
	DAC_SetChannel1Data(DAC_Align_12b_R,4095);
	DAC_SetChannel2Data(DAC_Align_12b_R,4095);
	//4)**********�������
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
/*******************************************************************************
*������		:DAC_MODE_Configuration
*��������	:DAC��������
*����			:
*���			:��
*����ֵ		:��
*˵��			:����DAC���ָ���ĵ�ѹ����������DACת����
					 STM32 DAC�ܽ�ΪDAC1-PA4,DAC2-PA5 12Bit 
*******************************************************************************/
void DAC_DMA_Configuration(u32 *MemoryAddr)
{
//	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//��ʱ���ṹ�嶨��
	DAC_InitTypeDef		DAC_InitStructure; 				//DAC�ṹ��
	DMA_InitTypeDef DMA_InitStructure;
	
	/* Enable peripheral clocks --------------------------------------------------*/
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
  /* AFIO and GPIOA Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  /* TIM6 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	DAC_GPIO_Configuration();
	
	 /* TIM6 Configuration */
	TIM_PrescalerConfig(TIM6, 71, TIM_PSCReloadMode_Update);		//��Ƶ
	TIM_SetAutoreload(TIM6, 1);																//��ֵ
	/* TIM6 TRGO selection */
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* DMA2 channel3 configuration */
	DMA_DeInit(DMA2_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)MemoryAddr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel4, &DMA_InitStructure);

	/* Enable DMA2 Channel3 */
	DMA_Cmd(DMA2_Channel4, ENABLE);

	/* Enable DAC Channel1 */
	DAC_Cmd(DAC_Channel_2, ENABLE);

	/* Enable DMA for DAC Channel1 */
	DAC_DMACmd(DAC_Channel_2, ENABLE);

	/* TIM6 enable counter */
	TIM_Cmd(TIM6, ENABLE);
}







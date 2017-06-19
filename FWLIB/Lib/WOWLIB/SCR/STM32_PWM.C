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



#include "STM32_PWM.H"

//#include "STM32_TIM.H"


//*******************************PWM��ؽṹ��**********************************/

///1************* ��ʱ���ṹ�� */
///* TIM Time Base Init structure definition */
//typedef struct
//{
//  u16 TIM_Prescaler;								//-------��Ƶϵ��========ȡֵ0x0000~0xFFFF��������ƵTIM clock
//  u16 TIM_CounterMode;							//-------������ʽ========TIM_CounterMode_Up(���ϼ���ģʽ),TIM_CounterMode_Down(���¼���ģʽ),
																			//-----------------------TIM_CounterMode_CenterAligned1(�������ģʽ1����ģʽ),TIM_CounterMode_CenterAligned2(�������ģʽ2����ģʽ),TIM_CounterMode_CenterAligned3(�������ģʽ3����ģʽ)
//  u16 TIM_Period;										//-------����ֵ==========��һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,ȡֵ0x0000~0xFFFF,����TIM_Period+1�����ĺ�������
//  u16 TIM_ClockDivision;						//-------�趨ʱ��ָ�ֵ===Ĭ��Ϊ0,���ⳡ��ʱTIM_ClockDivision������һ����ʱ,TIM_CKD_DIV1,TIM_CKD_DIV2,TIM_CKD_DIV3
//  u8 TIM_RepetitionCounter;					//-------�ظ���������=====�ظ����ٴ������Ŵ���һ������жϣ�
//} TIM_TimeBaseInitTypeDef;
///2************* PWM������� */
///* TIM Output Compare Init structure definition */
//typedef struct
//{
//  u16 TIM_OCMode;										//-------��ʱ��ģʽ=======TIM_OCMode_Timing(����Ƚ�ʱ��ģʽ),TIM_OCMode_Active(����Ƚ�����ģʽ),TIM_OCMode_Inactive(����ȽϷ�����ģʽ),
																			//-----------------------TIM_OCMode_Toggle(����Ƚϴ���ģʽ),TIM_OCMode_PWM1(������ȵ���ģʽ1),TIM_OCMode_PWM2(������ȵ���ģʽ2)		
//  u16 TIM_OutputState;							//-------
//  u16 TIM_OutputNState;							//-------
//  u16 TIM_Pulse;
//  u16 TIM_OCPolarity;
//  u16 TIM_OCNPolarity;
//  u16 TIM_OCIdleState;
//  u16 TIM_OCNIdleState;
//} TIM_OCInitTypeDef;
///3************* PWM���빹�� */
///* TIM Input Capture Init structure definition */
//typedef struct
//{
//  u16 TIM_Channel;
//  u16 TIM_ICPolarity;
//  u16 TIM_ICSelection;
//  u16 TIM_ICPrescaler;
//  u16 TIM_ICFilter;
//} TIM_ICInitTypeDef;
///4************* BDTR�߼���ʱ�������������ṹ�� */
///* BDTR structure definition */
//typedef struct
//{
//  u16 TIM_OSSRState;
//  u16 TIM_OSSIState;
//  u16 TIM_LOCKLevel; 
//  u16 TIM_DeadTime;
//  u16 TIM_Break;
//  u16 TIM_BreakPolarity;
//  u16 TIM_AutomaticOutput;
//} TIM_BDTRInitTypeDef;



/*##############################################################################
################################################################################
# ģ����		:	STM32_PWM	
# ��������	:	PWM����ʹ��
-------------------------------------------------------------------------------	


***********************************************************************************************************
---------------------------------------------------------------------------------------	
����	|	CH1		|	CH2		|	CH3		|	CH4		|								|								|								|
---------------------------------------------------------------------------------------	
TIM1	|	PA8		|	PA9		|	PA10	|	PA11	|								|								|								|
---------------------------------------------------------------------------------------	
TIM2	|	PA0		|	PA1		|	PA2		|	PA3		|								|								|								|
---------------------------------------------------------------------------------------	
TIM3	|	PA6		|	PA7		|	PB0		|	PB1		|								|								|								|
---------------------------------------------------------------------------------------	
TIM4	|	PB6		|	PB7		|	PB8		|	PB9		|								|								|								|
---------------------------------------------------------------------------------------	
TIM5	|				|				|				|				|								|								|								|
---------------------------------------------------------------------------------------	
TIM6	|				|				|				|				|								|								|								|
---------------------------------------------------------------------------------------	
TIM7	|				|				|				|				|								|								|								|
---------------------------------------------------------------------------------------	
TIM8	|				|				|				|				|								|								|								|
---------------------------------------------------------------------------------------	


################################################################################
###############################################################################*/
/*******************************************************************************
* ������		:	PWM_OUT	
* ��������	:		 
* ����		:	PWM_Frequency Ƶ�ʣ���λHz	
* ���		:
* ���� 		:
*******************************************************************************/
void PWM_OUT			//PWM�������
(
	TIM_TypeDef* TIMx,											//��ʹ�õĶ�ʱ��
	PWM_OUTChannelTypeDef PWM_OUTChanneln,	//PWM���ͨ����
	double PWM_Frequency,										//���Ƶ�ʣ���СƵ��0.02Hz		
	u16 PWM_Ratio														//���ռ�ձȣ��ֱ���1/1000
)
{
	//*1,�ṹ�嶨��
	//*2,��������
	//*3,�ܽ�ȷ��
	//*4,����Ӧ��ʱ��
	//*5,�ܽ����ã���ʼ����
	//*6,��ʱ�����ã���ʼ����
	//*7,PWM������ã���ʼ����
	//*8,ռ�ձ�����	
	
	//*1,�ṹ�嶨��***********************************************************************
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//��ʱ���ṹ�嶨��
	TIM_OCInitTypeDef TIMOCInitStructure;
	RCC_ClocksTypeDef RCC_ClocksStatus;							//ʱ��״̬---ʱ��ֵ	
	//*2,��������*************************************************************************	
	GPIO_TypeDef* GPIOx				=	0;			//x=A/B/C/D/E/F/G
	u16 GPIO_Pin_n						=	0xFF;		//n=0~15;
	u32 RCC_APB2Periph_GPIOx	=	0x00;		//x=A/B/C/D/E/F/G	
	u32	TIMx_Frequency=0;								//	��ʱ��ʱ��
	u16 TIMx_Prescaler				=	0	;			//	��ʱ��ʱ�ӷ�Ƶֵ		ȡֵ��Χ��0x0000~0xFFFF
  u16 TIMx_Period						=	0	;			//	��ʱ���Զ���װ��ֵ	ȡֵ��Χ��0x0000~0xFFFF
//	u32	Microsecond						=	0	;		//	΢��
//	u32	Nanosecond						=	0	;		//	����
	double	Tim_num1					=	0	;			//	��ʱ����1
//	u8	Tim_flg								=	0	;			//	��ʱ����2
	//*3,�ܽ�����--�����������ѡ����Ӧ��GPIO************************************************
	switch (*(u32*)&TIMx)
	{
		case TIM1_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_8;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;	
															break;
				case PWM_OUTChannel2:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_9;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel3:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_10;	RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel4:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_11;	RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
			}
			break;
		
		case TIM2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_0;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel2:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_1;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel3:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_2;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel4:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_3;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
			}
			break;
		
		case TIM3_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_6;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel2:	GPIOx	=	GPIOA;	GPIO_Pin_n	=	GPIO_Pin_7;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOA;
															break;
				case PWM_OUTChannel3:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_0;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
				case PWM_OUTChannel4:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_1;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
			}
			break;
		
		case TIM4_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_6;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
				case PWM_OUTChannel2:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_7;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
				case PWM_OUTChannel3:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_8;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
				case PWM_OUTChannel4:	GPIOx	=	GPIOB;	GPIO_Pin_n	=	GPIO_Pin_9;		RCC_APB2Periph_GPIOx	=	RCC_APB2Periph_GPIOB;
															break;
			}
			break;
		
		case TIM5_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			break;
		
		case TIM6_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			break;
		
		case TIM7_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			break;
		
		case TIM8_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			break;
		
		default:
			break;		
	}
	
	
	//*4,����Ӧ��ʱ��*********************************************************************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//ʹ�ܸ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);	//ʹ������ʱ��	
	//*5,�ܽ����ã���ʼ����*****************************************************************
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_n;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;//�����������
	GPIO_Init(GPIOx,&GPIO_InitStructure);	
	//*6,��ȡTIMxʱ��**********************************************************************
	//1��-----��Ƶֵ���Զ���װ��ֵ���㣨PWM_Frequency Ƶ�ʣ���λHz��
	//--------1MHz 1us=1000ns,1KHz 10us=10000ns
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//��ȡʱ�Ӳ���
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;;
	if (((*(u32*)&TIMx)&APB2PERIPH_BASE) == APB2PERIPH_BASE)
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	//APB2
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	//APB1
  }
	//*7,���㶨ʱ������*********************************************************************
	//Fsys==Fpwm*Count==Fpwm*(Prescaler*Period)	
	//	TIMx_Prescaler				=	72-1		;		// 	��ʱ��ʱ�ӷ�Ƶֵ
	//	TIMx_Period						=	1000-1	;		// 	��ʱ���Զ���װ��ֵ
	//	Tim_num1							=	0				;		//	��ʱ����1
	if(1/PWM_Frequency>10)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*100);							//���ݶ�ʱ�����Ƶ�ʼ������ֵ
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*200);
	}
	else if(1/PWM_Frequency>1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*10);							//���ݶ�ʱ�����Ƶ�ʼ������ֵ
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*20);
	}
	else if(PWM_Frequency>=1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency);							//���ݶ�ʱ�����Ƶ�ʼ������ֵ
		Tim_num1=(double)(Tim_num1*2.0);
		if(Tim_num1>=10000000)
		{
			TIMx_Prescaler=2000;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=1000000)
		{
			TIMx_Prescaler=200;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=100000)
		{
			TIMx_Prescaler=20;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=65530)
		{
			TIMx_Prescaler=2;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else
		{
			TIMx_Prescaler=1;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
	}	
	//8)**********��ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler-1; 				//�趨��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period-1;        		//�趨�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  				//���ָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  		//���ϼ���
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		//��ʼ��	
	//9����ʱ�����ã���ʼ��*******************************************************************
	if((TIMx_Period*(u32)PWM_Ratio)>1000)
		PWM_Ratio=(u16)((u32)(TIMx_Period*PWM_Ratio)/1000);
	else if(PWM_Ratio!=0)
		PWM_Ratio=1;
		
	TIMOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 								//ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1
	TIMOCInitStructure.TIM_Pulse =(u16)PWM_Ratio;										//ռ�ձ�=(CCRx/ARR)*1000%
	TIMOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//�������:TIM����Ƚϼ��Ը�
	TIMOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//�Ƚ����ʹ��
	//10����ʱ�����ã���ʼ��*******************************************************************
	switch(PWM_OUTChanneln)
	{
		case PWM_OUTChannel1:	TIM_OC1Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
		break;
		case PWM_OUTChannel2:	TIM_OC2Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
		break;
		case PWM_OUTChannel3:	TIM_OC3Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
		break;
		case PWM_OUTChannel4:	TIM_OC4Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
		break;
		default:
		break;
	}	
	TIM_CtrlPWMOutputs(TIMx,ENABLE);																//����TIM2��PWM���ʹ��
	//11����ʱ�����ã���ʼ��*******************************************************************
	switch(PWM_OUTChanneln)			//ʹ��TIM��CCR�ϵ�Ԥװ�ؼĴ���
	{
		case PWM_OUTChannel1:	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
				break;
		case PWM_OUTChannel2:	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
				break;
		case PWM_OUTChannel3:	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
				break;
		case PWM_OUTChannel4:	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
				break;
	}	
	
	TIM_ARRPreloadConfig(TIMx, ENABLE);			//ARPEʹ�� 
	
	TIM_Cmd(TIMx, ENABLE); 									//ʹ��TIM
}


























//*****************************************************����Ϊ�ɳ���********************
///*******************************************************************************
//* ������		:	PWM_Configuration	
//* ��������	:	 
//* ����		:	
//* ���		:
//* ���� 		:
//*******************************************************************************/
//void PWM_Configuration(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period,u8 PWM_RATIO)
//{
//	PWM_GPIO_Configuration();										//PWMʹ�õ�GPIO����
////	TIM_Configuration(TIMx,Prescaler,Period);		//��ʱ������
//	PWM_ClockCmd(TIMx,Prescaler,Period,PWM_RATIO);	//PWM�趨	
////	TIM_ARRPreloadConfig(TIM2, ENABLE);
////	TIM_Cmd(TIM2, ENABLE); 	
//}

//void PWM_GPIO_Configuration(void)			//PWMʹ�õ�GPIO����
//{//PA0����
//	GPIO_InitTypeDef GPIO_InitStructure;
////	GPIO_DeInit(GPIOA);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;//�����������
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOA�͸���ʱ��
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//}
///*******************************************************************************
//* ������		:	PWM_ClockCmd
//* ��������	:	PWM���ʱ��ʹ��	 
//* ����		:	
//* ���		:
//* ���� 		:
//*******************************************************************************/
//void PWM_ClockCmd(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period,u8 PWM_RATIO)		//�������GPIOʱ��	
//{
//	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//��ʱ���ṹ�嶨��
//	TIM_OCInitTypeDef TIMOCInitStructure;
////	NVIC_InitTypeDef	NVIC_InitStructure;						//�жϽṹ��
////	u8 TIM_IRQChannel=0;
//	//1)**********������ر���	
//		switch (*(u32*)&TIMx)
//	{
//		case TIM1_BASE:
//			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
////			TIM_IRQChannel=TIM1_UP_IRQChannel;
//			break;
//		
//		case TIM2_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
////			TIM_IRQChannel=TIM2_IRQChannel;
//			break;
//		
//		case TIM3_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
////			TIM_IRQChannel=TIM3_IRQChannel;
//			break;
//		
//		case TIM4_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
////			TIM_IRQChannel=TIM4_IRQChannel;
//			break;
//		
//		case TIM5_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
////			TIM_IRQChannel=TIM5_IRQChannel;
//			break;
//		
//		case TIM6_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
////			TIM_IRQChannel=TIM6_IRQChannel;
//			break;
//		
//		case TIM7_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
////			TIM_IRQChannel=TIM7_IRQChannel;
//			break;
//		
//		case TIM8_BASE:
//			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
////			TIM_IRQChannel=TIM8_UP_IRQChannel;
//			break;
//		
//		default:
//			break;
//		
//	}
//	
//	TIMx_RCC_ENABLE(TIMx);													//����Ӧ��ʱ��ʱ��
//	//1)**********������ر���	
//	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1; 		// �趨��Ƶֵ
//	TIM_TimeBaseStructure.TIM_Period = Period-1;        	//�趨�Զ���װ��ֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //���ָ�
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
//	//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//????,???????????????????-??????????
//	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		//��ʼ��
//	//1)**********������ر���	
//	TIM_ARRPreloadConfig(TIMx, ENABLE);
//	TIM_Cmd(TIMx, ENABLE); 
//	
//	//1)**********������ر���	
////	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel;
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);
//	
//	/* Clear TIMx update pending flag[���TIMx����ж�] */
//	TIM_ClearFlag(TIMx, TIM_FLAG_Update);

//	/* Enable TIM2 Update interrupt [TIMx����ж�����]*/
////	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); 

//	/* TIM2 enable counter [ʹ��TIMx����]*/
//	TIM_Cmd(TIMx, ENABLE);	//ʹ��TIMx����
//	
//	
//	TIMOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 							//PWM���ģʽ1
////	TIMOCInitStructure.TIM_Pulse =5000;													//ռ�ձ�=(CCRx/ARR)*100%
//	TIMOCInitStructure.TIM_Pulse =(TIMx->ARR)*PWM_RATIO/100;			//ռ�ձ�=(CCRx/ARR)*100%
//	TIMOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//TIM������Ը�
//	TIMOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
//	TIM_OC1Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
//	TIM_CtrlPWMOutputs(TIMx,ENABLE);															//����TIM2��PWM���ʹ��
//	
//	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
//	TIM_ARRPreloadConfig(TIMx, ENABLE);
//	TIM_Cmd(TIMx, ENABLE); 
//}
///*******************************************************************************
//* ������		:	PWM_SET	
//* ��������	:		 
//* ����		:	
//* ���		:
//* ���� 		:
//*******************************************************************************/
//void PWM_SET(TIM_TypeDef* TIMx,u8 PWM_RATIO)	//PWM�趨
//{  
//	TIM_OCInitTypeDef TIMOCInitStructure;
//	TIMOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 							//PWM���ģʽ1
////	TIMOCInitStructure.TIM_Pulse =5000;													//ռ�ձ�=(CCRx/ARR)*100%
//	TIMOCInitStructure.TIM_Pulse =(TIMx->ARR)/100*PWM_RATIO;			//ռ�ձ�=(CCRx/ARR)*100%
//	TIMOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//TIM������Ը�
//	TIMOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
//	TIM_OC1Init(TIMx, &TIMOCInitStructure);												//TIM2��CH1���ʹ��
//	TIM_CtrlPWMOutputs(TIMx,ENABLE);															//����TIM2��PWM���ʹ��
//	
//	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
//	TIM_ARRPreloadConfig(TIMx, ENABLE);
//	TIM_Cmd(TIMx, ENABLE); 																				//������ʱ��
//}
//void PWM_Configuration0(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period,u8 PWM_RATIO)
//{
//	PWM_GPIO_Configuration();					//PWMʹ�õ�GPIO����
//	TIM_Configuration(TIMx,Prescaler,Period);	//��ʱ������
//	PWM_SET(TIMx,PWM_RATIO);	//PWM�趨	
////	TIM_ARRPreloadConfig(TIM2, ENABLE);
////	TIM_Cmd(TIM2, ENABLE); 	
//}










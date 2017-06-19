#ifdef PM001V20

#include "PM001V20.H"



#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"
#include "STM32_PWM.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stm32f10x_dma.h"

#define BufferSize	512

u16 sysledcnt=0;			//ϵͳ����ָʾ��ɨ�����  0.5��

u8 txBuffer[BufferSize]={0};
u8 rxBuffer[BufferSize]={0};

u8	txflg=0;	//���ͱ�־
u8	rxflg=0;	//���ձ�־
u8	bpflg=0;	//������ʹ�ܱ�־

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PM001V20_Configuration(void)
{
	SYS_Configuration();					//ϵͳ����---��ϵͳʱ�� STM32_SYS.H
	
	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
	IWDG_Configuration(1000);			//�������Ź�����---������λms
	
	GPIO_DeInitAll();							//�����е�GPIO�ر�----V20170605
	
	GPIO_Configuration_OOD2	(GPIOC,GPIO_Pin_0);			//SysLed//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
	
	GPIO_Configuration_OPP2	(GPIOC,GPIO_Pin_1);			//BUZZER//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
	
	PM001V20_USART1();
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);	//PWM�趨-20161127�汾
	

}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PM001V20_Server(void)
{	
	IWDG_Feed();								//�������Ź�ι��
	PM001V20_SysLed();					//ϵͳ����ָʾ��	
	PM001V20_USART1_Server();
}

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PM001V20_SysLed(void)
{
	if(sysledcnt++>=500)			//ϵͳ����ָʾ��ɨ�����  0.5��
	{
		sysledcnt=0;
		GPIO_Toggle	(GPIOC,GPIO_Pin_0);		//SysLed//��GPIO��Ӧ�ܽ������ת----V20170605
		if(bpflg)
		GPIO_Toggle	(GPIOC,GPIO_Pin_1);		//BUZZER//��GPIO��Ӧ�ܽ������ת----V20170605
	}
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PM001V20_USART1(void)
{
	USART_DMA_Configuration(USART1,115200,1,1,(u32*)rxBuffer,(u32*)txBuffer,BufferSize);	//USART_DMA����
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC, DISABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, DISABLE);					//ʹ�ÿ����жϣ�DMA�Զ����գ���⵽���߿��б�ʾ���Ͷ��Ѿ�������ɣ����ݱ�����DMA��������
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PM001V20_USART1_Server(void)
{
	u32 num=0;
	if(USART_GetFlagStatus(USART1,USART_FLAG_IDLE))
	{
		USART_ClearFlag(USART1,USART_FLAG_IDLE); 										//������д��ڱ�־λ
		DMA_Cmd(DMA1_Channel5,DISABLE);    																//�رս���DMA
		num = USART1->DR; 																					//������������������־			
		num = BufferSize -  DMA_GetCurrDataCounter(DMA1_Channel5);	//�õ������������ݸ���
		DMA1_Channel5->CMAR=(u32)rxBuffer;													//��������DMA���յ�ַ
		DMA1_Channel5->CNDTR=BufferSize;														//�������ý������ݸ���			
		DMA_Cmd(DMA1_Channel5,ENABLE);  														//��������DMA	
		
		if(num==1)
		{
			if(rxBuffer[0]==0xFA)
			{
				bpflg=1;	//������ʹ�ܱ�־
			}
			else if(rxBuffer[0]==0xFB)
			{
				bpflg=0;	//������ʹ�ܱ�־
				GPIO_WriteBit(GPIOC,GPIO_Pin_1,Bit_RESET);			//����ӦGPIO�ܽ����Ϊ��
			}
		}
		if(num)
		{
			txflg=1;	//���ͱ�־
			memcpy(txBuffer, rxBuffer,num);
			USART_DMASend(USART1,(u32*)txBuffer,num);		//�Զ���printf����DMA���ͳ���
			memset(rxBuffer, 0x00, BufferSize);
		}		
	}
	if(DMA_GetFlagStatus(DMA1_FLAG_GL4))
	{
		if(USART_GetFlagStatus(USART1,USART_FLAG_TC))
		{
			USART_ClearFlag(USART1,USART_FLAG_TC); 										//������д��ڱ�־λ
			DMA_ClearFlag(DMA1_FLAG_GL4);
			DMA_Cmd(DMA1_Channel4,DISABLE);  														//��������DMA
		}
	}
	
	
}
#endif
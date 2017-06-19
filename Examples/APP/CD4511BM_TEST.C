#ifdef	CD4511BM_TEST


//1������ܲ���ָ��
//2��С����������ʾָ��
//3�����⹦�ܣ�����ָ��ȷ�����޳�����CAN,485ͨѶ

#include "CD4511BM_TEST.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#define	CD4511BM_DEBUG_TEST			//����ʱ����ܼ�����ʾ������ʹ��ʱӦ��ע�͵�


u16 Time=0;
u16 data=0;

u8 DsplayFlag=0;			//��ʾ��־��0-���������Լ�ʱLED��ʾ��1-������ʾ��ֵ��2-��������ʾ���λС����

u8 Sub_Cont=0;
u8 Cont=0;
u8 Key_Cont=0;
u16 Dsp_Seg=0;
u8 Key_Flag=0;
u16 time_cnt=0;

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void CD4511BM_TEST_Configuration(void)
{
	SYS_Configuration();											//ϵͳ���� STM32_SYS.H	
	CD4511BM_Configuration();
	CD4511BM_KEY_FUNC();
	PWM_Configuration(TIM2,7200,10000,50);
	SysTick_Configuration(1000);							//ϵͳ���ʱ������72MHz,��λΪuS
}

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void CD4511BM_TEST_Server(void)
{
	++Time;
	if(Time>=10000)
	{
		Time=0;
//		CD4511BM_DISPLAY_DP();
//		CD4511BM_DISPLAY(data,Time%3+1);
	}
	if(!PB8in)
	{
		time_cnt=0;
		if((!Key_Flag)&&(Key_Cont++>100))
		{
			Key_Flag=1;
			Key_Cont=0;
			Sub_Cont++;
			if(Sub_Cont==2)
			{
//				Sub_Cont=1;
				Cont++;				
			}
			if(Sub_Cont>2)
			{
				Sub_Cont=1;
			}
			Dsp_Seg=Sub_Cont*100+Cont;
		}
	}
	else
	{
		Key_Cont=0;
		Key_Flag=0;
		if(time_cnt++>1000)
		{
			if(Sub_Cont>=2)
			{
				Sub_Cont=0;
				Dsp_Seg=Sub_Cont*100+Cont;
			}
			
		}
		if(time_cnt++>2000)
		{
			time_cnt=0;
//			Sub_Cont=0;
//			Dsp_Seg=Sub_Cont*100+Cont;
		}
		
	}
//	SEG_DISPALY(Dsp_Seg);			//��ʾ����
	CD4511BM_DISPLAY(Dsp_Seg,Time%3+1);
//	CD4511BM_DISPLAY(Dsp_Seg,2);
//	CD4511BM_DISPLAY(Dsp_Seg,1);
//	CD4511BM_DISPLAY(Time,Time%3+1);
//	SEG_DISPALY(Time);			//��ʾ����
//	CD4511BM_DISPLAY_DP();
}

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void SEG_DISPALY(u16 time)
{

#ifdef	CD4511BM_DEBUG_TEST
	//1)**********�������ԣ�ʹ��ʱע�͵�
	if((time%100==0)&&(DsplayFlag==1))			//�������ԣ���0��999������ʾ		
	{
		data++;
		if(data>999)
			data=0;
	}
#endif
	//2)**********�ϵ�����ܲ���
	if(DsplayFlag==0)
	{
		if(time%500==0)
			data+=111;
		if(data>999)
#ifdef CD4511BM_DEBUG_TEST
			DsplayFlag=1;
#else
			DsplayFlag=2;
#endif
		CD4511BM_DISPLAY(data,time%3+11);
	}
	//2)**********������������Ϊ������ʾ
	else if(DsplayFlag==1)
		CD4511BM_DISPLAY(data,time%3+1);
	//3)**********������ʾ�����һ��С����1SƵ����
	else
	{
		if(time%500==0)
			CD4511BM_DISPLAY_DP();
	}
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CD4511BM_KEY_FUNC(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//GPIO�ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//1)**********S3�ܽ����ü���ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				//GPIO���ź�			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//GPIOģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO����ٶȣ�����ʱ��Ч
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

}








#endif

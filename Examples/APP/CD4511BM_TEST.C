#ifdef	CD4511BM_TEST


//1）数码管测试指令
//2）小数点整齐显示指令
//3）特殊功能，根据指令确认有无称重与CAN,485通讯

#include "CD4511BM_TEST.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#define	CD4511BM_DEBUG_TEST			//调试时数码管计数显示，正常使用时应该注释掉


u16 Time=0;
u16 data=0;

u8 DsplayFlag=0;			//显示标志，0-开机或者自检时LED显示，1-正常显示数值，2-待机，显示最后位小数点

u8 Sub_Cont=0;
u8 Cont=0;
u8 Key_Cont=0;
u16 Dsp_Seg=0;
u8 Key_Flag=0;
u16 time_cnt=0;

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_TEST_Configuration(void)
{
	SYS_Configuration();											//系统配置 STM32_SYS.H	
	CD4511BM_Configuration();
	CD4511BM_KEY_FUNC();
	PWM_Configuration(TIM2,7200,10000,50);
	SysTick_Configuration(1000);							//系统嘀嗒时钟配置72MHz,单位为uS
}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
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
//	SEG_DISPALY(Dsp_Seg);			//显示管理
	CD4511BM_DISPLAY(Dsp_Seg,Time%3+1);
//	CD4511BM_DISPLAY(Dsp_Seg,2);
//	CD4511BM_DISPLAY(Dsp_Seg,1);
//	CD4511BM_DISPLAY(Time,Time%3+1);
//	SEG_DISPALY(Time);			//显示管理
//	CD4511BM_DISPLAY_DP();
}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SEG_DISPALY(u16 time)
{

#ifdef	CD4511BM_DEBUG_TEST
	//1)**********计数测试，使用时注释掉
	if((time%100==0)&&(DsplayFlag==1))			//计数测试，从0到999自增显示		
	{
		data++;
		if(data>999)
			data=0;
	}
#endif
	//2)**********上电数码管测试
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
	//2)**********除计数测试外为正常显示
	else if(DsplayFlag==1)
		CD4511BM_DISPLAY(data,time%3+1);
	//3)**********待机显示，最后一个小数点1S频率闪
	else
	{
		if(time%500==0)
			CD4511BM_DISPLAY_DP();
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CD4511BM_KEY_FUNC(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//GPIO结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//1)**********S3管脚配置及初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				//GPIO引脚号			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//GPIO模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

}








#endif


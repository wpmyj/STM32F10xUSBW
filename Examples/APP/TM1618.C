#ifdef TM1618

#include "TM1618.H"




/*##############################################################################
################################################################################

********************************************************************************

################################################################################
##############################################################################*/


/******************************MX25L4006E命令定义*******************************/


//sbit stb=P3^4;		//片选，在上升或下降沿初始化串行接口，随后等待接收指令。
//					//STB为低后的第一个字节作为指令，当处理指令时，当前其它处
//					//理被终止。当STB 为高时，CLK 被忽略
////_________________________________________________________________________________________________
//sbit clk=P3^0;		//时钟上升沿输入串行数据。
////__________________________________________________________________________________________________
//sbit dio=P3^1;	  	//在时钟上升沿输入串行数据，从低位开始。

#define clk	PC8
#define	dio	PC9
#define	stb	PC10

#define	SEGEN		PC12
#define SEG1EN	PC10
#define	SEG2EN	PC11

unsigned char seg4[]={0x3F,0X06,0X5B,0X4F,0x66,0X6D,0X7D,0x07,0x7f,0x6f,0x00,0xff};
unsigned char addr[]={0XC0,0XC2,0XC4,0XC6,0XC8,0XCA,0XCC,0XCE};
unsigned char s[8]={0};
unsigned char d[8]={0};
unsigned char flag=0;
		
u16 time=0;
u16 delayt=2000;

#define ADC_TEST_BUFFERSIZE 128


u16 ADCBuffer=0;
u16 Temperature[100]={0};
u8 T_Flag=0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TM1618_Configuration(void)
{	
	SYS_Configuration();
	SysTick_Configuration(10000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	PWM_Configuration(TIM2,7200,200,20);
	TM1618_PinConf();	
	USART_DMA_Configuration(USART1,115200,1,1,(u32*)ADCBuffer,(u32*)ADCBuffer,ADC_TEST_BUFFERSIZE);	//USART_DMA配置
	ADC_TempSensorConfiguration((u32*)&ADCBuffer);																									//STM32内部温度传感器配置
	
	SEGEN=1;
	SEG1EN=1;
	SEG2EN=1;

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TM1618_Server(void)
{
	float Temperature=0.0;
//	u16 temp;
	time++;
	if(time>=10000)
		time=0;
//	Temperature=Get_ADC_Temperature(ADCBuffer);		//获取内部温度传感器温度
//	if((time%200==0)&&(time%400!=0))
//		GPIO_ResetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	if(time%400==0)
//		GPIO_SetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	if(time%2000==0)
	TM1618_DIS(time);
//	
//	temp=Temperature_COV();
//	temp=Get_ADC_Temperature((u16)&temp);		//获取内部温度传感器温度
//	if(time%500==0)

//	if(temp)
//	{
//		temp=Get_ADC_Temperature(ADCBuffer);		//获取内部温度传感器温度
//		TM1618_DIS(temp);
//	}
	

	if(!USART_TX_DMAFlagClear(USART1)&&time%100==0)
	{
		Temperature=Get_ADC_Temperature(ADCBuffer);		//获取内部温度传感器温度
		USART_DMAPrintf(USART1,"当前STM32内部温度为：%6.2f℃\n",Temperature);
	}
//	else if(USART_TX_DMAFlagClear(USART1))
//	{
//		memset((u8*)ADCBuffer,0,ADC_TEST_BUFFERSIZE);			//初始化缓冲
//	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
u16 Temperature_COV(void)
{
	T_Flag++;
	Temperature[T_Flag]=ADCBuffer;
	if(T_Flag>=100)
	{
		u16 ave=0;
		u8 i=0;
		T_Flag=0;
		ave=Temperature[0];
		for(i=1;i<100;i++)
		{
			ave=(ave+Temperature[i])/2;
		}
		return ave;
	}
	return 0;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
void TM1618_PinConf(void)
{
	GPIO_Configuration(GPIOC,GPIO_Pin_12,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEGEN
	GPIO_Configuration(GPIOC,GPIO_Pin_10,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG1EN
	GPIO_Configuration(GPIOC,GPIO_Pin_11,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SE2GEN
	GPIO_Configuration(GPIOC,GPIO_Pin_8,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG_CLK
	GPIO_Configuration(GPIOC,GPIO_Pin_9,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG_DIO
}



//////////////////////写一字节数据////////////////////////
void write(u8 datt)
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	GPIO_ResetBits(GPIOC,GPIO_Pin_9);		//SEG_DIO
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		TM1618_delay(delayt);
		clk=0;
		if(datt&0x01)						 //确认最低位数，从低位开始写入
			dio=1;
		else
			dio=0;
		clk=1;
		datt>>=1;							 //右移一位
		
	}
}

//////////////////////初始化TM1618///////////////////
void int_tm1629a(u16 b)
{
//	stb=1;
	SEG1EN=1;
	SEG2EN=1;
	TM1618_delay(delayt);
	write(0x44);	//固定地址模式
	TM1618_delay(delayt);
//	stb=0;
	SEG1EN=0;
	SEG2EN=0;
	TM1618_delay(delayt);
//	stb=1;
	SEG1EN=1;
	SEG2EN=1;
	TM1618_delay(delayt);
	write(b);	//脉冲宽度设置 0x80（关）<0x88<0x89<0x8a<0x8b<0x8c<0x8d<0x8e<0x8f
	TM1618_delay(delayt);
//	stb=0;
	SEG1EN=0;
	SEG2EN=0;
}
///////////////////////分位数据//////////////////////////////////////
void fe(u16 a)
{
	s[0]=seg4[a/1000];
	s[1]=seg4[a%1000/100];
	s[2]=seg4[a%100/10];
	s[3]=seg4[a%10];
	
	if(a<10)
	{
		s[0]=seg4[10];
		s[1]=seg4[10];
		s[2]=seg4[10];
	}
	else if(100>a&&a>9)
	{
		s[0]=seg4[10];
		s[1]=seg4[10];
	}
	else if(1000>a&&a>99)
		s[0]=seg4[10];
		
}	


////////////////////////显示代码转换////////////////////////////////////////////
void cov(u16 a)
{
	unsigned char i,j;
	fe(a);
	for(i=0;i<8;i++)
//		for(q=0;q<4;q++)
		{
			for(j=0;j<4;j++)
			{
				d[i]<<=1;
				if(s[j]&0x01)
				d[i]|=0x01;
				s[j]>>=1;
				
			}
		}
		
		
	
}
		
void display(u16 a)
{
	u16 i;
	int_tm1629a(0x8a);
	cov(a);
	for(i=0;i<8;i++)
	{
//		stb=1;
		SEG1EN=1;
		SEG2EN=1;
		TM1618_delay(delayt);
		write(addr[i]);
		write(d[i]);
		TM1618_delay(delayt);
//		stb=0;
		SEG1EN=0;
		SEG2EN=0;
	}
	
}



void TM1618_DIS(u16 a)
{
	display(a);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
void TM1618_delay(u16 time)
{
	while(time--);
}

#endif



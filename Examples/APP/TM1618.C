#ifdef TM1618

#include "TM1618.H"




/*##############################################################################
################################################################################

********************************************************************************

################################################################################
##############################################################################*/


/******************************MX25L4006E�����*******************************/


//sbit stb=P3^4;		//Ƭѡ�����������½��س�ʼ�����нӿڣ����ȴ�����ָ�
//					//STBΪ�ͺ�ĵ�һ���ֽ���Ϊָ�������ָ��ʱ����ǰ������
//					//������ֹ����STB Ϊ��ʱ��CLK ������
////_________________________________________________________________________________________________
//sbit clk=P3^0;		//ʱ�����������봮�����ݡ�
////__________________________________________________________________________________________________
//sbit dio=P3^1;	  	//��ʱ�����������봮�����ݣ��ӵ�λ��ʼ��

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
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void TM1618_Configuration(void)
{	
	SYS_Configuration();
	SysTick_Configuration(10000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
	PWM_Configuration(TIM2,7200,200,20);
	TM1618_PinConf();	
	USART_DMA_Configuration(USART1,115200,1,1,(u32*)ADCBuffer,(u32*)ADCBuffer,ADC_TEST_BUFFERSIZE);	//USART_DMA����
	ADC_TempSensorConfiguration((u32*)&ADCBuffer);																									//STM32�ڲ��¶ȴ���������
	
	SEGEN=1;
	SEG1EN=1;
	SEG2EN=1;

}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void TM1618_Server(void)
{
	float Temperature=0.0;
//	u16 temp;
	time++;
	if(time>=10000)
		time=0;
//	Temperature=Get_ADC_Temperature(ADCBuffer);		//��ȡ�ڲ��¶ȴ������¶�
//	if((time%200==0)&&(time%400!=0))
//		GPIO_ResetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	if(time%400==0)
//		GPIO_SetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	if(time%2000==0)
	TM1618_DIS(time);
//	
//	temp=Temperature_COV();
//	temp=Get_ADC_Temperature((u16)&temp);		//��ȡ�ڲ��¶ȴ������¶�
//	if(time%500==0)

//	if(temp)
//	{
//		temp=Get_ADC_Temperature(ADCBuffer);		//��ȡ�ڲ��¶ȴ������¶�
//		TM1618_DIS(temp);
//	}
	

	if(!USART_TX_DMAFlagClear(USART1)&&time%100==0)
	{
		Temperature=Get_ADC_Temperature(ADCBuffer);		//��ȡ�ڲ��¶ȴ������¶�
		USART_DMAPrintf(USART1,"��ǰSTM32�ڲ��¶�Ϊ��%6.2f��\n",Temperature);
	}
//	else if(USART_TX_DMAFlagClear(USART1))
//	{
//		memset((u8*)ADCBuffer,0,ADC_TEST_BUFFERSIZE);			//��ʼ������
//	}
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
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
*������			:	function
*��������		:	��������˵��
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
*******************************************************************************/
void TM1618_PinConf(void)
{
	GPIO_Configuration(GPIOC,GPIO_Pin_12,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEGEN
	GPIO_Configuration(GPIOC,GPIO_Pin_10,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG1EN
	GPIO_Configuration(GPIOC,GPIO_Pin_11,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SE2GEN
	GPIO_Configuration(GPIOC,GPIO_Pin_8,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG_CLK
	GPIO_Configuration(GPIOC,GPIO_Pin_9,	GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//SEG_DIO
}



//////////////////////дһ�ֽ�����////////////////////////
void write(u8 datt)
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_8);			//SEG_CLK
//	GPIO_ResetBits(GPIOC,GPIO_Pin_9);		//SEG_DIO
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		TM1618_delay(delayt);
		clk=0;
		if(datt&0x01)						 //ȷ�����λ�����ӵ�λ��ʼд��
			dio=1;
		else
			dio=0;
		clk=1;
		datt>>=1;							 //����һλ
		
	}
}

//////////////////////��ʼ��TM1618///////////////////
void int_tm1629a(u16 b)
{
//	stb=1;
	SEG1EN=1;
	SEG2EN=1;
	TM1618_delay(delayt);
	write(0x44);	//�̶���ַģʽ
	TM1618_delay(delayt);
//	stb=0;
	SEG1EN=0;
	SEG2EN=0;
	TM1618_delay(delayt);
//	stb=1;
	SEG1EN=1;
	SEG2EN=1;
	TM1618_delay(delayt);
	write(b);	//����������� 0x80���أ�<0x88<0x89<0x8a<0x8b<0x8c<0x8d<0x8e<0x8f
	TM1618_delay(delayt);
//	stb=0;
	SEG1EN=0;
	SEG2EN=0;
}
///////////////////////��λ����//////////////////////////////////////
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


////////////////////////��ʾ����ת��////////////////////////////////////////////
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
*������			:	function
*��������		:	��������˵��
*����				: 
*���				:	��
*����ֵ			:	��
*����				:
*���ú���		:
*�����ú���	:
*******************************************************************************/
void TM1618_delay(u16 time)
{
	while(time--);
}

#endif


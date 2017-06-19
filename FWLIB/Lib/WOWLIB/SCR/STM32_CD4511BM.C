/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/



#include "STM32_CD4511BM.H"
//#include "STM32F10x_BitBand.H"


/* Exported types ------------------------------------------------------------*/
//#define GPIOxLE				GPIOB
//#define GPIO_Pin_LE

//#define GPIOxBI				GPIOB
//#define GPIO_Pin_BI

//#define GPIOxLT				GPIOB
//#define GPIO_Pin_LT

#define GPIOxA				GPIOB
#define GPIO_Pin_A		GPIO_Pin_0

#define GPIOxB				GPIOB
#define GPIO_Pin_B		GPIO_Pin_1

#define GPIOxC				GPIOB
#define GPIO_Pin_C		GPIO_Pin_2

#define GPIOxD				GPIOB
#define GPIO_Pin_D		GPIO_Pin_3



#define GPIOxS1				GPIOB
#define GPIO_Pin_S1		GPIO_Pin_5

#define GPIOxS2				GPIOB
#define GPIO_Pin_S2		GPIO_Pin_14

#define GPIOxS3				GPIOB
#define GPIO_Pin_S3		GPIO_Pin_15	

//u8 SEGDSP=0;
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
	//1)**********LE管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOx,&GPIO_InitStructure);						//GPIO初始化
	
	//2)**********BI管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOx,&GPIO_InitStructure);						//GPIO初始化
	
	//3)**********BT管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOx,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********A管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_A;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOA,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********B管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_B;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxB,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********C管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_C;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxC,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********D管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_D;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxD,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********S1管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_S1;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxS1,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********S2管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_S2;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxS2,&GPIO_InitStructure);						//GPIO初始化
//	
//	//1)**********S3管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_S3;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOxS3,&GPIO_InitStructure);						//GPIO初始化
	
	//1)**********S3管脚配置及初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_14|GPIO_Pin_15;				//GPIO引脚号			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

}
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_DISPLAY(u16 num,u8 wei)
{
//	GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
//	GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
//	num=6;
//	num=0XFFF0|num;
//	u16 temp=0;
//	num=(0XFFE0&GPIO_ReadOutputData(GPIOB))|(num%100);
//	GPIO_ReadOutputData(GPIOB);
	//1)**********S3管脚配置及初始化
//	GPIO_SetBits(GPIOB,GPIO_Pin_4);				//DP
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);				//S1
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//S2
//	GPIO_SetBits(GPIOB,GPIO_Pin_15);			//S3
	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
//	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
//	GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3
//	
//	GPIO_ResetBits(GPIOB, GPIO_Pin_0);			//A
//	GPIO_ResetBits(GPIOB, GPIO_Pin_1);			//B
//	GPIO_ResetBits(GPIOB, GPIO_Pin_2);			//C
//	GPIO_ResetBits(GPIOB, GPIO_Pin_3);			//D
	
//	GPIO_SetBits(GPIOB, GPIO_Pin_0);			//A
//	GPIO_SetBits(GPIOB, GPIO_Pin_1);			//B
//	GPIO_SetBits(GPIOB, GPIO_Pin_2);			//C
//	GPIO_SetBits(GPIOB, GPIO_Pin_3);			//D
//	GPIO_Write(GPIOB,num);
	
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);				//S1
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//S2
//	GPIO_SetBits(GPIOB,GPIO_Pin_15);			//S3


	//1)**********百位显示
	if(wei%10==3)				//S3百位
	{
		num=num/100;
		if((num==0)&&((wei/10)<3))
			num=0x0F;
		
		num=(0XFFE0&GPIO_ReadOutputData(GPIOB))|num;
		GPIO_Write(GPIOB,num);
		
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3
		
		GPIO_SetBits(GPIOB,GPIO_Pin_5);					//S1
	}
	
	//1)**********十位显示		
	else if(wei%10==2)		//S2十位
	{
		if((num/100==0)&&(num%100/10==0)&&((wei/10)==0))
			num=0x0F;
		else
			num=num%100/10;
		
		num=(0XFFE0&GPIO_ReadOutputData(GPIOB))|num;
		GPIO_Write(GPIOB,num);

		GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3

		GPIO_SetBits(GPIOB,GPIO_Pin_14);				//S2
	}
	//1)**********个位显示	
	else if(wei%10==1)			//S1个位
	{
		num=num%10;
		
		num=(0XFFE0&GPIO_ReadOutputData(GPIOB))|num;
		GPIO_Write(GPIOB,num);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3

		GPIO_SetBits(GPIOB,GPIO_Pin_15);				//S3
	}
	else if(wei==0)
	{
		num=(0XFFE0&GPIO_ReadOutputData(GPIOB))|0x0F;
		GPIO_Write(GPIOB,num);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3

		GPIO_SetBits(GPIOB,GPIO_Pin_15);				//S3
	}
	

	
//	GPIO_SetBits(GPIOB, GPIO_Pin_0);			//A
//	GPIO_SetBits(GPIOB, GPIO_Pin_1);			//B
//	GPIO_ResetBits(GPIOB, GPIO_Pin_2);			//C
//	GPIO_ResetBits(GPIOB, GPIO_Pin_3);			//D
//	GPIO_SetBits(GPIOB,GPIO_Pin_4);				//DP
////	GPIO_Write(GPIOB,num);
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);				//S1
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//S2
//	GPIO_SetBits(GPIOB,GPIO_Pin_15);			//S3	
	
}
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_DISPLAY_DP(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);				//S1
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);			//S2
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//S3
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0);			//A
	GPIO_SetBits(GPIOB, GPIO_Pin_1);			//B
	GPIO_SetBits(GPIOB, GPIO_Pin_2);			//C
	GPIO_SetBits(GPIOB, GPIO_Pin_3);			//D
	
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4))
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);				//DP
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_4);				//DP
	}
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);				//S1		//个位
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);			//S2		//十位
	GPIO_SetBits(GPIOB,GPIO_Pin_15);			//S3		//百位
}





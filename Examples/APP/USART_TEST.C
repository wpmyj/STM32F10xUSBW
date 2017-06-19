#ifdef USART_TEST

#include "USART_TEST.H"

#include "STM32_USART.H"
#include "STM32_DMA.H"
#include "STM32_TIM.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"

#define	DMA1_BufferSize 300		//DMA1缓冲大小

u32	num_temp=0;
u16	tema=0;
u8	USART_TX_FLAG=0;
u8	USART_RX_FLAG=0;
u32 DMASTAST=0;
ErrorStatus status = ERROR;



u8 Usart_RXBuffer[DMA1_BufferSize]={0};
u8 Usart_TXBuffer[DMA1_BufferSize]={0};
u8 num=0;
u8 ch[120]="USART_BASIC_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority)\n";

//u8 itf=0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Usart_test_Configuration(void)
{
	//1）系统配置---打开系统时钟
	SYS_Configuration();									//系统配置---打开系统时钟 STM32_SYS.H
	//2）串口配置
	USART_DMA_Configuration(USART1,115200,1,1,(u32*)Usart_RXBuffer,(u32*)Usart_TXBuffer,DMA1_BufferSize);	//USART_DMA配置
	//3）系统运行指示灯打开---此处用TIM2-CH1 PWM输出，减少单片机工作负荷
	PWM_OUT(TIM2,PWM_OUTChannel1,200000,2);	//PWM设定-20161127版本
	//4）系统嘀嗒时钟打开---做周期性中断扫描
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	//————————————————配置完成
//	USART_DMASend(USART2,"测试开始\n");
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Usart_test_Server(void)
{
//	ErrorStatus status = ERROR;
//	u32 num=0;
//	num_temp=USART_RX_FlagClear(USART1);						//清除串口DMA发送全局中断标志
//	num_temp=USART_RX_FlagClearADDR(USART1,(u32*)Usart_Test_Buffer);
	
//	status=USART_TX_DMAFlagClear(USART1);						//清除串口DMA发送全局中断标志
	num_temp=USART_RX_FlagClear(USART1);						//清除串口DMA发送全局中断标志
	status=USART_TX_DMAFlagClear(USART1);						//清除串口DMA发送全局中断标志
//	DMASTAST=*(vu32*)DMA1_Channel4_BASE;
//	if(num_temp!=0)
//	{
//		memcpy(Usart_TXBuffer,Usart_RXBuffer,num_temp);
//		USART_DMAPrintf(USART1,"接收到的数据个数:%d;接收到的数据:%s\n",num_temp,Usart_TXBuffer);
//		tema=0;
//	}
//	else if(!USART_TX_DMAFlagClear(USART1))
//	{
//		memset(Usart_TXBuffer,0,DMA1_BufferSize);			//初始化缓冲
//		if(tema<=100)
//		{		
//			USART_DMAPrintf(USART1,"测试开始:%d\n",tema);
//			tema++;
//		}
//	}
	
	if(num_temp)
	{
//		num_temp=USART_RX_FlagClear(USART1);						//清除串口DMA发送全局中断标志
		memcpy(Usart_TXBuffer,Usart_RXBuffer,num_temp);
		USART_DMASend(USART1,(u32*)Usart_TXBuffer,num_temp);
//		num_temp=0;
	}
//	else if(!USART_TX_DMAFlagClear(USART1))
//	{
//		memset(Usart_Test_Buffer,0,DMA1_BufferSize);			//初始化缓冲
//		if(tema<=100)
//		{		
//			USART_DMAPrintf(USART1,"测试开始:%d\n",tema);
////			USART_DMAPrintf(USART1,"测试开始:%s\n",ch);
////			printf("测试开始:%d\n",tema);
//			tema++;
//		}
////		else
////			tema=0;
//	}
	
/*
	ErrorStatus status = ERROR;
	status=USART_TX_DMAFlagClear(USART1);						//清除串口DMA发送全局中断标志
	USART_RX_FlagClear(USART1);				//清除串口接收中断标志
	if(status==SUCCESS)
	{
//		free(USART_BUFFER);						//释放动态空间
	}
	else
	{
		if(tema<=100)
		{		
//			USART_DMAPrintf(USART1,"测试开始:%d\n",tema);
			USART_DMAPrintf(USART1,"测试开始:%s\n",ch);
//			printf("测试开始:%d\n",tema);
			tema++;
		}
		else
			tema=0;
	}
*/
//	IWDG_Feed();
/*	//USART1
	if(USART_GetITStatus(USART1,USART_IT_IDLE))
  {
			USART_ClearITPendingBit(USART1,USART_IT_IDLE); 					//清除空闲串口标志位
			num = USART1->DR; 												//读出数据以完成清除标志
			DMA_Cmd(DMA1_Channel5,DISABLE);    										//关闭接收DMA
			num = DMA1_BufferSize -  DMA_GetCurrDataCounter(DMA1_Channel6);	//得到真正接收数据个数
			DMA1_Channel4->CNDTR =num;										//设定待发送数据个数
			DMA1_Channel5->CNDTR=DMA1_BufferSize;       					//重新设置接收数据个数				
			DMA_Cmd(DMA1_Channel5,ENABLE);  								//开启接收DMA			
			DMA_Cmd(DMA1_Channel4,ENABLE);									//DMA发送开启
			tema=0;
	}
	else if(DMA_GetFlagStatus(DMA1_FLAG_GL4))
	{
		DMA_ClearFlag(DMA1_FLAG_GL4);
		DMA_Cmd(DMA1_Channel4,DISABLE);			//DMA发送关闭
		free(USART_BUFFER);						//释放动态空间
	}
	else
	{
		if(tema<=100)
		{		
//			USART_DMASend(USART2,"测试开始:%d\n",tema);
			printf("测试开始:%d\n",tema);
			tema++;
		}
	}
*/
/*
	//USART2
	if(USART_GetITStatus(USART2,USART_IT_IDLE))
  {
			USART_ClearITPendingBit(USART2,USART_IT_IDLE); 					//清除空闲串口标志位
			num = USART2->DR; 												//读出数据以完成清除标志
			DMA_Cmd(DMA1_Channel6,DISABLE);    										//关闭接收DMA
			num = DMA1_BufferSize -  DMA_GetCurrDataCounter(DMA1_Channel6);	//得到真正接收数据个数
			DMA1_Channel7->CNDTR =num;										//设定待发送数据个数
			DMA1_Channel6->CNDTR=DMA1_BufferSize;       	//重新设置接收数据个数				
			DMA_Cmd(DMA1_Channel6,ENABLE);  							//开启接收DMA			
			DMA_Cmd(DMA1_Channel7,ENABLE);								//DMA发送开启
			tema=0;
	}
	if(DMA_GetFlagStatus(DMA1_FLAG_TC7))
	{
		DMA_ClearFlag(DMA1_FLAG_TC7);
		DMA_Cmd(DMA1_Channel7,DISABLE);			//DMA发送关闭
		free(USART_BUFFER);						//释放动态空间
	}
	else
	{
		if(tema<=1000)
		{		
			USART_DMASend(USART2,"测试开始:%d\n",tema);
//			printf("测试开始:%d\n",tema);
			tema++;
		}
		else
			tema=0;
	}
*/

//	if(tema<30000)
//		tema++;
//	else
//		tema=0;
	
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC7))
//	{
//		DMA_ClearFlag(DMA1_FLAG_TC7);
//		DMA_Cmd(DMA1_Channel7,DISABLE);			//DMA发送关闭
//		free(USART_BUFFER);									//释放动态空间
//	}
//	else
//	{
//			USART_DMASend(USART2,"测试开始:%d\n",tema);
////			printf("测试开始:%d\n",tema);
//	}
//	if(num!=0)
//	{
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
////		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//		GPIO_Write(GPIOE,0XAAAA);
//		num=0;
//	}
//	else
//	{
////		GPIO_SetBits(GPIOA,GPIO_Pin_2);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		GPIO_Write(GPIOE,0X5555);
//		num=1;
//	}

}

#endif


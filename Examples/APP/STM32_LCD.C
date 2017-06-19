#ifdef STM32_LCD

#include "STM32_LCD.H"

//#define SDCardTest
//#define GT32L32M0180Test	
//


GT32L32_Info_TypeDef	GT32L32_Info;			//字符信息

u16 millisecond=0;
u8 hour=20,min=43,second=00;

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void STM32_LCD_Configuration(void)
{	
	SYS_Configuration();				//系统配置
	SSD1963_Configuration();			//LCD接口配置
	GT32L32_Configuration();
	LCD_PrintfString(0,16,"SD_TYPE IS SD_TYPE_V2HC");		//后边的省略号就是可变参数
//	LCD_PrintfStringGT(0,32,32,"后边的省略号就是可变参数~!@#$%^&*()_+{}:<>?|");		//后边的省略号就是可变参数
	LCD_PrintfStringGT(0,64,32,"1234567890SD_TYPE IS SD_TYPE_V2HC");		//后边的省略号就是可变参数
	Draw_Circle(400,240,100);
	LCD_PrintfStringGT(300,230,32,"%02d-%02d-%02d-%03d",hour,min,second,millisecond);		//后边的省略号就是可变参数
//	LCD_PrintfStringGT(0,256,32,"运行计时：");		//后边的省略号就是可变参数
//	LCD_PrintfStringGT(300,256,32,"%02d:%02d:%02d:%02d",hour,min,second,millisecond);		//后边的省略号就是可变参数
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void STM32_LCD_Server(void)
{
	millisecond++;
	if(millisecond>999)
	{
		millisecond=0;
		second++;
		if(second>59)
		{
			second=0;
			min++;			
			if(min>59)
			{
				min=0;
				hour++;
				if(hour>23)
				{
					hour=0;
				}
				LCD_PrintfStringGT(300,230,32,"%02d",hour);		//后边的省略号就是可变参数
			}
			LCD_PrintfStringGT(348,230,32,"%02d",min);		//后边的省略号就是可变参数
		}
		LCD_PrintfStringGT(396,230,32,"%02d",second);		//后边的省略号就是可变参数
	}
//	LCD_PrintfStringGT(444,230,32,"%03d",millisecond);		//后边的省略号就是可变参数
}

/*******************************************************************************
*函数名		:	LCD_ShowString
*功能描述	:	显示字符串高通字库
*输入			: x,y:起点坐标
						*p:字符串起始地址
						用16字体
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
unsigned int LCD_PrintfStringGT(u16 x,u16 y,u8 font,const char *format,...)				//后边的省略号就是可变参数
{ 	
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//    	va_start( ap, format );
//    	vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	*Char_Buffer;

	//1)**********获取数据宽度
	u16 num=strlen((const char*)format);		//获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize;
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args;                                        
	//4)**********申请动态空间
	Char_Buffer = (char*)malloc(sizeof(char) * num);
	if(Char_Buffer==NULL)
	{
		Char_Buffer=NULL;
		return 0;
	}
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsprintf(Char_Buffer, format, args);
	num=BufferSize;
	//7)**********结束可变参数的获取
	va_end(args);                                      		
	//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
//	while(*Char_Buffer!='\0')
	while(num>0)
	{ 
		unsigned char	*char_GT32L32;
		unsigned char dst=*Char_Buffer;
		
		if(dst>0x80)		//双字节--汉字
		{
			u16 word=dst<<8;
			Char_Buffer++;
			dst=*Char_Buffer;
			word=word|dst;
			//显示超限判断
			if(x>LCD_W-16)
			{
				x=0;
				y+=32;
			}
			if(y>LCD_H-32)
			{
				y=x=0;
				LCD_Clear(RED);
			}
			//字体大小判断
			if(font==12)
			{
				GT32L32_Info.GT32L32_BaseAddr=GB18030_BaseAddr_hz12x12;
			}
			else if(font==16)
			{
				GT32L32_Info.GT32L32_BaseAddr=GB18030_BaseAddr_hz16x16;
			}
			else if(font==24)
			{
				GT32L32_Info.GT32L32_BaseAddr=GB18030_BaseAddr_hz24x24;
			}
			else if(font==32)
			{
				GT32L32_Info.GT32L32_BaseAddr=GB18030_BaseAddr_hz32x32;
			}
			
			GT32L32_Get_Info(word,&GT32L32_Info);
			
			char_GT32L32 = (unsigned char*)malloc(GT32L32_Info.GT32L32_BufferSize);
			
			GT32L32_ReadBuffer(GT32L32_Info.GT32L32_Address,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);	//从字库中读数据函数
			LCD_ShowCharGT(x,y,font,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);
			
			if(font==12)
			{
				x+=12;
			}
			else if(font==16)
			{
				x+=16;
			}
			else if(font==24)
			{
				x+=24;
			}
			else if(font==32)
			{
				x+=32;
			}
			Char_Buffer++;
			num--;
			num--;			
			free(char_GT32L32);		//发送完成后注意应该释放缓冲区：free(Char_Buffer); 
		}
		else		//单字节
		{
			if(x>LCD_W-16)
			{
				x=0;
				y+=32;
			}
			if(y>LCD_H-32)
			{
				y=x=0;
				LCD_Clear(RED);
			}
		
			if(font==12)
			{
				GT32L32_Info.GT32L32_BaseAddr=ASCII_BaseAddr_zfs16x32;
			}
			else if(font==16)
			{
				GT32L32_Info.GT32L32_BaseAddr=ASCII_BaseAddr_zfs16x32;
			}
			else if(font==24)
			{
				GT32L32_Info.GT32L32_BaseAddr=ASCII_BaseAddr_zfs16x32;
			}
			else if(font==32)
			{
				GT32L32_Info.GT32L32_BaseAddr=ASCII_BaseAddr_zfs16x32;
			}
			
			
			
			GT32L32_Get_Info(dst,&GT32L32_Info);
			
			char_GT32L32 = (unsigned char*)malloc(GT32L32_Info.GT32L32_BufferSize);
			
			GT32L32_ReadBuffer(GT32L32_Info.GT32L32_Address,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);	//从字库中读数据函数
			LCD_ShowCharGT(x,y,font,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);
			
			if(font==12)
			{
				x+=6;
			}
			else if(font==16)
			{
				x+=8;
			}
			else if(font==24)
			{
				x+=12;
			}
			else if(font==32)
			{
				x+=16;
			}
			
			Char_Buffer++;
			num--;
			free(char_GT32L32);		//发送完成后注意应该释放缓冲区：free(Char_Buffer);
		}
		
//		LCD_ShowCharGT(x,y,1,STM32_DSP_Buffer);
//		GT32L32_Get_Info(0xB0A1,&GT32L32_Info);
//		GT32L32_ReadBuffer(u32 address,u16 len,unsigned char *Buffer);	//从字库中读数据函数
//		LCD_ShowCharGT(x,y,1,STM32_DSP_Buffer);
//		LCD_ShowCharGT(664,300,1,STM32_DSP_Buffer);
//		GT32L32_GetGB18030_16(0xb0,0xa1,0,0,Char_Buffer);
//		LCD_ShowCharGT(x,y,*Char_Buffer,0);		
	}
	//9)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
	Char_Buffer-=BufferSize;
	free(Char_Buffer);		//发送完成后注意应该释放缓冲区：free(Char_Buffer); 
	return BufferSize;
}

#endif

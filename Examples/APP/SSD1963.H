#ifndef __SSD1963_H
#define __SSD1963_H


#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"
#include "STM32_GPIO.H"
#include "font.h"

#include	"stdio.h"			//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间


#define SSD1963
#define SSD1963_BITBAND
//#include "STM32_PWM.H"
//#include "STM32_SYSTICK.H"
//#include "STM32_GPIO.H"
//#include "STM32_EXTI.H"

//#include "sys\sys.h"
/* http://ttmcu.taobao.com 雨亭电子
代码测试环境:JME-2核心板+1T指令周期的STC单片机（51内核STC12LE5A60S2)+33M晶振	  单片机工作电压3.3V
程序默认IO连接方式：
控制线：RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^2;
数据线: DB0-DB7依次连接P0^0-P0^7;  DB8-DB15依次连接P2^0-P2^7;（8位模式下DB0-DB7可以不连接）
触摸功能连接方式：(不使用触摸可不连接)
D_CLK-P1^7;  D_CS-P1^4;  D_DIN-P3^0;  D_OUT-P3^1;  D_PENIRQ-P3^4;
*/ 
 //定义LCD的尺寸	
#define LCD_W 800
#define LCD_H 480


#define	Bus_16        //16位数据模式,如果使用8位模式，请注释此语句，如果使用16位模式，请打开此句,修改8位模式之前，请确认你手里的模块是否是8位总线接口
#define ShowCharAscii	//二维数组查询
//IO连接
//#define	LCD_DataPortH P2     //高8位数据口,8位模式下只使用高8位 
//#define	LCD_DataPortL P0     //低8位数据口	,8位模式下低8位可以不接线,请确认P0口已经上拉10K电阻,不宜太小，最小4.7K,推荐10K.


//画笔颜色
#define WHITE         	 	0xFFFF
#define BLACK         	 	0x0000	  
#define BLUE         	 		0x001F  
#define BRED             	0XF81F
#define GRED 			 				0XFFE0
#define GBLUE							0X07FF
#define RED           	 	0xF800
#define MAGENTA       	 	0xF81F
#define GREEN         	 	0x07E0		//0X07E0
#define CYAN          	 	0x7FFF
#define YELLOW        	 	0xFFE0
#define BROWN 			 			0XBC40 //棕色
#define BRRED 			 			0XFC07 //棕红色
#define GRAY  			 			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 	0X01CF	//深蓝色
#define LIGHTBLUE      	 	0X7D7C	//浅蓝色  
#define GRAYBLUE       	 	0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 	0X841F //浅绿色
#define LGRAY 			 			0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           	0X2B12 //浅棕蓝色(选择条目的反色)


//sbit LCD_RS = P3^5;  		 //数据/命令切换
//sbit LCD_WR = P3^6;		  //写控制
//sbit LCD_RD =P3^7;		     //读控制
//sbit LCD_CS=P1^0;		//片选	
//sbit LCD_REST = P1^2;	      //复位 


//****************************管脚定义Start************************







#ifdef SSD1963

	#define	SSD1963_BACKLIGHT_PORT	GPIOC
	#define SSD1963_BACKLIGHT_PIN		GPIO_Pin_0

	#define SSD1963_RD_PORT					GPIOC
	#define SSD1963_RD_PIN					GPIO_Pin_1

	#define SSD1963_REST_PORT				GPIOC
	#define SSD1963_REST_PIN				GPIO_Pin_2		//复位	0-复位

	#define SSD1963_DC_PORT					GPIOC
	#define SSD1963_DC_PIN					GPIO_Pin_3		//数据/命令切换	//0-命令，1-数据

	#define SSD1963_WR_PORT					GPIOC					//读写数据控制		//0-写，1-读
	#define SSD1963_WR_PIN					GPIO_Pin_4

	#define SSD1963_CS_PORT					GPIOC					//使能 	0-启用，1-禁止
	#define SSD1963_CS_PIN					GPIO_Pin_5			

	#define SSD1963_DATABUS_PORT		GPIOE
	#define SSD1963_DATABUS_PIN			GPIO_Pin_All

	//____________GPIO控制定义
	#ifdef		SSD1963_BITBAND		//*************位绑定
			#include "STM32F10x_BitBand.H"
		//____________背光控制定义
			#define SSD1963_BACKLIGHT_ON						PC0=1			//开背光
			#define SSD1963_BACKLIGHT_OFF						PC0=0			//关背光
		//____________RD控制定义
			#define SSD1963_RD_H								PC1=1			//取消片选
			#define SSD1963_RD_L								PC1=0			//片选
		//____________REST控制定义
			#define SSD1963_REST								PC2=0			//复位
			#define SSD1963_SET									PC2=1			//运行
		//____________写数据/命令(D/C)控制定义
			#define SSD1963_DC_Data							PC3=1			//传数据
			#define SSD1963_DC_Command					PC3=0			//传命令
		//____________读写数据（W/R）控制定义
			#define SSD1963_WR_Write						PC4=0			//写数据
			#define SSD1963_WR_Read							PC4=1			//读数据
		//____________使能控制定义
			#define SSD1963_CS_Disable					PC5=1			//取消片选
			#define SSD1963_CS_Enable						PC5=0			//片选
	#else		//*************未进行位绑定
		//____________背光控制定义
			#define LCD_BACKLIGHT_ON						GPIO_SetBits(SSD1963_BACKLIGHT_PORT,		SSD1963_BACKLIGHT_PIN)			//开背光
			#define SSD1963_BACKLIGHT_OFF				GPIO_ResetBits(SSD1963_BACKLIGHT_PORT,	SSD1963_BACKLIGHT_PIN)			//关背光
		//____________RD控制定义
			#define SSD1963_RD_H								GPIO_SetBits(SSD1963_RD_PORT,			SSD1963_RD_PIN)			//取消片选
			#define SSD1963_RD_L								GPIO_ResetBits(SSD1963_RD_PORT,		SSD1963_RD_PIN)		//使能片选
		//____________REST控制定义
			#define SSD1963_REST								GPIO_ResetBits(SSD1963_REST_PORT,	SSD1963_REST_PIN)		//低电平
			#define SSD1963_SET									GPIO_SetBits(SSD1963_REST_PORT,		SSD1963_REST_PIN)			//高电平
		//____________写数据/命令(D/C)控制定义
			#define SSD1963_DC_Command					GPIO_ResetBits(SSD1963_REST_PORT,	SSD1963_DC_PIN)		//低电平
			#define SSD1963_DC_Data							GPIO_SetBits(SSD1963_REST_PORT,		SSD1963_DC_PIN)			//高电平
		//____________读写数据（W/R）控制定义
			#define SSD1963_WR_Write						GPIO_ResetBits(SSD1963_WR_PORT,		SSD1963_WR_PIN)		//低电平
			#define SSD1963_WR_Read							GPIO_SetBits(SSD1963_WR_PORT,			SSD1963_WR_PIN)			//高电平
		//____________使能控制定义
			#define SSD1963_CS_Disable					GPIO_SetBits(SSD1963_CS_PORT,			SSD1963_CS_PIN)			//高电平
			#define SSD1963_CS_Enable						GPIO_ResetBits(SSD1963_CS_PORT,		SSD1963_CS_PIN)		//低电平
			
		
	#endif
#endif






#define OFF 0
#define	ON	1

#define Status_L	0
#define Status_H	1



#define LCD_HDP 799			//水平像素点个数
#define LCD_HT	928			//显示时长 928
#define LCD_HPS	46			//消影时长		46
#define LCD_LPS	15			//15
#define LCD_HPW	48			//48

#define LCD_VDP	479			//垂直像素点个数
#define LCD_VT	525
#define LCD_VPS	16
#define LCD_FPS	8
#define LCD_VPW	16

#define	LCD_LR	0X05		//左向右扫描
#define	LCD_RL	0X04		//左向右扫描
#define	LCD_UD	0X04		//上往下扫描
#define	LCD_DU	0X06		//下往上扫描

//--------------------SD卡命令
#define	SD_CMD0	0X40;

//****************************管脚定义End**************************

//****************************控制定义Start************************
//--------------背光  //高电平---开背光
//#define LCD_BACKLIGHT(n)	{if(0)	GPIO_ResetBits(LCD_BACKLIGHT_PORT,	LCD_BACKLIGHT_PIN);	else	GPIO_SetBits(LCD_BACKLIGHT_PORT,	LCD_BACKLIGHT_PIN);}

//--------------读控制 //低电平 8080模式，读选通信号
//#define LCD_RD(n)	{if(0)	GPIO_ResetBits(LCD_RD_PORT,	LCD_RD_PIN);	else	GPIO_SetBits(LCD_RD_PORT,	LCD_RD_PIN);}

//--------------复位  //低电平有效
//#define LCD_REST(n)	{if(0)	GPIO_ResetBits(LCD_REST_PORT,	LCD_REST_PIN);	else	GPIO_SetBits(LCD_REST_PORT,	LCD_REST_PIN);}
//#define LCD_REST(0)	GPIO_ResetBits(LCD_REST_PORT,	LCD_REST_PIN)
//#define LCD_REST(1)	GPIO_SetBits(LCD_REST_PORT,	LCD_REST_PIN)

//--------------数据/命令切换   //数据--高电平//命令--低电平
//#define LCD_RS(n)	{if(0)	GPIO_ResetBits(LCD_RS_PORT,	LCD_RS_PIN);	else	GPIO_SetBits(LCD_RS_PORT,	LCD_RS_PIN);}  		 //数据/命令切换

//--------------写控制  	//0--写开启，1--写关闭
//#define LCD_WR(n)	{if(0)	GPIO_ResetBits(LCD_WR_PORT,	LCD_WR_PIN);	else	GPIO_SetBits(LCD_WR_PORT,	LCD_WR_PIN);}

//--------------片选，//芯片使能--低电平有效
//#define LCD_CS(n)	{if(0)	GPIO_ResetBits(LCD_CS_PORT,	LCD_CS_PIN);	else	GPIO_SetBits(LCD_CS_PORT,	LCD_CS_PIN);}

//****************************控制定义End**************************



//extern	char *Char_Buffer;
extern  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void delayms(u16 xms);

void SSD1963_Configuration(void);		//管脚初始化

void LCD_REST(void);					//复位

void LCD_Writ_Bus(unsigned short BUS_DATA);   //并行数据写入函数
void LCD_WR_DATA8(char VH,char VL); //发送数据-8位参数
void LCD_WR_DATA8(char VH,char VL); //发送数据-8位参数
	
//void Lcd_Init(void); 
void Lcd_Init0(void);
void LCD_Clear(u16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
//void LCD_WR_DATA8(char VH,char VL); //发送数据-8位参数
void LCD_WR_DATA(unsigned short data);				//写数据
void LCD_WR_COMMAND(unsigned short Command);			//写命令

void LCD_DrawPoint(u16 x,u16 y);//画点
void LCD_DrawPoint_big(u16 x,u16 y);//画一个大点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
void Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowCharGT(u16 x,u16 y,u8 font,u8 num,u8 *Buffer);		//高通字库测试程序
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//显示数字
void LCD_ShowEn(u16 x,u16 y,u32 num);	//显示单字节字符
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//显示2个数字串，包含数字
unsigned int LCD_PrintfString(u16 x,u16 y,const char *format,...);			//后边的省略号就是可变参数

void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //显示一个字符串,16字体
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);
void RGB888ToRGB565(unsigned char Color_R,unsigned char Color_G,unsigned char Color_B,u16 *RGB565);			//RGB888转RGB565颜色(分别取高位)


void SSD1963_Configuration(void);
void SSD1963_Server(void);


#endif




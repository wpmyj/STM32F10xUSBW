//#ifdef	SSD1963

/********************************************************************************
***SSD1963 LCD��������
********************************************************************************/
#include "SSD1963.H"

//#include <reg51.h>
//#include "intrins.h"
//#include "font\font.h"
//#include "sys\sys.h"
//#include "lcd\lcd.h"
/* http://ttmcu.taobao.com ��ͤ����
������Ի���:JME-2���İ�+1Tָ�����ڵ�STC��Ƭ����51�ں�STC12LE5A60S2)+33M����	  ��Ƭ��������ѹ3.3V
����Ĭ��IO���ӷ�ʽ��
�����ߣ�RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^2;
������: DB0-DB7��������P0^0-P0^7;  DB8-DB15��������P2^0-P2^7;��8λģʽ��DB0-DB7���Բ����ӣ�
�����������ӷ�ʽ��(��ʹ�ô����ɲ�����)
D_CLK-P1^7;  D_CS-P1^4;  D_DIN-P3^0;  D_OUT-P3^1;  D_PENIRQ-P3^4;
*/
u16 BACK_COLOR=GREEN;		//����ɫ
u16 POINT_COLOR=BLUE;   //����ɫ

//u16  HDP=800;
//u16  HT=928;
//u16  HPS=46;
//u16  LPS=15;
//u8   HPW=48;

//u16  VDP=480;
//u16  VT=525;
//u16  VPS=16;
//u16  FPS=8;
//u8   VPW=16;

//char *Char_Buffer;
unsigned char hanzidata;
/*******************************************************************************
*������		:	LCD_Writ_Bus
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void delayms(u16 xms)
{
	while(xms--);
}
/*******************************************************************************
*������		:	SSD1963_Configuration
*��������	:	�ܽų�ʼ��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void SSD1963_Configuration(void)
{
	//-----------��STM_GPIO���ó���
//	GPIO_Configuration(SSD1963_RD_PORT,					SSD1963_RD_PIN,					GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//RD
//	GPIO_Configuration(SSD1963_REST_PORT,				SSD1963_REST_PIN,				GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//REST
//	GPIO_Configuration(SSD1963_DC_PORT,					SSD1963_DC_PIN,					GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//RS
//	GPIO_Configuration(SSD1963_WR_PORT,					SSD1963_WR_PIN,					GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//WR
//	GPIO_Configuration(SSD1963_CS_PORT,					SSD1963_CS_PIN,					GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//RS
//	GPIO_Configuration(SSD1963_DATABUS_PORT,		SSD1963_DATABUS_PIN,		GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//WR
//	GPIO_Configuration(SSD1963_BACKLIGHT_PORT,	SSD1963_BACKLIGHT_PIN,	GPIO_Mode_Out_PP,	GPIO_Speed_50MHz);		//����
	
	//RD
	GPIO_Configuration_OPP50(SSD1963_RD_PORT,					SSD1963_RD_PIN);						//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//REST
	GPIO_Configuration_OPP50(SSD1963_REST_PORT,				SSD1963_REST_PIN);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//RS
	GPIO_Configuration_OPP50(SSD1963_DC_PORT,					SSD1963_DC_PIN);						//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//WR
	GPIO_Configuration_OPP50(SSD1963_WR_PORT,					SSD1963_WR_PIN);						//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//RS
	GPIO_Configuration_OPP50(SSD1963_CS_PORT,					SSD1963_CS_PIN);						//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//WR
	GPIO_Configuration_OPP50(SSD1963_DATABUS_PORT,		SSD1963_DATABUS_PIN);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	//����
	GPIO_Configuration_OPP50(SSD1963_BACKLIGHT_PORT,	SSD1963_BACKLIGHT_PIN);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	Lcd_Init0();						//LCD��ʼ��
}
/*******************************************************************************
*������		:	SSD1963_Configuration
*��������	:	�ܽų�ʼ��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_REST(void)
{
	u16 time=500;
	u16	temp=time;
	
	SSD1963_REST;				//
	while(temp--);	
	SSD1963_SET;
	temp=time;
	while(temp--);
}
//��������-16λ����ģʽ 
/*******************************************************************************
*������		:	LCD_Writ_Bus
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
#ifdef  Bus_16
void LCD_Writ_Bus(unsigned short BUS_DATA)   //��������д�뺯��
{
//	LCD_DataPortH=VH;	
//	LCD_DataPortL=VL;
	SSD1963_WR_Write; 		//0--д������1--д�ر�
	GPIO_Write(SSD1963_DATABUS_PORT,BUS_DATA);
	SSD1963_WR_Read; 		//0--д������1--д�ر�
}
#else			//��������-8λ����ģʽ
/*******************************************************************************
*������		:	LCD_Writ_Bus
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_Writ_Bus(unsigned short BUS_DATA)   //��������д�뺯��
{	
	unsigned char VH,VL;
	VH=BUS_DATA>>8;
	VL=BUS_DATA&0XFF;
	
	LCD_DataPortH=VH;	
	LCD_WR(0);		//0--д������1--д�ر�
	LCD_WR(1);		//0--д������1--д�ر�
	LCD_DataPortH=VL;		
	LCD_WR(0);		//0--д������1--д�ر�
	LCD_WR(1);		//0--д������1--д�ر�
}
#endif
/*******************************************************************************
*������		:	LCD_WR_DATA8
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
//void LCD_WR_DATA8(char VH,char VL) //��������-8λ����
//{
//	LCD_RS(1);
//	LCD_Writ_Bus(VH,VL);
//}
/*******************************************************************************
*������		:	LCD_WR_DATA
*��������	:	д����
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
 void LCD_WR_DATA(unsigned short data)
{
	SSD1963_DC_Data;					//����/�����л�	//1-���ݣ�0-����
	LCD_Writ_Bus(data);
}
/*******************************************************************************
*������		:	LCD_WR_REG
*��������	:	д����
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_WR_COMMAND(unsigned short Command)	 
{	
	SSD1963_DC_Command;				//����/�����л�	//1-���ݣ�0-����
	LCD_Writ_Bus(Command);
}
/*******************************************************************************
*������		:	LCD_WR_REG_DATA
*��������	:	д���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
 void LCD_WR_REG_DATA(int reg,int da)
{
	LCD_WR_COMMAND(reg);
	LCD_WR_DATA(da);
}
/*******************************************************************************
*������		:	Address_set
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	LCD_WR_COMMAND(0x002A);			//�����е�ַ
	LCD_WR_DATA(x1>>8);	    
	LCD_WR_DATA(x1&0x00ff);
	LCD_WR_DATA(x2>>8);	    
	LCD_WR_DATA(x2&0x00ff);
	LCD_WR_COMMAND(0x002b);			//����ҳ��ַ	
	LCD_WR_DATA(y1>>8);	    
	LCD_WR_DATA(y1&0x00ff);
	LCD_WR_DATA(y2>>8);	    
	LCD_WR_DATA(y2&0x00ff);
	LCD_WR_COMMAND(0x002c);			//д�ڴ���ʼ��ַ 					 						 
}
/*******************************************************************************
*������		:	Lcd_Init
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void Lcd_Init(void)
{

////����һ����Щ��������ñ����ʱ����ʾ����
////	LCD_CS (0);
////	delayms(500);	
////	if(LCD_CS==0)
////	{
////		LCD_WR_REG_DATA(0,0);
////		LCD_ShowString(0,0,"01");
////		LCD_ShowNum(0,0,0,0);
////		LCD_Show2Num(0,0,0,0);
////		LCD_DrawPoint_big(0,0);
////		LCD_DrawRectangle(0,0,0,0);
////		Draw_Circle(0,0,0);
////	}
//	//1������������������������λ
//	SSD1963_REST;				//
//	delayms(500);	
//	SSD1963_SET;
//	delayms(500);
//	SSD1963_REST;
//	//2������������������������λ
//	LCD_CS(1);			//0--��Ƭѡʹ�ܣ�1--ȡ��Ƭѡ
//	LCD_RD(1);
//	LCD_WR(1);			//0--д������1--д�ر�
//	LCD_CS(0);  		//0--��Ƭѡʹ�ܣ�1--ȡ��Ƭѡ
//	//3������������������������λ
//	LCD_WR_COMMAND(0x00E2);						//PLL multiplier, set PLL clock to 120M
//	LCD_WR_DATA(0x0023);	    				//N=0x36 for 6.5M, 0x23 for 10M crystal
//	LCD_WR_DATA(0x0002);
//	LCD_WR_DATA(0x0004);
//	
//	LCD_WR_COMMAND(0x00E0);  					// PLL enable
//	LCD_WR_DATA(0x0001);
//	
//	LCD_WR_COMMAND(0x00E0);
//	LCD_WR_DATA(0x0003);
//	
//	LCD_WR_COMMAND(0x0001);  					// software reset
//	delayms(500);
//	LCD_WR_COMMAND(0x00E6);						//PLL setting for PCLK, depends on resolution
//	LCD_WR_DATA(0x0003);
//	LCD_WR_DATA(0x00ff);
//	LCD_WR_DATA(0x00ff);

//	LCD_WR_COMMAND(0x00B0);						//LCD SPECIFICATION
//	LCD_WR_DATA(0x0000);
//	LCD_WR_DATA(0x0000);
//	LCD_WR_DATA((LCD_HDP>>8)&0X00FF);  		//Set HDP
//	LCD_WR_DATA(LCD_HDP&0X00FF);
//	LCD_WR_DATA((LCD_VDP>>8)&0X00FF);  		//Set VDP
//	LCD_WR_DATA(LCD_VDP&0X00FF);
//	LCD_WR_DATA(0x0000);

//	LCD_WR_COMMAND(0x00B4);	//HSYNC
//	LCD_WR_DATA((LCD_HT>>8)&0X00FF);  //Set HT
//	LCD_WR_DATA(LCD_HT&0X00FF);
//	LCD_WR_DATA((LCD_HPS>>8)&0X00FF);  //Set HPS
//	LCD_WR_DATA(LCD_HPS&0X00FF);
//	LCD_WR_DATA(LCD_HPW);			   //Set HPW
//	LCD_WR_DATA((LCD_LPS>>8)&0X00FF);  //Set HPS
//	LCD_WR_DATA(LCD_LPS&0X00FF);
//	LCD_WR_DATA(0x0000);

//	LCD_WR_COMMAND(0x00B6);							//VSYNC
//	LCD_WR_DATA((LCD_VT>>8)&0X00FF);   //Set VT
//	LCD_WR_DATA(LCD_VT&0X00FF);
//	LCD_WR_DATA((LCD_VPS>>8)&0X00FF);  //Set VPS
//	LCD_WR_DATA(LCD_VPS&0X00FF);
//	LCD_WR_DATA(LCD_VPW);			   //Set VPW
//	LCD_WR_DATA((LCD_FPS>>8)&0X00FF);  //Set FPS
//	LCD_WR_DATA(LCD_FPS&0X00FF);

//	LCD_WR_COMMAND(0x00BA);
//	LCD_WR_DATA(0x0005);    //GPIO[3:0] out 1

//	LCD_WR_COMMAND(0x00B8);
//	LCD_WR_DATA(0x0007);    //GPIO3=input, GPIO[2:0]=output
//	LCD_WR_DATA(0x0001);    //GPIO0 normal

//	LCD_WR_COMMAND(0x0036); //rotation
//	LCD_WR_DATA(0x0000);

//	LCD_WR_COMMAND(0x00F0); //pixel data interface
//	LCD_WR_DATA(0x0003);


//	delayms(500);

//	LCD_WR_COMMAND(0x0029); //display on



//	LCD_WR_COMMAND(0x00d0); 
//	LCD_WR_DATA(0x000d);
//	
////	LCD_Clear(BACK_COLOR);	//�Ա���ɫ����
}
/*******************************************************************************
*������		:	Lcd_Init
*��������	:	STM32�ڲ��¶ȴ���������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void Lcd_Init0(void)
{

	u16 time=500;
	u16	temp=time;
//����һ����Щ��������ñ����ʱ����ʾ����
	//1������������������������λ
//	SSD1963_BACKLIGHT_OFF;	//�ر���
//	LCD_REST();
	SSD1963_REST;
//	delayms(10);
	SSD1963_SET;
	while(temp--);
	//2������������������������λ
	SSD1963_CS_Disable;			//��ȡ��Ƭѡ
	SSD1963_RD_H;
	SSD1963_WR_Write;				//���߹���Ϊд����
	SSD1963_CS_Enable;  		//ʹ��	
	//3��������������������������ϵͳʱ��  ����Ƶ�� 10MHz  250MHz < VCO < 800MHz
	LCD_WR_COMMAND(0x00E2);						//PLL multiplier, set PLL clock to 120M Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input
	LCD_WR_DATA(0x0023);	    				//���ñ�Ƶ N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_DATA(0x0001);							//���÷�Ƶ
	LCD_WR_DATA(0x0004);							//�������
	//4����������������������ʹ��PLL
	LCD_WR_COMMAND(0x00E0);  					//PLL enable
	LCD_WR_DATA(0x0001);
	
	LCD_WR_COMMAND(0x00E0);
	LCD_WR_DATA(0x0003);
	//5����������������������������λ
	LCD_WR_COMMAND(0x0001);  					//software reset
//	delayms(5000);
	//6��������������������������ɨ��Ƶ��
	LCD_WR_COMMAND(0x00E6);						//PLL setting for PCLK, depends on resolution
	LCD_WR_DATA(0x0003);
	LCD_WR_DATA(0x00FF);
	LCD_WR_DATA(0x00FF);
	//7��������������������������LCD���ģʽ Set the LCD panel mode (RGB TFT or TTL)
	LCD_WR_COMMAND(0x00B0);						//LCD SPECIFICATION
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((LCD_HDP>>8)&0X00FF);  		//����ˮƽ���ص������8λ		Set HDP 
	LCD_WR_DATA(LCD_HDP&0X00FF);					//����ˮƽ���ص������8λ
	LCD_WR_DATA((LCD_VDP>>8)&0X00FF);  		//���ô�ֱ���ص������8λ		Set VDP
	LCD_WR_DATA(LCD_VDP&0X00FF);					//���ô�ֱ���ص������8λ
	LCD_WR_DATA(0x0000);									//������ż��RGB˳��Ĭ��0��Even line RGB sequence&Odd line RGB sequence
	//8��������������������������ˮƽ�� Set Horizontal Period
	LCD_WR_COMMAND(0x00B4);							//HSYNC
	LCD_WR_DATA((LCD_HT>>8)&0X00FF);  	//High byte of horizontal total period
	LCD_WR_DATA(LCD_HT&0X00FF);					//Low byte of the horizontal total period (display + non-display) in pixel clock (POR = 10101111)
																			//Horizontal total period = (HT + 1) pixels
	LCD_WR_DATA((LCD_HPS>>8)&0X00FF);  	//High byte of the non-display period between the start of the horizontal sync (LLINE) signal and the first
																			//display data. (POR = 000)
	LCD_WR_DATA(LCD_HPS&0X00FF);
	LCD_WR_DATA(LCD_HPW);			   //Set HPW
	LCD_WR_DATA((LCD_LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(LCD_LPS&0X00FF);
	LCD_WR_DATA(0x0000);
	//9�������������������������ô�ֱ��	Set Vertical Period
	LCD_WR_COMMAND(0x00B6);							//VSYNC
	LCD_WR_DATA((LCD_VT>>8)&0X00FF);   //Set VT
	LCD_WR_DATA(LCD_VT&0X00FF);
	LCD_WR_DATA((LCD_VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_DATA(LCD_VPS&0X00FF);
	LCD_WR_DATA(LCD_VPW);			   //Set VPW
	LCD_WR_DATA((LCD_FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_DATA(LCD_FPS&0X00FF);	
	//10��������������������������GPIO
	LCD_WR_COMMAND(0x00B8);
	LCD_WR_DATA(0x0007);    //GPIO3=input, GPIO[2:0]=output //���ģʽ
	LCD_WR_DATA(0x0001);   	//0 GPIO0 is used to control the panel power with Enter Sleep Mode 0x10 or Exit Sleep Mode 0x11.
													//1 GPIO0 is used as normal GPIO
	//11��������������������������GPIO������ɨ�跽�� Set GPIO value for GPIO configured as output
	LCD_WR_COMMAND(0x00BA);
	LCD_WR_DATA((LCD_LR&0XFF)|(LCD_UD&0XFF));    //GPIO[3:0] out 1
	//12�������������������������õ�ַģʽ	Set Address Mode
	LCD_WR_COMMAND(0x0036); //rotation
	LCD_WR_DATA(0x0000);
	//13�����������������������������ݽӿ� Set Pixel Data Interface/Pixel Data Interface Format
	LCD_WR_COMMAND(0x00F0); //pixel data interface
	LCD_WR_DATA(0x0003);
	
//	delayms(5000);
	//14�������������������������ô�ֱ��
	LCD_WR_COMMAND(0x0029); //display on
	//15�������������������������ô�ֱ��
	LCD_WR_COMMAND(0x00d0); 
	LCD_WR_DATA(0x000D);

	LCD_Clear(BACK_COLOR);	//�Ա���ɫ����
	
	SSD1963_BACKLIGHT_ON;		//������
}
/*******************************************************************************
*������		:	LCD_Clear
*��������	:	��������
*����			: Color:Ҫ���������ɫ
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_Clear(u16 Color)
{
//	u8 VH,VL;
	u16 i,j;
//	VH=Color>>8;
//	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
	for(i=0;i<LCD_W;i++)
	{
		for (j=0;j<LCD_H;j++)
		{
			LCD_WR_DATA(Color);
		}
	}
}
/*******************************************************************************
*������		:	showhanzi
*��������	:	��ָ��λ����ʾһ������(32*33��С)
*����			: dcolor:������ɫ
						gbcolor:������ɫ
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void showhanzi(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j;
	unsigned char *temp=&hanzidata;    
	Address_set(x,y,x+31,y+31); //��������      
	temp+=index*128;	
	for(j=0;j<128;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
			if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(POINT_COLOR);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
	}
}
/*******************************************************************************
*������		:	LCD_DrawPoint
*��������	:	����
*����			: POINT_COLOR:�˵����ɫ
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y)
{
	Address_set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(POINT_COLOR); 	    
}
/*******************************************************************************
*������		:	LCD_DrawPoint_big
*��������	:	��һ�����
*����			: POINT_COLOR:�˵����ɫ
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_DrawPoint_big(u16 x,u16 y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
}
/*******************************************************************************
*������		:	LCD_Fill
*��������	:	��ָ�����������ָ����ɫ
*����			: �����С:(xend-xsta)*(yend-ysta)
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//���ù��λ�� 	    
	} 					  	    
}
/*******************************************************************************
*������		:	LCD_DrawLine
*��������	:	����
*����			: x1,y1:�������
						x2,y2:�յ�����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//ˮƽ�� 
	else
		{incy=-1;delta_y=-delta_y;} 
		
	if( delta_x>delta_y)
		distance=delta_x; //ѡȡ�������������� 
	else
		distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
/*******************************************************************************
*������		:	LCD_DrawRectangle
*��������	:	������
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
/*******************************************************************************
*������		:	Draw_Circle
*��������	:	��ָ��λ�û�һ��ָ����С��Բ
*����			: (x,y):���ĵ�
						r    :�뾶
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
}

//#ifdef ShowCharAscii		//��ͨ�ֿ���Գ���
/*******************************************************************************
*������		:	LCD_ShowChar
*��������	:	��ָ��λ����ʾһ���ַ�
*����			: x,y		:�������
						font	:�����С
						num		:Ҫ��ʾ���ַ�:" "--->"~"
						Buffer	:����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowCharGT(u16 x,u16 y,u8 font,u8 num,u8 *Buffer)		//��ͨ�ֿ���Գ���
{
	u8 temp;
	u8 mode=0;
	u8 i,j;
//	u8 num=0;
//	u16 x0=x;
	u16 colortemp=POINT_COLOR;
	if(font==12)
	{
		if(x>LCD_W-12||y>LCD_H-12)
			return;
		Address_set(x,y,x+12-1,y+12-1);      //���ù��λ�� 
	}
	if(font==16)
	{
		if(x>LCD_W-16||y>LCD_H-16)
			return;
		Address_set(x,y,x+16-1,y+16-1);      //���ù��λ�� 
	}
	if(font==24)
	{
		if(x>LCD_W-24||y>LCD_H-24)
			return;
		Address_set(x,y,x+24-1,y+24-1);      //���ù��λ�� 
	}
	else if(font==32)
	{
		if(x>LCD_W-32||y>LCD_H-32)
			return;
		Address_set(x,y,x+16-1,y+32-1);      //���ù��λ�� 
	}
	else
	{
		return ;
	}
	SSD1963_DC_Data;					//����/�����л�	//1-���ݣ�0-����
//	SSD1963_WR_Write; 		//0--д������1--д�ر�
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//����1608����--��ά������ʽ--�ֿ�ʹ��ʱȡ��  
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				POINT_COLOR=BRED;
			}
			else
				POINT_COLOR=BACK_COLOR;
			
			SSD1963_WR_Write; 		//0--д������1--д�ر�
			GPIO_Write(SSD1963_DATABUS_PORT,POINT_COLOR);
			SSD1963_WR_Read; 			//0--д������1--д�ر�
//			LCD_WR_DATA(POINT_COLOR);
//			{
//				LCD_RS(1);
////				LCD_Writ_Bus(POINT_COLOR);
//				{
//					LCD_WR(0); 		//0--д������1--д�ر�
//					GPIO_Write(LCD_DATABUS_PORT,POINT_COLOR);
//					LCD_WR(1); 		//0--д������1--д�ر�
//				}
//			}
			temp=temp<<1;
		}
	}	
//	SSD1963_WR_Read; 		//0--д������1--д�ر�
	POINT_COLOR=colortemp;	
	
}
//#else
/*******************************************************************************
*������		:	LCD_ShowChar
*��������	:	��ָ��λ����ʾһ���ַ�
*����			: x,y		:�������
						num		:Ҫ��ʾ���ַ�:" "--->"~"
						mode	:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
						num		:Ҫ��ʾ���ַ�:" "--->"~"
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode)
{
	u8 temp;
	u8 pos,t;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
	if(x>LCD_W-16||y>LCD_H-16)return;	    
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
//	num=41;//�õ�ƫ�ƺ��ֵ
	Address_set(x,y,x+8-1,y+16-1);      //���ù��λ�� 
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=code_asc2_1608[(u16)num*16+pos];		 //����1608����
//			temp=code_num_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
			{                 
				if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1; 
				x++;
			}
			x=x0;
			y++;
		}	
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{
			temp=code_asc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
			{                 
				if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����     
				temp>>=1; 
			}
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}
//#endif
/*******************************************************************************
*������		:	mypow
*��������	:	m^n����
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}
/*******************************************************************************
*������		:	LCD_ShowNum
*��������	:	��ʾ����
*����			: x,y		:�������
						len 	:���ֵ�λ��
						color	:��ɫ
						num		:��ֵ(0~4294967295);
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u32)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0); 
	}
}
/*******************************************************************************
*������		:	LCD_ShowEn
*��������	:	��ʾ����
*����			: x,y		:�������
						len 	:���ֵ�λ��
						color	:��ɫ
						num		:��ֵ(0~4294967295);
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowEn(u16 x,u16 y,u32 num)
{         	
	u8 t=0,len=0;
	u32 num2=num;
	u8 enshow=0;
	while(num2)
	{
		num2=num2/10;
		len++;		
	}
	for(t=len;t>0;t--)
	{
		num2=mypow(10,t-1);
		if(num>9)
		{
			enshow=num/num2;
			num=num%num2;
		}
		else
			enshow=(char)num;
	 	LCD_ShowChar(x+8*(len-t),y,enshow+48,0); 
	}
}
/*******************************************************************************
*������		:	LCD_Show2Num
*��������	:	��ʾ2������
*����			: x,y:�������
						num:��ֵ(0~99);
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0); 
	}
}
/*******************************************************************************
*������		:	LCD_ShowString
*��������	:	��ʾ�ַ���
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
unsigned int LCD_PrintfString(u16 x,u16 y,const char *format,...)				//��ߵ�ʡ�Ժž��ǿɱ����
{ 

	
//		va_list ap; 										//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>,���ڻ�ȡ��ȷ�������Ĳ���
//    static char string[ 256 ];			//�������飬
//    va_start( ap, format );
//    vsprintf( string , format, ap );    
//    va_end( ap );
	
	char	*Char_Buffer;

	//1)**********��ȡ���ݿ���
	u16 num=strlen((const char*)format);		//��ȡ���ݿ���
	//2)**********���建������С����
	unsigned int BufferSize;
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args;                                        
	//4)**********���붯̬�ռ�
	Char_Buffer = (char*)malloc(sizeof(char) * num);
//	if(Char_Buffer==NULL)
//	{
//		Char_Buffer=NULL;
//		return;
//	}
	//5)**********��ʼ��args�ĺ�����ʹ��ָ��ɱ�����ĵ�һ��������format�ǿɱ������ǰһ������
	va_start(args, format);
	//6)**********��������·��������ִ��ĳ���(��ȥ\0),����������ظ�ֵ
	BufferSize = vsprintf(Char_Buffer, format, args);
	num=BufferSize;
	//7)**********�����ɱ�����Ļ�ȡ
	va_end(args);                                      		
	//8)**********���ȷ��ͻ�������С�����ݸ���������������ַ����DMA��������
//	while(*Char_Buffer!='\0')
	while(num>0)
	{       
		if(x>LCD_W-16)
		{
			x=0;
			y+=16;
		}
		if(y>LCD_H-16)
		{
			y=x=0;
			LCD_Clear(RED);
		}
		LCD_ShowChar(x,y,*Char_Buffer,0);
		x+=8;
		Char_Buffer++;
		num--;
	}
	//9)**********DMA������ɺ�ע��Ӧ���ͷŻ�������free(USART_BUFFER);
//	Char_Buffer=NULL;
	Char_Buffer-=BufferSize;
	free(Char_Buffer);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer); 
	return BufferSize;
//	Char_Buffer=NULL;
//	free(format);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer);	
}

/*******************************************************************************
*������		:	LCD_ShowString
*��������	:	��ʾ�ַ���
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowString(u16 x,		
										u16 y,
										const u8 *p
											)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;LCD_Clear(RED);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}

/*******************************************************************************
*������		:	RGB888ToRGB565
*��������	:	RGB888תRGB565��ɫ(�ֱ�ȡ��λ)
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void RGB888ToRGB565(unsigned char Color_R,		//RED	
										unsigned char Color_G,		//GREEN
										unsigned char Color_B,		//BLUE
										u16 *RGB565
											)
{  
	u16 temp=0;
	temp|=(u16)(Color_R&0XF8)<<8;
	temp|=(u16)(Color_G&0XFC)<<3;
	temp|=(u16)(Color_B>>3);
	*RGB565=temp;
//	*RGB565=(Color_R
}
















//#endif

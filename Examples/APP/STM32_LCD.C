#ifdef STM32_LCD

#include "STM32_LCD.H"

//#define SDCardTest
//#define GT32L32M0180Test	
//


GT32L32_Info_TypeDef	GT32L32_Info;			//�ַ���Ϣ

u16 millisecond=0;
u8 hour=20,min=43,second=00;

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->������		:	
//->��������	:	 
//->����		:	
//->���		:
//->���� 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void STM32_LCD_Configuration(void)
{	
	SYS_Configuration();				//ϵͳ����
	SSD1963_Configuration();			//LCD�ӿ�����
	GT32L32_Configuration();
	LCD_PrintfString(0,16,"SD_TYPE IS SD_TYPE_V2HC");		//��ߵ�ʡ�Ժž��ǿɱ����
//	LCD_PrintfStringGT(0,32,32,"��ߵ�ʡ�Ժž��ǿɱ����~!@#$%^&*()_+{}:<>?|");		//��ߵ�ʡ�Ժž��ǿɱ����
	LCD_PrintfStringGT(0,64,32,"1234567890SD_TYPE IS SD_TYPE_V2HC");		//��ߵ�ʡ�Ժž��ǿɱ����
	Draw_Circle(400,240,100);
	LCD_PrintfStringGT(300,230,32,"%02d-%02d-%02d-%03d",hour,min,second,millisecond);		//��ߵ�ʡ�Ժž��ǿɱ����
//	LCD_PrintfStringGT(0,256,32,"���м�ʱ��");		//��ߵ�ʡ�Ժž��ǿɱ����
//	LCD_PrintfStringGT(300,256,32,"%02d:%02d:%02d:%02d",hour,min,second,millisecond);		//��ߵ�ʡ�Ժž��ǿɱ����
	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->������		:	
//->��������	:	 
//->����		:	
//->���		:
//->���� 		:
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
				LCD_PrintfStringGT(300,230,32,"%02d",hour);		//��ߵ�ʡ�Ժž��ǿɱ����
			}
			LCD_PrintfStringGT(348,230,32,"%02d",min);		//��ߵ�ʡ�Ժž��ǿɱ����
		}
		LCD_PrintfStringGT(396,230,32,"%02d",second);		//��ߵ�ʡ�Ժž��ǿɱ����
	}
//	LCD_PrintfStringGT(444,230,32,"%03d",millisecond);		//��ߵ�ʡ�Ժž��ǿɱ����
}

/*******************************************************************************
*������		:	LCD_ShowString
*��������	:	��ʾ�ַ�����ͨ�ֿ�
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
unsigned int LCD_PrintfStringGT(u16 x,u16 y,u8 font,const char *format,...)				//��ߵ�ʡ�Ժž��ǿɱ����
{ 	
//		va_list ap; 										//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>,���ڻ�ȡ��ȷ�������Ĳ���
//		static char string[ 256 ];			//�������飬
//    	va_start( ap, format );
//    	vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	*Char_Buffer;

	//1)**********��ȡ���ݿ���
	u16 num=strlen((const char*)format);		//��ȡ���ݿ���
	//2)**********���建������С����
	unsigned int BufferSize;
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args;                                        
	//4)**********���붯̬�ռ�
	Char_Buffer = (char*)malloc(sizeof(char) * num);
	if(Char_Buffer==NULL)
	{
		Char_Buffer=NULL;
		return 0;
	}
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
		unsigned char	*char_GT32L32;
		unsigned char dst=*Char_Buffer;
		
		if(dst>0x80)		//˫�ֽ�--����
		{
			u16 word=dst<<8;
			Char_Buffer++;
			dst=*Char_Buffer;
			word=word|dst;
			//��ʾ�����ж�
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
			//�����С�ж�
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
			
			GT32L32_ReadBuffer(GT32L32_Info.GT32L32_Address,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);	//���ֿ��ж����ݺ���
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
			free(char_GT32L32);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer); 
		}
		else		//���ֽ�
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
			
			GT32L32_ReadBuffer(GT32L32_Info.GT32L32_Address,GT32L32_Info.GT32L32_BufferSize,char_GT32L32);	//���ֿ��ж����ݺ���
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
			free(char_GT32L32);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer);
		}
		
//		LCD_ShowCharGT(x,y,1,STM32_DSP_Buffer);
//		GT32L32_Get_Info(0xB0A1,&GT32L32_Info);
//		GT32L32_ReadBuffer(u32 address,u16 len,unsigned char *Buffer);	//���ֿ��ж����ݺ���
//		LCD_ShowCharGT(x,y,1,STM32_DSP_Buffer);
//		LCD_ShowCharGT(664,300,1,STM32_DSP_Buffer);
//		GT32L32_GetGB18030_16(0xb0,0xa1,0,0,Char_Buffer);
//		LCD_ShowCharGT(x,y,*Char_Buffer,0);		
	}
	//9)**********DMA������ɺ�ע��Ӧ���ͷŻ�������free(USART_BUFFER);
	Char_Buffer-=BufferSize;
	free(Char_Buffer);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer); 
	return BufferSize;
}

#endif
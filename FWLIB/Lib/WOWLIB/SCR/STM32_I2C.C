/******************************** User_library *********************************
* �ļ��� 	: STM32_SDCard.H
* ����   	: wegam@sina.com
* �汾   	: V
* ����   	: 2016/01/01
* ˵��   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_I2C.H"
//#include "STM32F10x_BitBand.H"

//////////////////////////////////////////////////////////////////////////////////	

////////////////////////////////////////////////////////////////////////////////// 	
//#define IIC_SCL	GPIO_Pin_10
//#define IIC_SDA	GPIO_Pin_11
//#define GPIO_SCL	GPIOB
//#define GPIO_SDA	GPIOB
//GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
//GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
//GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
//GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitActionBitVal);
//#define	(IIC_SCL=1) 0
//u16 IIC_SCL=0;
//GPIO_TypeDef* GPIO_SCL=0;

//GPIO_TypeDef* GPIO_SDA=0;
//u16 IIC_SDA=0;

/*******************************************************************************
*������		:IIC_Delay
*��������	:595��ʱ����
*����			:j-��ʱʱ��					
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_Delay(u16 j)
{
	j*=5;
	for(;j>0;j--);
}

/*******************************************************************************
*������		:IIC_INII
*��������	:IIC�ܽų�ʼ��
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
//void IIC_INII(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
//{
//	GPIO_SCL=GPIOx_SCL;
//	IIC_SCL=IIC_SCLPin;
//	
//	GPIO_SDA=GPIOx_SDA;
//	IIC_SDA=IIC_SDAPin;
//}
/*******************************************************************************
*������		:IIC_Configuration
*��������	:IIC�ܽų�ʼ��
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_Configuration(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{					
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ��
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	//SCL�ܽ�����
	GPIO_InitStructure.GPIO_Pin = IIC_SCLPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx_SCL, &GPIO_InitStructure);
	//SDA�ܽ�����
	GPIO_InitStructure.GPIO_Pin = IIC_SDAPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);

}
/*******************************************************************************
*������		:IIC_IN
*��������	:IIC�����ݹܽ�����
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_IN(GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{					
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ��
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDAPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);

//	IIC_SCL=1;
//	IIC_SDA=1;
}
/*******************************************************************************
*������		:IIC_OUT
*��������	:IICд���ݹܽ�����
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_OUT(GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{					
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ��
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDAPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);

}
/*******************************************************************************
*������		:IIC_Start
*��������	:IIC����,��SCL���Ǹߵ�ƽʱSDA�ߴӸߵ�ƽ��͵�ƽ�л���������ʾ��ʼ����
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_Start(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{
	//����������Ϊ���ģʽ
	IIC_OUT(GPIOx_SDA,IIC_SDAPin);     //sda�����
	GPIO_SetBits(GPIOx_SDA,IIC_SDAPin);
//	IIC_SDA=1;
	GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=1;
	IIC_Delay(5);
	GPIO_ResetBits(GPIOx_SDA,IIC_SDAPin);
// 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	IIC_Delay(5);
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;//ǯסIIC���ߣ�׼�����ͻ��������
}
/*******************************************************************************
*������		:IIC_Stop
*��������	:IICֹͣ,��SCL�Ǹߵ�ƽʱSDA���ɵ͵�ƽ��ߵ�ƽ�л���ʾֹͣ����
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_Stop(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{
	IIC_OUT(GPIOx_SDA,IIC_SDAPin);//sda�����
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
	GPIO_ResetBits(GPIOx_SDA,IIC_SDAPin);
//	IIC_SCL=0;
//	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	IIC_Delay(5);
	GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
	GPIO_SetBits(GPIOx_SDA,IIC_SDAPin);
//	IIC_SCL=1; 
//	IIC_SDA=1;//����IIC���߽����ź�
	IIC_Delay(5);
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
	GPIO_ResetBits(GPIOx_SDA,IIC_SDAPin);	
}
/*******************************************************************************
*������		:IIC_Wait_Ack
*��������	:���IICӦ��
*����			:��
*���			:��
*����ֵ		:1������Ӧ��ʧ��
					 0������Ӧ��ɹ�
*����			��
*******************************************************************************/
u8 IIC_Wait_Ack(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{
	u8 ucErrTime=0;
	IIC_IN(GPIOx_SDA,IIC_SDAPin);//SDA����Ϊ����
	IIC_Delay(5);
	GPIO_SetBits(GPIOx_SDA,IIC_SDAPin);  
//	IIC_SDA=1;
	IIC_Delay(5);
	GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);	
//	IIC_SCL=1;
	IIC_Delay(5);	
	while(GPIO_ReadInputDataBit(GPIOx_SDA,IIC_SDAPin))
	{
		ucErrTime++;
		IIC_Delay(5);
		if(ucErrTime>250)
		{
			IIC_Stop(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin);
			return 0;
		}
	}
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;//ʱ�����0 	
	return 1;  
}
/*******************************************************************************
*������		:IIC_Ack
*��������	:����Ӧ���ź�
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void IIC_Ack(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;
	IIC_Delay(5);
	
	IIC_OUT(GPIOx_SDA,IIC_SDAPin);
	GPIO_ResetBits(GPIOx_SDA,IIC_SDAPin);
//	IIC_SDA=0;
	IIC_Delay(5);
	GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=1;
	IIC_Delay(5);
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;
}
/*******************************************************************************
*������		:IIC_NAck
*��������	:��Ӧ��
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
//������ACKӦ��		
void IIC_NAck(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin)
{
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;
	IIC_OUT(GPIOx_SDA,IIC_SDAPin);
	GPIO_SetBits(GPIOx_SDA,IIC_SDAPin); 
//	IIC_SDA=1;
	IIC_Delay(5);
	GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=1;
	IIC_Delay(5);
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;
}
/*******************************************************************************
*������		:IIC_Send_Byte
*��������	:IIC����һ���ֽ�
*����			:��
*���			:��
*����ֵ		:��
*����			:
*******************************************************************************/
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			
void IIC_Send_Byte(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin,u8 txd)
{                        
	u8 t;   
	IIC_OUT(GPIOx_SDA,IIC_SDAPin); 
	GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	IIC_Delay(5);
	for(t=0;t<8;t++)
	{     
		if((txd&0x80) == 0x00)
			GPIO_ResetBits(GPIOx_SDA,IIC_SDAPin);
		else
			GPIO_SetBits(GPIOx_SDA,IIC_SDAPin);
//        IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	
		IIC_Delay(5);   //��TEA5767��������ʱ���Ǳ����
		GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
//		IIC_SCL=1;
		IIC_Delay(5);
		GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//		IIC_SCL=0;	
		IIC_Delay(5);
	}	
}
/*******************************************************************************
* ������		:IIC_Send_Data	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
u8 IIC_Send_Data(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin,unsigned char *Buffer_Addr)
{
	u8 ack_flag=0;
	IIC_Start(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin);
	IIC_Send_Byte(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin,0x82);//IIC��ȡһ���ֽ�
	ack_flag=IIC_Wait_Ack(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin); 				//IIC�ȴ�ACK�ź�
	if(ack_flag==0)
		return 1;
	else
		return 0;

}

/*******************************************************************************
*������		:
*��������	:
*����			:��
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 IIC_Read_Byte(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin,unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_IN(GPIOx_SDA,IIC_SDAPin);//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
		GPIO_ResetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=0; 
		IIC_Delay(5);
		GPIO_SetBits(GPIOx_SCL,IIC_SCLPin);
//	IIC_SCL=1;
		IIC_Delay(5);
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIOx_SDA,IIC_SDAPin))
			receive++;   
		IIC_Delay(5); 
	}					
	if (!ack)
		IIC_NAck(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin);//����nACK
	else
		IIC_Ack(GPIOx_SCL,IIC_SCLPin,GPIOx_SDA,IIC_SDAPin); //����ACK   
	return receive;
}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void IIC_Read_Data(GPIO_TypeDef* GPIOx_SCL,u16 IIC_SCLPin,GPIO_TypeDef* GPIOx_SDA,u16 IIC_SDAPin,unsigned char *Buffer_Addr)
{

}









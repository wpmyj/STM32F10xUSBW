#ifndef __MS0800_PC004V10_H
#define __MS0800_PC004V10_H

//#include "STM32_USART.H"
//#include "STM32_TIM.H"
//#include "STM32_DMA.H"
//#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
//#include "STM32_ADC.H"
//#include "STM32_DAC.H"
#include "STM32_CAN.H"
#include "STM32_PWM.H"
#include "STM32_CD4511BM.H"
#include "STM32_GPIO.H"
#include "STM32_USART.H"

#include "STM32_TOOLS.H"		//����У�鹤��


void MS0800_PC004V10_Configuration(void);
void MS0800_PC004V10_Server(void);
u8 PC004V10_485_TR(void);				//485�շ�
void PC004V10_CAN_RX(void);			//��Ҫ��������ܰ��ַ��
void PC004V10_CAN_TX(void);			//CAN�������ݣ���ַ���������ͣ�����
void PC004V10_CAN_COMMAD(void);	//CAN�������������ַ���������ͣ�����--ʱ��ͬ��
void WORK_LED(u16 time);				//WORK_LED
void PC004V10_BUZZER(u16 time);	//������
u8 PC004V10_Get_ID(void);				//��ȡ��ǰ�豸ID//�����

void Self_Test(u16 time);			//���뿪��Ϊ0ʱ��������ʾ����

void PC004V10_delay(u16 time);


#endif

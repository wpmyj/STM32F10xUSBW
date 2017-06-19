#ifndef __TM1618_H
#define __TM1618_H


#include "stdio.h"
#include "stm32f10x_type.h"
//#include "STM32_SPI.H"
#include "STM32_PWM.H"
#include "STM32_ADC.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"
#include "STM32_SYSTICK.H"

//#include "STM32_SPI.H"






void TM1618_Configuration(void);
void TM1618_Server(void);
u16 Temperature_COV(void);
void TM1618_PinConf(void);

extern  void TM1618_DIS(u16);

void TM1618_delay(u16 time);

#endif


#ifndef __STM32F10x_DAC_Conf_H
#define __STM32F10x_DAC_Conf_H

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"


void DAC_Configuration(void);						//DAC����
void DAC_GPIO_Configuration(void);			//DAC�ܽ�����
void DAC_MODE_Configuration(void);			//DAC��������
void DAC_DMA_Configuration(u32 *MemoryAddr);				//DAC DMAģʽ����


#endif



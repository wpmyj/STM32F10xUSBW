#include "STM32_WOW.H"


//#include "STM32F10x_BitBand.H"
//#include "stm32f10x_map.h"
//#include "STM32_WDG.H"
//#include "STM32_SYSTICK.H"
//#include "STM32_SYS.H"



//#ifndef	Usart_Test
//#define	Usart_Test
//	#include "USART_TEST.H"
//#endif
//#define R2A15908SP
//#define Usart_Test



/*******************************************************************************
* 函数名	:	WOW_Configuration
* 功能描述	:	配置函数	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void WOW_Configuration(void)
{
//	GPIO_DeInit(GPIOA);
//	GPIO_DeInit(GPIOB);
//	GPIO_DeInit(GPIOC);
//	GPIO_DeInit(GPIOD);
//	GPIO_DeInit(GPIOE);
//	GPIO_DeInit(GPIOF);
//	GPIO_DeInit(GPIOG);
	
//	IWDG_Configuration(5000);	//独立看门狗配置 1000ms
	
//	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
//***********************************TEST***********************************//
#ifdef TEST	
	TEST_Configuration();
#endif	
//***********************************数字调音板配置程序***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Configuration();
#endif
//***********************************串口测试配置程序***********************************//
#ifdef USART_TEST	
	Usart_test_Configuration();
#endif
//***********************************7寸LCD配置程序***********************************//
#ifdef SSD1963	
	SSD1963_Configuration();
#endif
//***********************************7寸LCD配置程序***********************************//
#ifdef STM32_LCD	
	STM32_LCD_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef ADC_TEST	
	ADC_TEST_Configuration();
#endif
	
//***********************************ADC_TEST***********************************//
#ifdef ADC_Temperature	
	ADC_Temperature_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef CAN_TEST	
	CAN_TEST_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef SPI_TEST	
	SPI_TEST_Configuration();
#endif
//***********************************SPI_FLASH***********************************//
#ifdef SPI_FLASH
	SPI_FLASH_Configuration();
#endif

////***********************************ADC_TEST***********************************//
//#ifdef MS0800_WOW	
//	MS0800_WOW_Configuration();
//#endif

//***********************************ADC_TEST***********************************//
#ifdef CD4511BM_TEST	
	CD4511BM_TEST_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PL001V20	
	MS0800_PL001V20_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PC004V10	
	MS0800_PC004V10_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PM001V20	
	MS0800_PM001V20_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MX25L4006E	
	MX25L4006E_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef TM1618	
	TM1618_Configuration();
#endif

//***********************************VirtualCom***********************************//
#ifdef VirtualCom	
	VirtualCom_Configuration();
#endif

//***********************************USBtoSPI***********************************//
#ifdef USBtoSPI	
	USBtoSPI_Configuration();
#endif

//***********************************SPItoUSART***********************************//
#ifdef SPItoUSART	
	SPItoUSART_Configuration();
#endif
//***********************************PWM_TEST***********************************//
#ifdef PWM_TEST
	PWM_TEST_Configuration();
#endif
//********************************OLED096_TEST*********************************//
#ifdef OLED096_TEST
	OLED096_TEST_Configuration();
#endif

//*********************************LK3U_40MR*********************************//
#ifdef LK3U_40MR
	LK3U_40MR_Configuration();
#endif

//*********************************FX2N_14MR*********************************//
#ifdef FX2N_14MR
	FX2N_14MR_Configuration();
#endif

//*********************************A3987_TEST*********************************//
#ifdef A3987_TEST
	A3987_TEST_Configuration();
#endif

//*********************************Buzzer_TEST*********************************//
#ifdef Buzzer_TEST
	Buzzer_TEST_Configuration();
#endif

//*********************************PM001V20*********************************//
#ifdef PM001V20
	PM001V20_Configuration();
#endif



}
/*******************************************************************************
* 函数名	:	WOW_Server
* 功能描述	:	服务函数 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void WOW_Server(void)
{
//	IWDG_Feed();								//独立看门狗喂狗
	
//***********************************数字调音板服务程序***********************************//
#ifdef TEST
	TEST_Server();
#endif
//***********************************数字调音板服务程序***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Server();
#endif
//***********************************串口测试服务程序***********************************//
#ifdef USART_TEST	
	Usart_test_Server();
#endif
//***********************************7寸LCD服务程序***********************************//
#ifdef SSD1963	
//	SSD1963_Server();
#endif
//***********************************7寸LCD配置程序***********************************//
#ifdef STM32_LCD	
	STM32_LCD_Server();
#endif
//***********************************ADC_TEST***********************************//
#ifdef ADC_TEST	
	ADC_TEST_Server();
#endif
//***********************************ADC_TEST***********************************//
#ifdef ADC_Temperature	
	ADC_Temperature_Server();
#endif
//***********************************ADC_TEST***********************************//
#ifdef CAN_TEST	
	CAN_TEST_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef SPI_TEST	
	SPI_TEST_Server();
#endif
//***********************************SPI_FLASH***********************************//
#ifdef SPI_FLASH
	SPI_FLASH_Server();
#endif
//***********************************ADC_TEST***********************************//
//#ifdef MS0800_WOW	
//	MS0800_WOW_Server();
//#endif

//***********************************ADC_TEST***********************************//
#ifdef CD4511BM_TEST	
	CD4511BM_TEST_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PL001V20	
	MS0800_PL001V20_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PC004V10	
	MS0800_PC004V10_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PM001V20	
	MS0800_PM001V20_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MX25L4006E	
	MX25L4006E_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef TM1618	
	TM1618_Server();
#endif

//***********************************VirtualCom***********************************//
#ifdef VirtualCom	
	VirtualCom_Server();
#endif

//***********************************USBtoSPI***********************************//
#ifdef USBtoSPI	
	USBtoSPI_Server();
#endif

//***********************************SPItoUSART***********************************//
#ifdef SPItoUSART	
	SPItoUSART_Server();
#endif
//***********************************PWM_TEST***********************************//
#ifdef PWM_TEST	
	PWM_TEST_Server();
#endif
//********************************OLED096_TEST*********************************//
#ifdef OLED096_TEST
	OLED096_TEST_Server();
#endif
//*********************************LK3U_40MR*********************************//
#ifdef LK3U_40MR
	LK3U_40MR_Server();
#endif
//*********************************FX2N_14MR*********************************//
#ifdef FX2N_14MR
	FX2N_14MR_Server();
#endif

//*********************************A3987_TEST*********************************//
#ifdef A3987_TEST
	A3987_TEST_Server();
#endif

//*********************************Buzzer_TEST*********************************//
#ifdef Buzzer_TEST
	Buzzer_TEST_Server();
#endif

//*********************************PM001V20*********************************//
#ifdef PM001V20
	PM001V20_Server();
#endif
//IWDG_Feed();								//独立看门狗喂狗

}





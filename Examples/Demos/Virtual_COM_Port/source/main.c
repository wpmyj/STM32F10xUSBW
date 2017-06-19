/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Virtual Com Port Demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"
//#include "usb_lib.h"
//#include "usb_desc.h"
//#include "hw_config.h"
//#include "usb_pwr.h"

#include "STM32_WOW.H"

//#define test_warning

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
//extern u32 count_out;
//extern u8 buffer_out[VIRTUAL_COM_PORT_DATA_SIZE];
//extern u16 txTemp;




//u8	DMAF=0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

//u8 ta=0;	
//	u32 time=0;
#ifdef DEBUG
  debug();
#endif

//#ifdef USBtoSPI
////  Set_System();
//////	SYS_Configuration();
//////	WOW_Configuration();					//���ú���
//////	SysTick_Configuration(10000);	//ϵͳ���ʱ������72MHz,��λΪuS

////	USB_EN();
////  Set_USBClock();
////	
////  USB_Interrupts_Config();
////	
////  USB_Init();
//#else	
//	SYS_Configuration();
//#endif	
	WOW_Configuration();					//���ú���
//	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS

#ifdef test_warning
#warning: "����
#error: "����
#endif


//#endif

  while (1)
  {
#ifdef USBtoSPI

#endif	

  }
}



#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

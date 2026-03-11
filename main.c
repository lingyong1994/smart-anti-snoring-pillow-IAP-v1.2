/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "EXIT.h"
#include "UART.h"
#include "FLASH.h"
#include "H711_api.h"
#include "bord_conf.h"
#include "main.h"
#include "mcu_api.h"

/** @addtogroup STM32F0xx_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t JumpAddress;
pFunction Jump_To_Application;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Buffer used for transmission */
uint8_t aTxBuffer[BUFFER_SIZE] = "USART Example: 8xUsarts Tx/Rx Communication";
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	PARA_FLASH_Read((uint32_t *)&IAP_str,sizeof(IAP_str));
	if((IAP_str.APP_addr != APP_1_START_ADDR)&&(IAP_str.APP_addr != APP_2_START_ADDR))
	{
		IAP_str.APP_addr = APP_1_START_ADDR;
		//memcpy((uint8_t *)debug_buff,(uint8_t *)&IAP_str,sizeof(IAP_str));
		PARA_FLASH_Write((uint32_t *)&IAP_str,sizeof(IAP_str));
	}
	/* Keep the user application running */

    /* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
    if (((*(__IO uint32_t*)IAP_str.APP_addr) & 0x2FFE0000 ) == 0x20000000)
    { 
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (IAP_str.APP_addr + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) IAP_str.APP_addr);
      
      /* Jump to application */
      Jump_To_Application();
    }
	
	
	
	if (SysTick_Config(SystemCoreClock / 1000))//1ms
  { 
    /* Capture error */ 
    while (1);
  }
	
	
	
	/* Configure GPIO Pin Tx/Rx for Usart communication */
  GPIO_Configuration();
	
	EXTI4_15_Configuration();
  
	UART_Configuration();
	
	W25QXX_Init();
	
	GPIO_Weigh_Init();
	
	wifi_protocol_init();
	
	//mcu_set_wifi_mode(0);
  /* Add your application code here
     */

  /* Infinite loop */
  while (1)
  {
		/*for(i=0;i<sizeof(aTxBuffer);i++)
		{
			USART_SendData(USART1, aTxBuffer[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)== RESET);
		}*/
	//	delay_ms(3000);
		if(Count_Read_Time_word_100ms(SysTime_Struct.Unit_Get_H711_Time,UNIT_100ms_TIME_500ms))
		{
			SysTime_Struct.Unit_Get_H711_Time = SysTime_Struct.Unit_100ms_CurTime;
			h711_value = Read_Weigh();			
		}
		//mcu_get_wifi_connect_status();
		if(set_wifi_flag==1)
		{
			set_wifi_flag = 0;
			mcu_set_wifi_mode(0);
		}
		wifi_uart_service();
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
		
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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
#include "main.h"
#include <string.h>
#include "w25qxx.h"
#include "bord_conf.h"
/** @addtogroup STM32F0xx_IAP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
uint32_t JumpAddress;
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/



uint32_t appsize[256];
static void IAP_Process(void)
{
	uint32_t write_addr = 0;
	uint32_t * in_buff_temp;
	uint8_t Page_Num=0;
	uint16_t i=0;
	uint16_t j=0;	

	//1、计算升级文件需要扇区大小
	Page_Num = IAP_str.plug_bin_len/1024 + 1;

	if(Page_Num < 10) return;
  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 

	for(i=0;i<Page_Num;i++)
	{
		//擦除扇区
		if (FLASH_ErasePage(APPLICATION_ADDRESS + 1024*i)!= FLASH_COMPLETE)
		{
     /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
      while (1)
      {
      }
    }
		//读取数据
		memset((uint8_t *)appsize,0,sizeof(appsize));
		W25QXX_Read((uint8_t *)appsize,IAP_DATA_ADDR + 1024*i,1024);  
		write_addr = APPLICATION_ADDRESS + 1024*i;
		in_buff_temp = appsize;
		for(j=0;j<256;j++)
		{
			if (FLASH_ProgramWord(write_addr, *in_buff_temp) == FLASH_COMPLETE)
			{
				write_addr = write_addr + 4;
				in_buff_temp++;
			}
			else
			{ 
				/* Error occurred while writing data in Flash memory. 
					 User can add here some code to deal with this error */
				while (1)
				{
				}
			}
		}
		LED2_TOGGLE;
	}
	
	  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	
	GPIO_InitTypeDef        GPIO_InitStructure;
	/* GPIOB Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	//PB输出PB5,6		开漏	
	GPIO_InitStructure.GPIO_Pin = 	LED2_PIN ;
  GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  /* Keep the user application running */
		W25QXX_Init();	
		W25QXX_Read((uint8_t *)&IAP_str,PARA_DATA_ADDR,sizeof(IAP_str));
		//IAP_clean_para();
		if((IAP_str.APP_addr != 0)&&(IAP_str.plug_bin_len != 0xFFFFFFFF))
		{
			//程序写入
			IAP_Process();
			//清除升级参数
			//IAP_clean_para();
		}
    /* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
    if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
    {
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      
      /* Jump to application */
      Jump_To_Application();
    }
}


/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

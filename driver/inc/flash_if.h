/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/inc/flash_if.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USER_FLASH_LAST_PAGE_ADDRESS  0x0800F800
#define USER_FLASH_END_ADDRESS        0x0800FFFF /* 64 KBytes */
#define FLASH_PAGE_SIZE               0x400      /* 1 Kbytes */


#define APP_PARA_START_ADDR			APPLICATION_ADDRESS
#define APP_PARA_END_ADDR				APPLICATION_ADDRESS + 1024*30


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint8_t PARA_FLASH_Read(uint32_t *out_buff ,uint16_t out_buff_len);
uint8_t PARA_FLASH_Write(uint32_t * in_buff,uint16_t in_buff_len );
#endif  /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


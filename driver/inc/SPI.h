/**
  ******************************************************************************
  * @file    SPI/M25P64_FLASH/spi_flash.h 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Header for spi_flash.c file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_SPI_H
#define __API_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */


/* Exported functions --------------------------------------------------------*/
void SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler);
void SPI2_Init(void);

uint8_t SPI_ReadWriteByte(SPI_TypeDef* SPIx,uint8_t TxData);

#endif /* __API_SPI_H */










/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

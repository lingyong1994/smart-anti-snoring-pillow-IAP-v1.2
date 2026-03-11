
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BORD_CONF_H
#define __BORD_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "w25qxx.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define	F_SCF_PIN							GPIO_Pin_12		//SPI FLASH接口
#define	F_SCLK_PIN							GPIO_Pin_13
#define	F_MISO_PIN							GPIO_Pin_14
#define	F_MOSI_PIN							GPIO_Pin_15
#define W25QXX_CS_L						GPIOB->BRR = F_SCF_PIN 
#define W25QXX_CS_H						GPIOB->BSRR = F_SCF_PIN 
#define SPI_FLASH_PIN_SCK_L   GPIOB->BRR = F_SCLK_PIN 
#define SPI_FLASH_PIN_SCK_H   GPIOB->BSRR = F_SCLK_PIN 			
#define SPI_FLASH_PIN_MISO_L   GPIOB->BRR = F_MISO_PIN 
#define SPI_FLASH_PIN_MISO_H   GPIOB->BSRR = F_MISO_PIN 
#define SPI_FLASH_PIN_MOSI_L   GPIOB->BRR = F_MOSI_PIN 
#define SPI_FLASH_PIN_MOSI_H   GPIOB->BSRR = F_MOSI_PIN 

#define LED2_PIN					GPIO_Pin_6
#define LED2_L						GPIOB->BRR = GPIO_Pin_6 
#define LED2_H   		      GPIOB->BSRR = GPIO_Pin_6
#define LED2_TOGGLE        GPIOB->ODR ^= GPIO_Pin_6




#define APPLICATION_ADDRESS			0x08001000
#define IAP_DATA_ADDR						0x700000		//升级文件暂存区
#define PARA_DATA_ADDR					0x7C0000		//参数存储区




__packed typedef struct{
		uint32_t APP_addr;            //设备最新运行地址
    uint32_t plug_bin_len;      	//文件大小
		uint8_t plug_part_num;
}PLUG_OTA_BIN_S;

/* Exported functions ------------------------------------------------------- */

extern PLUG_OTA_BIN_S IAP_str;

extern void delay_us(unsigned int us);

/*------------------------------------------------------------
                         ms延时函数
------------------------------------------------------------*/
extern void delay_ms(unsigned int ms);

#endif /* __BORD_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

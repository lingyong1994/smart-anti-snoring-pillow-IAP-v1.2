/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/src/flash_if.c 
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
#include "flash_if.h"
#include "flash_if.h"

uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint8_t PARA_FLASH_Read(uint32_t *out_buff ,uint16_t out_buff_len)
{

	uint16_t i=0;
	uint32_t test_addr_temp=APP_PARA_START_ADDR;
//	in_buff_temp = in_buff;
	for(i=0;i<out_buff_len;i++)
	{
		out_buff[i] = *(uint32_t *)test_addr_temp;
		test_addr_temp += 4;
	}

}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint8_t PARA_FLASH_Write(uint32_t * in_buff,uint16_t in_buff_len )
{

	uint32_t * in_buff_temp;
	uint32_t test_data_temp=0;
	in_buff_temp = in_buff;
  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 

  /* Define the number of page to be erased */
  NbrOfPage = in_buff_len / FLASH_PAGE_SIZE+1;

  /* Erase the FLASH pages */
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    if (FLASH_ErasePage(APP_PARA_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter))!= FLASH_COMPLETE)
    {
     /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
      while (1)
      {
      }
    }
  }
  /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  Address = APP_PARA_START_ADDR;

  while (Address < (APP_PARA_START_ADDR + in_buff_len))
  {
    if (FLASH_ProgramWord(Address, *in_buff_temp) == FLASH_COMPLETE)
    {
      Address = Address + 4;
			in_buff_temp += 4;
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

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 


  /* Check if the programmed data is OK 
      MemoryProgramStatus = 0: data programmed correctly
      MemoryProgramStatus != 0: number of words not programmed correctly ******/
  Address = APP_PARA_START_ADDR;
  in_buff_temp = in_buff;
  while (Address < (APP_PARA_START_ADDR+in_buff_len))
  {
    test_data_temp = *(__IO uint32_t *)Address;

    if (test_data_temp != *(__IO uint32_t *)in_buff_temp)
    {
			return 1;
    }

    Address = Address + 4;
		in_buff_temp += 4;
  }

}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

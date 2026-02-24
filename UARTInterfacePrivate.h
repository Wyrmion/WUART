/**
  ******************************************************************************
  * @file     UARTInterfacePrivate.h
  * @author   Wyrm
  * @brief    Header file for UART Interface abstract class
  * @version  V1.0.1
  * @date     24 Feb. 2026
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_INTERFACE_PRIVATE_H__
#define __UART_INTERFACE_PRIVATE_H__


#include "UARTInterface.h"
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup UARTInterfacePrivate UART Interface private
 * @{
 */

/* Public macro -------------------------------------------------------------*/

/**
 * @brief UART Interface class 
 * 
 */
struct UartInterface
{
  void*   hwuart;                        /*!< pointer to hardware tim class*/
  
  int32_t IRQn;                         /*!< IRQ number for critical section*/
  bool    IRQnEnable;                   /*!< IRQ enable flag (use for critical section)*/

  
  void*   ctx;                          /*!< pointer to parent*/
  
  uint32_t RxCnt;  

  
  void(*RxClb)(void* ctx,uint32_t len);   /*!< Rx complete callback*/
  void(*TxClb)(void* ctx);              /*!< Tx complete callback */
  void(*ErrClb)(void* ctx);             /*!< Get Error callback*/
    
  #ifdef W_USE_RTOS
    struct
    {
      void*                                 ThreadId; /*!< pointer to rtos semaphore*/
      UartInterface_eIRQTag_t               tag;      /*!< IRQ tag then semaphore call*/
    }Os;
  #endif
};

/* Public function prototypes -----------------------------------------------*/

/** @} */  /* UART Interface group end */
/** @} */  /* Wyrm_Drivers group end*/


#ifdef __cplusplus
}
#endif

#endif


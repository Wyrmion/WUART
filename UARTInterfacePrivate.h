/**
  ******************************************************************************
  * @file     UARTInterfacePrivate.h
  * @author   Wyrm
  * @brief    Header file for UART Interface abstract class
  * @version  V1.0.0
  * @date     12 Nov. 2024
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

  #ifndef W_USE_RTOS
    void(*RxClb)(void* ctx,size_t len);   /*!< Rx complete callback*/
    void(*TxClb)(void* ctx);              /*!< Tx complete callback */
    void(*ErrClb)(void* ctx);             /*!< Get Error callback*/
  #else
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


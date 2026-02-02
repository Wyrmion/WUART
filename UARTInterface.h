/**
  ******************************************************************************
  * @file     UartInterface.h
  * @author   Wyrm
  * @brief    Header file for UartInterface
  * @version  V1.0.1
  * @date     25. Oct. 2025
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "main.h"


/* Public macro -------------------------------------------------------------*/
/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup UartInterface Uart Interface
 * @{
 */
#ifdef WINTERFACE_STATIC_ALLOCATE
  #include "UARTInterfacePrivate.h"
#endif
/**
 * @brief Uart Subscriber interface class
 * 
 */
#define UART_INTERFACE_NO_CRITICAL INT32_MAX
/**
 * @brief Uart Interface class 
 * 
 */
typedef struct UartInterface UartInterface_t;  

//#ifdef INC_FREERTOS_H
/**
 * @brief IRQ tag for semaphore unsleap
 * 
 */
//#ifdef INC_FREERTOS_H
  typedef enum
  {
    UartInterface_eIRQTag_NoEvent,
    UartInterface_eIRQTag_ClbRx   = 0b1,
    UartInterface_eIRQTag_ClbTx   = 0b10,
    UartInterface_eIRQTag_ClbErr  = 0b100,  
  }UartInterface_eIRQTag_t;
//#endif


/* Public function prototypes -----------------------------------------------*/
/**
 * @defgroup Uart_public_func Uart public function
 * @{
 */

  /**
   * @defgroup Template_public_ctor_dtor Template constructor/destructor
   * @{
   */
  #ifndef WINTERFACE_STATIC_ALLOCATE
    UartInterface_t*	  UartInterface_ctor(void* hwuart,int32_t IRQn);
    void                UartInterface_dtor(UartInterface_t* cthis);
  #else
    void                UartInterface_init(UartInterface_t* cthis,void* hwuart,int32_t IRQn);
  #endif 
  /** @}*/ /*End of Template constructor/destructor group*/
  
/**
 * @defgroup UartInterface_public_func Uart subscriber class public function
 * @{
 */
  bool UartInterface_SubscribeIrq(UartInterface_t* cthis);
  bool UartInterface_UnsubscribeIrq(UartInterface_t* cthis);

  void UartInterface_StartIT(UartInterface_t* cthis);
  void UartInterface_StopIT(UartInterface_t* cthis);

  bool UartInterface_StartRx(const UartInterface_t* cthis,uint8_t* dst,const size_t size);
  bool UartInterface_StartTx(const UartInterface_t* cthis,uint8_t* src,const size_t size);

  void UartInterface_CRITICAL_enter(UartInterface_t* cthis);
  void UartInterface_CRITICAL_exit(UartInterface_t* cthis);
  
  bool UartInterface_IsFreeRxTx(const UartInterface_t* cthis);
  bool UartInterface_IsFreeTx(const UartInterface_t* cthis);

  bool UartInterface_Reset(const UartInterface_t* cthis);

  #ifndef W_USE_RTOS
    bool UartInterface_SetClbRx(  UartInterface_t* cthis,void* ctx,void(*RxClb)(void* ctx,size_t len)) ;  /*!< Rx complete callback*/;
    bool UartInterface_SetClbTx(  UartInterface_t* cthis,void* ctx,void(*TxClb)(void* ctx));              /*!< Tx complete callback */
    bool UartInterface_SetClbErr( UartInterface_t* cthis,void* ctx,void(*ErrClb)(void* ctx));            /*!< Get Error callback*/
  #else
    UartInterface_eIRQTag_t UartInterface_GetIRQEvent(UartInterface_t* cthis);

    bool UartInterface_SetNotificationsThreadID(UartInterface_t *cthis,void* ctx, void *ThreadID);
    uint32_t UartInterface_GetRxCnt(const UartInterface_t *cthis);
  #endif
/** @}*/

/** @} */ /*End of Uart interface group*/
/** @} */ /*End of Wyrm drivers group*/

#ifdef __cplusplus
}
#endif

#endif


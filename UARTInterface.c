/**
 ****************************************************************************
 * @file     UARTInterface.C
 * @author   Wyrm
 * @brief    This file p1ovides code for work with UARTInterface abstract class
 * @version  V1.0.1
 * @date     24 Feb. 2026
 *************************************************************************
 */
 
#include "UARTInterface.h"

#include <stdlib.h>
#include <string.h>

#ifndef WINTERFACE_STATIC_ALLOCATE
  #include "wheap.h"
  #include "UARTInterfacePrivate.h"
#endif
/**
 * @addtogroup UARTInterface
 * @{
 */

  /** @defgroup UartInterface_Private_macro UartInterface Private macro
   * @{
   */
 
  /** @}*/ /* End of UartInterface macro group*/

  /** @defgroup UartInterface_Private_Functions UartInterface Private Functions
    * @{
    */

  /** @}*/

/**
 * @brief Uart interface init object
 * 
 * @param[in] cthis pointer to this @rer UartInterface_t obj
 * @param[in] hwuart pointer to hw class
 * @param[in] IRQn  irq number for critical section. Use UART_INTERFACE_NO_CRITICAL if you don't need enter critical section
 */
void UartInterface_init(UartInterface_t* cthis,void* hwuart,int32_t IRQn)
{
  memset(cthis,0,sizeof(*cthis));

  cthis->hwuart  = hwuart;
  cthis->IRQn = IRQn;
}

/**
 * @brief Uart interface constructor 
 * 
 * @param[in] hwuart pointer to hw class
 * @param[in] IRQn  irq number for critical section. Use UART_INTERFACE_NO_CRITICAL if you don't need enter critical section
 * @return UartInterface_t* allocated memory
 */
UartInterface_t*	  UartInterface_ctor(void* hwuart,int32_t IRQn)
{
  if(hwuart == NULL)
    return NULL;
  
  UartInterface_t* cthis;
  
  if((cthis = heap_malloc_cast(UartInterface_t)) == NULL)
    return NULL;
  
  UartInterface_init(cthis,hwuart,IRQn);
  
  return cthis;
}

/**
 * @brief Uart interface destructor 
 * 
 * @param cthis pointer to this @rer UartInterface_t obj
 */
void UartInterface_dtor(UartInterface_t* cthis)
{
  heap_free(cthis);
}


/**
 * @brief Set callback for Rx callback
 * 
 * @param[in] cthis  pointer to @ref UartInterface_t obj
 * @param[in] ctx pointer to ctx
 * @param[in] RxClb pointer to uart callback function
 * @return true  is setup succesful
 * @return false 
 */
bool UartInterface_SetClbRx(UartInterface_t* cthis,void* ctx,void(*RxClb)(void* ctx,uint32_t len))
{
  if((cthis == NULL)||(RxClb == NULL))
    return false;
  
  cthis->ctx = ctx;
  cthis->RxClb = RxClb;
  return true;
}

/**
 * @brief Set callback for Tx callback
 * 
 * @param[in] cthis  pointer to @ref UartInterface_t obj
 * @param[in] ctx pointer to ctx
 * @param[in] TxClb pointer to uart callback function
 * @return true  is setup succesful
 * @return false 
 */
bool UartInterface_SetClbTx(UartInterface_t* cthis,void* ctx,void(*TxClb)(void* ctx))            
{
  if((cthis == NULL)||(TxClb == NULL))
    return false;
  
  cthis->ctx = ctx;
  cthis->TxClb = TxClb;

  return true;
}

/**
 * @brief Set callback for Err callback
 * 
 * @param[in] cthis  pointer to @ref UartInterface_t obj
 * @param[in] ctx pointer to ctx
 * @param[in] ErrClb pointer to uart callback function
 * @return true  is setup succesful
 * @return false 
 */
bool UartInterface_SetClbErr(UartInterface_t* cthis,void* ctx,void(*ErrClb)(void* ctx))            /*!< Get Error callback*/
{
  if((cthis == NULL)||(ErrClb == NULL))
    return false;
  
  cthis->ctx = ctx;
  cthis->ErrClb = ErrClb;

  return true;
}


/**
* @brief Set callback for tim ellapsed
 * 
 * @param[in] cthis  pointer to @ref UartInterface_t obj
 * @param[in] ctx   pointer to ctx
 * @param[in] ThreadID pointer to thread ID
 * @return true is setup succesful
 * @return false 
 */
bool UartInterface_SetNotificationsThreadID(UartInterface_t *cthis,void* ctx, void *ThreadID)
{
  if((cthis == NULL)||(ThreadID == NULL))
      return false;

  cthis->ctx = ctx;
  cthis->Os.ThreadId = ThreadID;    
  
  return true;
}


/**
 * @brief Return last irq tag
 * 
 * @param[in] cthis  pointer to @ref UartInterface_t obj
 * @return UartInterface_eIRQTag_t 
 */
UartInterface_eIRQTag_t UartInterface_GetIRQEvent(UartInterface_t* cthis)
{
  __auto_type ret = cthis->Os.tag;
  
  cthis->Os.tag = UartInterface_eIRQTag_NoEvent;

  return ret;
}

  

/** @}*/ /*End of TimerInterface group*/
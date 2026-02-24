/**
 ****************************************************************************
 * @file     STHallTUartInterface.C
 * @author   Wyrm
 * @brief    This file provides code for work interface uart class 
 * @version  V1.0.0
 * @date     02. Nov. 2024						
 *************************************************************************
 */


#include <stdlib.h>

#include "UartInterfacePrivate.h"
#include "main.h"
#include "STHallUartInterface.h"

#ifdef W_USE_RTOS
  #include "cmsis_os.h"
#endif


/**
 * @addtogroup UartInterface 
 * @{
 */

 /**
  * @defgroup Uart_private_macro_basic Uart private basic macro
  * @{
  */
  #define ST_UART_CAST(cthis) ((UART_HandleTypeDef*)cthis)/*!< Uart cast from (void*)*/
/**@} */ /**  */

/**
 * @defgroup Uart_private_macro_indx_switch Uart private index swich macro
 * @{
 */
   /**
    * @defgroup Uart_private_macro_basic Usart to uart name macro (for index switch) 
    * @{
    */
    #ifdef USART1_BASE
      #define UART1_BASE USART1_BASE
    #endif
    #ifdef USART2_BASE
      #define UART2_BASE USART2_BASE
    #endif
    #ifdef USART3_BASE
      #define UART3_BASE USART3_BASE
    #endif
    #ifdef USART4_BASE
      #define UART4_BASE USART4_BASE
    #endif
    #ifdef USART5_BASE
      #define UART5_BASE USART5_BASE
    #endif
    #ifdef USART6_BASE
      #define UART6_BASE USART6_BASE
    #endif
    #ifdef USART7_BASE
      #define UART7_BASE USART7_BASE
    #endif
    #ifdef USART8_BASE
      #define UART8_BASE USART8_BASE
    #endif
    #ifdef USART9_BASE
      #define UART9_BASE USART9_BASE
    #endif
    #ifdef USART10_BASE
      #define UART10_BASE USART10_BASE
    #endif
    #ifdef USART11_BASE
      #define UART11_BASE USART11_BASE
    #endif
    #ifdef USART12_BASE
      #define UART12_BASE USART12_BASE
    #endif
    #ifdef USART13_BASE
      #define UART13_BASE USART13_BASE
    #endif
    #ifdef USART14_BASE
      #define UART14_BASE USART14_BASE
    #endif
    /**@} */ /**Ennd of usart to uart macro */

#define CHECK_ST_UART1     ~,~
#define CHECK_ST_UART2     ~,~
#define CHECK_ST_UART3     ~,~
#define CHECK_ST_UART4     ~,~
#define CHECK_ST_UART5     ~,~
#define CHECK_ST_UART6     ~,~
#define CHECK_ST_UART7     ~,~
#define CHECK_ST_UART8     ~,~
#define CHECK_ST_UART9     ~,~
#define CHECK_ST_UART10    ~,~
#define CHECK_ST_UART11    ~,~
#define CHECK_ST_UART12    ~,~
#define CHECK_ST_UART13    ~,~
#define CHECK_ST_UART14    ~,~

enum {kCOUNTER_UART_1_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_1_BASE - 1)  

#define UART_CASE_(num,counter) case (UART##num##_BASE): {return COUNTER_REL_INC(counter);}
#define UART_CASE(num) UART_CASE_(num,__COUNTER__)

#define UART_CASE_INDX_(num,indx,counter) case (UART##num##_BASE): {indx = COUNTER_REL_INC(counter);break;}
#define UART_CASE_INDX(num,indx) UART_CASE_INDX_(num,indx,__COUNTER__)

#define CAT(a, b) CAT_IMPL(a, b)
#define CAT_IMPL(a, b) a ## b

#define IS_ST_UART_DEFINED(num) CHECK((CAT(CHECK_,CAT(ST_UART,num)), 0, 1))
#define CHECK_ST_UART1 ~,~
#define CHECK(tup) CHECK_IMPL tup
#define CHECK_IMPL(a, b, c, ...) c

#define IIF(condition, true_value, false_value) CAT(IIF_,condition)(true_value, false_value)
#define IIF_0(true_value, false_value) false_value
#define IIF_1(true_value, false_value) true_value 

#define CASE_IF_ST_UART(num,indx)  IIF(IS_ST_UART_DEFINED(num), CASE_ST_UART, CASE_NOT_ST_UART)(num,indx)
// this will be used if ST_UART##num is defined:
#define CASE_ST_UART(num,indx)     UART_CASE_INDX(num,indx)
// this will be used if ST_UART##num is NOT defined:
#define CASE_NOT_ST_UART(num,indx) //

#define UART_IRQ_SWICH(mem,indx)\
  switch(mem){\
    CASE_IF_ST_UART(1, indx)\
    CASE_IF_ST_UART(2, indx)\
    CASE_IF_ST_UART(3, indx)\
    CASE_IF_ST_UART(4, indx)\
    CASE_IF_ST_UART(5, indx)\
    CASE_IF_ST_UART(6, indx)\
    CASE_IF_ST_UART(7, indx)\
    CASE_IF_ST_UART(8, indx)\
    CASE_IF_ST_UART(9, indx)\
    CASE_IF_ST_UART(10, indx)\
    CASE_IF_ST_UART(11, indx)\
    CASE_IF_ST_UART(12, indx)\
    CASE_IF_ST_UART(13, indx)\
    CASE_IF_ST_UART(14, indx)\
    default:  indx = -1;\
              break;\
  }\
  
/** @}*/ /** end of Uart private index swich macro*/

/** @defgroup UartInterface_Private_macro UartInterface Private macro
 * @{
 */
#ifndef USE_MACRO_SWITCH
static inline  int32_t _this_get_uart_indx(uint32_t uart);
#endif
/** @}*/ /* End of UartInterface macro group*/

/**
 * @brief Array of stm32 @ref UART_HandleTypeDef.
 * @note Used for link @ref sUartInterface_Handle_t obj with stm32 uart handle
 * 
 */
static UART_HandleTypeDef* huartarr[kUartInter_number_of_elem] = {
                                                                    #ifdef ST_UART1
                                                                    &huart1,
                                                                    #endif

                                                                    #ifdef ST_UART2
                                                                    &huart2,
                                                                    #endif

                                                                    #ifdef ST_UART3
                                                                    &huart3,
                                                                    #endif

                                                                    #ifdef ST_UART4
                                                                    &huart4,
                                                                    #endif

                                                                    #ifdef ST_UART5
                                                                    &huart5,
                                                                    #endif

                                                                    #ifdef ST_UART6                
                                                                    &huart6,
                                                                    #endif

                                                                    #ifdef ST_UART7
                                                                    &huart7,
                                                                    #endif

                                                                    #ifdef ST_UART8
                                                                    &huart8,
                                                                    #endif
                                                                              };
                                                                             
/**
 * @brief Array of pointer to @ref sUartInterface_Handle_t linked to stm32 handle 
 *
 */ 
static UartInterface_t* huartInter[kUartInter_number_of_elem] = {NULL};


/**
 * @brief Uart Subscriber
 * 
 * @param cthis pointer to @ref UartInterface_t 
 * @return true   if subscribe successful
 * @return false  error
 */
bool  UartInterface_SubscribeIrq(UartInterface_t* cthis)
{
   if( (cthis == NULL)||
      (cthis->hwuart == NULL))
    return false;  
  

  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
  UART_IRQ_SWICH((uint32_t)(ST_UART_CAST(cthis->hwuart)->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(cthis->hwuart)->Instance));
  #endif

  if( (indx >= 0)&&
      (huartInter[indx] == NULL)&&
      (HAL_UART_GetState(huartarr[indx]) == HAL_UART_STATE_READY))
    huartInter[indx] = cthis; 
  else 
    return false;

  return true;
}

enum {kCOUNTER_UART_2_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_2_BASE - 1)  

/**
 * @brief Uart unsubscribe
 * 
 * @param cthis pointer to @ref UartInterface_t 
 * @return true   if unsubscribe successful
 * @return false  error
 */
bool UartInterface_UnsubscribeIrq(UartInterface_t* cthis)
{
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    UART_IRQ_SWICH((uint32_t)(ST_UART_CAST(cthis->hwuart)->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(cthis->hwuart)->Instance));
  #endif
  
  if(indx < 0)  
    return false;
            
  if( ( indx<0 )||
      (huartInter[indx]!=cthis))
    return false;

  HAL_UART_Abort(huartarr[indx]); 
  huartInter[indx] = NULL;

  return true; 
}

/**
 * @brief Uart enter critical stm32 wrapper
 * 
 * @param cthis pointer to @ref UartInterface_t obj
 */
void UartInterface_CRITICAL_enter(UartInterface_t* cthis)
{
  if(cthis->IRQn == UART_INTERFACE_NO_CRITICAL)
    return;

  if((cthis->IRQnEnable = NVIC_GetEnableIRQ(cthis->IRQn)) == true)
    NVIC_DisableIRQ(cthis->IRQn);
}

/**
 * @brief Uart exit critical stm32 wrapper
 * 
 * @param cthis pointer to @ref UartInterface_t obj
 */
void UartInterface_CRITICAL_exit(UartInterface_t* cthis)
{
  if(cthis->IRQn == UART_INTERFACE_NO_CRITICAL)
    return; 

  if(cthis->IRQnEnable)
    NVIC_EnableIRQ(cthis->IRQn);
}

enum {kCOUNTER_UART_3_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_3_BASE - 1)  

/**
 * @brief Uart RX complete event(idle)
 * 
 * @param huart Uart @ref UART_HandleTypeDef
 * @param Size  rx data leng
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    UART_IRQ_SWICH((uint32_t)(huart->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(huart)->Instance));
  #endif

  if(indx < 0)  
    return;

  huartInter[indx]->RxCnt = Size;


   if(huartInter[indx]->RxClb != NULL) 
    huartInter[indx]->RxClb(huartInter[indx]->ctx,huartInter[indx]->RxCnt);

  #ifdef W_USE_RTOS
  huartInter[indx]->Os.tag = UartInterface_eIRQTag_ClbRx;

  if(huartInter[indx]->Os.ThreadId != NULL)
    osThreadFlagsSet(huartInter[indx]->Os.ThreadId,huartInter[indx]->Os.tag);
  #endif

}

enum {kCOUNTER_UART_4_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_4_BASE - 1)  
/**
 * @brief Uart RX complete
 * 
 * @param huart Uart @ref UART_HandleTypeDef
 * @param Size  rx data leng
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    UART_IRQ_SWICH((uint32_t)(ST_UART_CAST(huart)->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(huart)->Instance));
  #endif

  if(indx < 0)  
    return;
  huartInter[indx]->RxCnt = huart->RxXferCount;

  if(huartInter[indx]->RxClb != NULL) 
      huartInter[indx]->RxClb(huartInter[indx]->ctx,huartInter[indx]->RxCnt);

  #ifdef W_USE_RTOS
  huartInter[indx]->Os.tag = UartInterface_eIRQTag_ClbRx;

  if(huartInter[indx]->Os.ThreadId != NULL)
    osThreadFlagsSet(huartInter[indx]->Os.ThreadId,huartInter[indx]->Os.tag);
  #endif
  
}


enum {kCOUNTER_UART_5_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_5_BASE - 1)  

/**
 * @brief Uart TX complete event
 * 
 * @param huart Uart @ref UART_HandleTypeDef
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    UART_IRQ_SWICH((uint32_t)(ST_UART_CAST(huart)->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(huart)->Instance));
  #endif

  if(indx < 0)  
    return;
  
  

  if(huartInter[indx]->TxClb != NULL) 
    huartInter[indx]->TxClb(huartInter[indx]->ctx);
  
  #ifdef W_USE_RTOS
  huartInter[indx]->Os.tag = UartInterface_eIRQTag_ClbTx;
  
  if(huartInter[indx]->Os.ThreadId != NULL)
    osThreadFlagsSet(huartInter[indx]->Os.ThreadId,huartInter[indx]->Os.tag);
  #endif

}

enum {kCOUNTER_UART_6_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_6_BASE - 1)  
/**
 * @brief Uart error complete event
 * 
 * @param huart Uart @ref UART_HandleTypeDef
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart)
{
    #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    UART_IRQ_SWICH((uint32_t)(ST_UART_CAST(huart)->Instance),indx);
  #else
  __auto_type indx = _this_get_uart_indx((uint32_t)(ST_UART_CAST(huart)->Instance));
  #endif

  if(indx < 0)  
    return;


  if(huartInter[indx]->ErrClb != NULL) 
    huartInter[indx]->ErrClb(huartInter[indx]->ctx);
  
  #ifdef W_USE_RTOS
  huartInter[indx]->Os.tag = UartInterface_eIRQTag_ClbErr;

  if(huartInter[indx]->Os.ThreadId != NULL)
    osThreadFlagsSet(huartInter[indx]->Os.ThreadId,huartInter[indx]->Os.tag);
  #endif  
  
}


enum {kCOUNTER_UART_7_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_UART_7_BASE - 1) 

#ifndef USE_MACRO_SWITCH
/**
 * @brief Get uart interface index
 * 
 * @param[in] uart Peripheral addres
 * @return int32_t -1 if index not found or >= 0  in found
 */
static inline  int32_t _this_get_uart_indx(uint32_t uart)
{
  switch(uart)
  {
    #ifdef ST_UART1
      UART_CASE(1);
    #endif

    #ifdef ST_UART2
      UART_CASE(2);
    #endif

    #ifdef ST_UART3
      UART_CASE(3);
    #endif

    #ifdef ST_UART4
      UART_CASE(4);
    #endif
    #ifdef ST_UART5
      UART_CASE(5);
    #endif
    #ifdef ST_UART6
      UART_CASE(6);
    #endif
    #ifdef ST_UART7
      UART_CASE(7);    
    #endif
    #ifdef ST_UART8
      UART_CASE(8);
    #endif
    #ifdef ST_UART9
      UART_CASE(9);
    #endif
    #ifdef ST_UART10
      UART_CASE(10);
    #endif
    #ifdef ST_UART11
      UART_CASE(11);
    #endif
    #ifdef ST_UART12
      UART_CASE(12);
    #endif
    #ifdef ST_UART13
      UART_CASE(13);
    #endif
    #ifdef ST_UART14
      UART_CASE(14);
    #endif
  }
  return -1;
}
#endif

/**
 * @brief Start UART recive 
 * 
 * @param[in] cthis pointer to @ref UartInterface_t obj 
 * @param[in] dst   poiner to destination buffer   
 * @param[in] size  size of destination buffer 
 * @return true   if recive start successful 
 * @return false  
 */
bool UartInterface_StartRx(const UartInterface_t* cthis,uint8_t* dst,const size_t size)
{       
  if(HAL_UARTEx_ReceiveToIdle_DMA(cthis->hwuart,dst,size) != HAL_OK) 
    return false;
    
  __HAL_DMA_DISABLE_IT(ST_UART_CAST(cthis->hwuart)->hdmarx,DMA_IT_HT);
  return true;  
}

/**
 * @brief Start UART transmit 
 * 
 * @param[in]   cthis pointer to @ref UartInterface_t obj 
 * @param[out]  src   poiner to source  buffer
 * @param[in]   size  size of sourse buffer 
 * @return true if transmit start successful
 * @return false 
 */
bool UartInterface_StartTx(const UartInterface_t* cthis,uint8_t* src,const size_t size)
{
  if(HAL_UART_Transmit_DMA(cthis->hwuart,src,size) != HAL_OK)
    return false;
  return true;  
}

/**
 * @brief Check is rx and tx free
 * 
 * @param[in]   cthis pointer to @ref UartInterface_t obj 
 * @return true  if free
 * @return false else 
 */
bool UartInterface_IsFreeRxTx(const UartInterface_t* cthis)
{
  return (HAL_UART_GetState(cthis->hwuart)==HAL_UART_STATE_READY);
}

/**
 * @brief Get RX count
 * 
 * @param[in]   cthis pointer to @ref UartInterface_t obj 
 * @return uint32_t 
 */
uint32_t UartInterface_GetRxCnt(const UartInterface_t *cthis)
{
  return cthis->RxCnt;
}

/**
 * @brief Check is tx free
 * 
 * @param[in]   cthis pointer to @ref UartInterface_t obj 
 * @return true  if free
 * @return false else 
 */
bool UartInterface_IsFreeTx(const UartInterface_t* cthis)
{
    __auto_type tx_state = HAL_UART_GetState(cthis->hwuart);

    if((tx_state&HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX)
      return false;
    
    return true;
}

/**
 * @brief Reset UART RXTX
 * 
 * @param[in]   cthis pointer to @ref UartInterface_t obj 
 * @return true if reset successful
 * @return false 
 */
bool UartInterface_Reset(const UartInterface_t* cthis)
{
  return (HAL_UART_Abort(cthis->hwuart)==HAL_OK);
}





/** @} */ /*End of uart interface group group*/
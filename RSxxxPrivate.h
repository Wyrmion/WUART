/**
  ******************************************************************************
  * @file     RSxxxPrivate.h
  * @author   Wyrm
  * @brief    Header file for RSxxx private class 
  * @version  V1.2.9
  * @date     08 Nov. 2026
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RS_XXX_PRIVATE_H__
#define __RS_XXX_PRIVATE_H__




#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef W_USE_RTOS
  #include "cmsis_os2.h"
#endif

//#include "RSxxx.h"

/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup RSxxxInterfacePrivate RSxxx Interface private
 * @{
 */

/* Public macro -------------------------------------------------------------*/

/**
 * @brief RSxxx Interface class 
 * 
 */
typedef struct     
{
  uint8_t*      src;
  uint8_t*      dst;

  const size_t  src_dst_size;
}RSxxx_sStaticCfg;

struct RSxxx //public: HWInterface_t
{
  #ifdef WINTERFACE_USE_INTERFACE_PARENT_LIB
    HWInterface_t       parent;       /*!< Parent  @ref HWInterface_t */
  #endif
    RSxxx_eRSMode_t    Mode;         /*!< RS mode @ref eMyStRSxxxMode_t*/
  
  #ifdef W_RSXXX_USE_HW_PIN
   RS4xxDEnRE_t DEnRE; 
  #endif 

  uint8_t*            RxBuff;       /*!< Pointer to external RxBuff*/
  size_t              RxBuff_Maxlen;/*!< sizeof external RxBuff*/  
  
  uint8_t*            RxBuffInternal; /*!< Internal Rx buffer*/
  uint32_t            Rxlen;          /*!< Bytes received */
  
  uint8_t*            TxBuff;                               /*!< Pointer to external TxBuff*/
  size_t              TxBuff_Maxlen;                        /*!< sizeof external RxBuff*/  
  
  uint8_t*            TxBuffInternal; /*!< Internal Rx buffer*/

  size_t              InternalSize;
  
  bool                drdy;                                 /*!<Rx Data ready signal*/

  UartInterface_t*    hwinter;                       /*!<Uart IRQ Subscriber class*/

  #ifdef W_USE_RTOS
    void*             ThreadID;
  #endif
};
/* Public function prototypes -----------------------------------------------*/

/** @} */  /* RSxxx Interface group end */
/** @} */  /* Wyrm_Drivers group end*/


#ifdef __cplusplus
}
#endif

#endif


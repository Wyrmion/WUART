/**
  ******************************************************************************
  * @file     RSxxxInterfacePrivate.h
  * @author   Wyrm
  * @brief    Header file for RSxxx Interface abstract class
  * @version  V1.0.0
  * @date     12 Nov. 2024
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_INTERFACE_PRIVATE_H__
#define __TIMER_INTERFACE_PRIVATE_H__



#include "cmsis_os2.h"
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef W_USE_RTOS
  #include "cmsis_os.h"
#endif

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

  #ifdef RS4XX_USE_HW_PIN
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


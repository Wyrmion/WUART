/**
  ******************************************************************************
  * @file     MyStRSxxx.h
  * @author   Wyrm
  * @brief    Header file for RSxxx abstract layer
  * @version  V1.1.1
  * @date     26 Feb. 2026
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_ST_RSXXX_H__
#define __MY_ST_RSXXX_H__


#include "UARTInterface.h"
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>



/**
 * @addtogroup Interface Interface
 * @{
 */

/**
 * @defgroup MySTRSxxx My ST RSxxxx abstract layer
 * @{
 */

/**
 * @brief Recommended Standard (RS) enumeration 
 * 
 */
typedef enum
{
  RSxxx_eRSMode_RS232, /*!< 232 */
  RSxxx_eRSMode_RS485, /*!< 485 Half-duplex*/
  RSxxx_eRSMode_RS422, /*!< 422 Full-duplex*/
}RSxxx_eRSMode_t;

typedef struct RSxxx RSxxx_t; /*!< RSxxx class declaration :public @ref HWInterface_t*/
#ifdef RS4XX_USE_HW_PIN
 #include "RS4xxDEnRE.h"
#endif 

#ifdef WINTERFACE_STATIC_ALLOCATE
  #include "RSxxxPrivate.h"
#endif

typedef struct
{
  UartInterface_t*  hwinter;      /*!< Pointer to platform @ref UART_HandleTypeDef  */
  size_t            intbuffsize;  /*!< Internal buffer size                         */
  RSxxx_eRSMode_t   Mode;         /*!< Mode  @ref RSxxx_eRSMode_t RS4xx mode        */
  #ifdef RS4XX_USE_HW_PIN
  RS4xxDEnRE_t*     DEnRE;        /*!< DEnRE transciver pin struct @ref RS4xxDEnRE_t */
  #endif
  #ifdef W_USE_RTOS
    void*     Thread;             /*!< Pointer to thread ID for call notifi*/
  #endif 
}RSxxx_sInitConfig_t;
/**
 * @defgroup RSxxx_public_func MyStRSxxx public function
 * @{
 */

  /**
   * @defgroup RSxxx_public_ctor_dtor MyStRSxxx constructor/destructor
   * @{
   */
  #ifndef WINTERFACE_STATIC_ALLOCATE
    RSxxx_t*  RSxxx_ctor(RSxxx_sInitConfig_t* cnfg);
    void      RSxxx_dtor(RSxxx_t* cthis);
  #else    
    bool      RSxxx_init(RSxxx_t* cthis,UartInterface_t* hwinter,const RSxxx_sStaticCfg* cfg);
  #endif

  #ifdef RS4XX_USE_HW_PIN
 

  
    #ifndef WINTERFACE_STATIC_ALLOCATE
      RSxxx_t*  RSxxx_ctorRS4xx(RSxxx_sInitConfig_t* cnfg);
    #else
      bool      RSxxx_InitRS4xx(RSxxx_t* cthis,UartInterface_t* hwinter,const RSxxx_sStaticCfg* cfg, RSxxx_eRSMode_t Mode,RS4xxDEnRE_t* DenRe);
    #endif
  #endif
  /** @}*/

  /**
   * @defgroup RSxxx_public_mode MyStRSxxx set RS4xx @ref mode RSxxx_eRSMode_t
   * @{
   */
  void      MyStRSXXX_SetRS4xxMode(RSxxx_t* cthis, RSxxx_eRSMode_t Mode);
  /** @}*/
/** @}*/

/** @}*/
/** @}*/

#ifdef __cplusplus
}
#endif

#endif
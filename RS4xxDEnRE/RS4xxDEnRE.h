 /**
  ******************************************************************************
  * @file     RS4xxDEnRE.h
  * @author   Wyrm
  * @brief    Header file for fork with RS4xx transceiver
  * @version  V1.0.1
  * @date     16. Dec. 2024
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RS4XX_DE_NRE_H__
#define __RS4XX_DE_NRE_H__



#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>

#include "WPin.h"


/**
 * @addtogroup MySTRSxxx 
 * @{
 */

/**
 * @defgroup RS485Pin RS485/RS422 pin control
 * @{
 */


/**
 * @brief De/nRe pin struct @ref MyHALPin_t
 * 
 */
typedef struct
{   
	WPin_t De;    /*!< Driver   pin*/
  WPin_t nRe;   /*!< Reciver  pin*/
}RS4xxDEnRE_t;

/**
 * @defgroup RS485_public_function RS485 transceiver public function
 * @{
 */

  /**
   * @defgroup RS485_public_pins RS485 transceiver half-duplex synchronous control of two pins (DenRe)
   * @{
   */
  void    RS4xxDEnRE_SetTxTPins(const RS4xxDEnRE_t* DenRePins);    	
  void    RS4xxDEnRE_SetRxTPins(const RS4xxDEnRE_t* DenRePins);     
  /** @}*/
  
  /**
  * @defgroup RS485_public_pin RS485 transceiver half/full duplex independent control one of two pins (DenRe)
  * @{
  */
  void    RS4xxDEnRE_SetTxSPin(const RS4xxDEnRE_t* DenRePins,bool state);         
  void    RS4xxDEnRE_SetRxSPin(const RS4xxDEnRE_t* DenRePins,bool state);         
  /** @}*/
  
  /**
   * @defgroup RS485_public_sleep RS485 transceiver speep mode enable (only if have two pins control)
   * @{
   */
  void 	  RS4xxDEnRE_SetSleep(const RS4xxDEnRE_t* DenRePins);			
  /** @}*/

  /**
   * @defgroup RS485_public_sup   RS485 transceiver support function
   * @{
   */
    bool	  RS4xxDEnRE_isDenReTwoPins(const RS4xxDEnRE_t* DenRePins);
  /** @}*/
/** @}*/

/** @}*/
/** @}*/
#ifdef __cplusplus
}
#endif

#endif
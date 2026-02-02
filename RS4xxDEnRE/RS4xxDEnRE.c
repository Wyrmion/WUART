/**
 ****************************************************************************
  * @file     RS4xxDEnRE.c
  * @author   Wyrm
  * @brief    Source file for fork with RS4xx transceiver
  * @version  V1.0.1
  * @date     16. Dec. 2024
 *************************************************************************
 */
 
#include "RS4xxDEnRE.h"
#include <string.h>


/**
 * @addtogroup RS485Pin 
 * @{
 */

/**
  * @brief  Switch transceiver to TX using two pins (De and nRe)
	* @param  DenRePins pin struct @ref RS4xxDEnRE_t
  */
void    RS4xxDEnRE_SetTxTPins(const RS4xxDEnRE_t* DenRePins)       
{

  if((DenRePins->De.Pin != 0) && ((DenRePins->De.Port)!=NULL)) 
    WPIN_S_SET(DenRePins->De);
  if((DenRePins->nRe.Pin != 0) && ((DenRePins->nRe.Port)!=NULL)) 
    WPIN_S_SET(DenRePins->nRe);

}

/**
  * @brief  Switch transceiver De pin to selected state 
	* @param  DenRePins pin struct @ref RS4xxDEnRE_t
  * @param  state true - driver on, false - off 
  */
void    RS4xxDEnRE_SetTxSPin(const RS4xxDEnRE_t* DenRePins,bool state)   
{
  if((DenRePins->De.Pin != 0) && ((DenRePins->De.Port)!=NULL)) 
  {
    if(state) WPIN_S_SET(DenRePins->De);
    else  WPIN_S_RESET(DenRePins->De);
  }
}


/**
  * @brief  Switch transceiver to RX using two pins (De and nRe)
	* @param  DenRePins pin struct @ref RS4xxDEnRE_t
  */
void    RS4xxDEnRE_SetRxTPins(const RS4xxDEnRE_t* DenRePins)
{

  if((DenRePins->De.Pin != 0) && ((DenRePins->De.Port)!=NULL)) 
    WPIN_S_RESET(DenRePins->De);
  if((DenRePins->nRe.Pin != 0) && ((DenRePins->nRe.Port)!=NULL)) 
    WPIN_S_RESET(DenRePins->nRe);

}

/**
  * @brief  Switch transceiver nRe pin to selected state 
	* @param  DenRePins pin struct @ref RS4xxDEnRE_t
  * @param  state true - reciver on, false - off
  */
 void RS4xxDEnRE_SetRxSPin(const RS4xxDEnRE_t* DenRePins,bool state)
{

  if((DenRePins->De.Pin != 0) && ((DenRePins->De.Port)!=NULL)) 
  {
    if(state)    
      WPIN_S_RESET(DenRePins->nRe);
    else         
      WPIN_S_SET(DenRePins->nRe);
  }
}


/**
  * @brief  Switch transceiver to sleep mode using two pins (De and nRe)
	* @param  DenRePins pin struct @ref RS4xxDEnRE_t
  */
void    RS4xxDEnRE_SetSleep(const RS4xxDEnRE_t* DenRePins)
{

  if(RS4xxDEnRE_isDenReTwoPins(DenRePins))
  {
    WPIN_S_RESET(DenRePins->De);
    WPIN_S_SET(DenRePins->nRe);
  }

}

/**
 * @brief Check is struct @ref RS4xxDEnRE_t have two pins
 * 
 * @param  DenRePins pin struct @ref RS4xxDEnRE_t
 * @return true - two pins used
 * @return false - one pin
 */
bool    RS4xxDEnRE_isDenReTwoPins(const RS4xxDEnRE_t* DenRePins)
{
	if( (DenRePins->nRe.Port != NULL)&& 
		  (DenRePins->nRe.Pin  != 0) && 
	    (DenRePins->De.Port  != NULL) && 
		  (DenRePins->De.Pin   != 0))
	{
		return true;
	}
  return false;
}

/** @}*/ 
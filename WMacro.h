/**
  ******************************************************************************
  * @file     WMacro.h
  * @author   Wyrm
  * @brief    Header file for Wyrm std macros
  * @version  V1.0.0
  * @date     30. Oct. 2025
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W_MACRO_H__
#define __W_MACRO_H__


#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup main_group
 * @{
 */

/**
 * @defgroup W_Macro Wyrm std macros
 * @{
 */
#define W_UNUSED(x) (void)x

#define W_CONSTRAIN(x,lower,upper)    ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))
#define W_HTONS_16(x)                 ((((a)>>8)&0xff)|(((a)<<8)&0xff00)) 

#define W_ARRAY_SIZE(x)               (sizeof(x)/sizeof(x[0]))
/* Public macro -------------------------------------------------------------*/


/** @}*/  /* End of Template group */
/** @}*/ /* End of main_group group */


#ifdef __cplusplus
}
#endif

#endif


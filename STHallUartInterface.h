/**
 ****************************************************************************
 * @file    STHallUartInterface.h
 * @author  Wyrm
 * @brief   This is a project-specific configuration file (should be skip-worktree in git). 
 *          Comment out the necessary lines to properly configure the project 
 * @version V1.0.1
 * @date    09. Jan. 2025							
 *************************************************************************
 */
#ifndef __ST_HALL_UART_INTERFACE_H__
#define __ST_HALL_UART_INTERFACE_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include "main.h"

/**ыфва 
 * @addtogroup UartInterface 
 * @{
 */

/**
 * @defgroup STHallUartInterface STHallUartInterface Config file 
 * @note
 * @{
 */
/* Private macro -------------------------------------------------------------*/
#define ST_UART1
//#define ST_UART2
#define ST_UART3
//#define ST_UART4
//#define ST_UART5
//#define ST_UART6
//#define ST_UART7
#define ST_UART8
//#define ST_UART9
//#define ST_UART10
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions -------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ST_UART1
extern UART_HandleTypeDef huart1; /*!< external platform dependent uart1 handle*/
#endif

#ifdef ST_UART2
extern UART_HandleTypeDef huart2; /*!< external platform dependent uart2 handle*/
#endif 

#ifdef ST_UART3
extern UART_HandleTypeDef huart3; /*!< external platform dependent uart3 handle*/
#endif 

#ifdef ST_UART4
extern UART_HandleTypeDef huart4; /*!< external platform dependent uart4 handle*/
#endif 

#ifdef ST_UART5
extern UART_HandleTypeDef huart5; /*!< external platform dependent uart5 handle*/
#endif 

#ifdef ST_UART6
extern UART_HandleTypeDef huart6; /*!< external platform dependent uart6 handle*/
#endif 

#ifdef ST_UART7
extern UART_HandleTypeDef huart7; /*!< external platform dependent uart7 handle*/
#endif 

#ifdef ST_UART8
extern UART_HandleTypeDef huart8; /*!< external platform dependent uart8 handle*/
#endif


/**
 * @brief   Used uart's enumerate in current code 
 * @details this enumeration is needed to determine the number of uarts to be used
 */
typedef enum {	
                #ifdef ST_UART1
                    kUartInter_huart1,
                #endif

                #ifdef ST_UART2
                    kUartInter_huart2,
                #endif

                #ifdef ST_UART3
                    kUartInter_huart3,
                #endif

                #ifdef ST_UART4
                    kUartInter_huart4,
                #endif

                #ifdef ST_UART5
                    kUartInter_huart5,
                #endif

                #ifdef ST_UART6                
                    kUartInter_huart6,
                #endif

                #ifdef ST_UART7
                    kUartInter_huart7,
                #endif

                #ifdef ST_UART8
                    kUartInter_huart8,
                #endif

                kUartInter_number_of_elem
}eUartHandle_t;



/** @}*/
/** @}*/

#ifdef __cplusplus
}
#endif

#endif
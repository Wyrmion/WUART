/**
 ****************************************************************************
 * @file    MyStRSxxx.c
 * @author  Wyrm
 * @brief   cthis file provide code for RSxxx abstract layer
 * @version V1.2.1
 * @date   	03 Feb. 2026
 * @todo    Move all platform depending code to @ref sUartInterface_Handle_t
 *************************************************************************
 */
 

#include <string.h>

#include "RSxxx.h" 
#include "UARTInterface.h"
#include "WMacro.h"


#ifdef WINTERFACE_USE_INTERFACE_PARENT_LIB
  #include "InterfacePrivate.h"
#endif

#ifndef WINTERFACE_STATIC_ALLOCATE
  #include "wheap.h"
  #include "RSxxxPrivate.h"
#endif





/* Private macro -------------------------------------------------------------*/


/**
 * @addtogroup MySTRSxxx 
 * @{
 */

/**
 * @defgroup RSxxx_defines_group MyStRSxxx defines 
 * @{
 */

#define _this_start_rx(cthis)  UartInterface_StartRx(cthis->hwinter,cthis->RxBuffInternal,cthis->InternalSize)
//  #define INTERNAL_BUFFER_SIZE 255 /*!< @ref RSxxx internal rx/tx buffer size*/
/** @}*/




/** @defgroup RSxxx_Private_Functions RSxxx Private Functions
  * @{
  */
  static void ResetDrdy(RSxxx_t* cthis);

  /**
   * @defgroup RSxxx_Private_HWSubsribe RSxxx @ref sUartInterface_Handle_t private functions 
   * @{
   */
    static void URxIrq(void* cthis_ptr,uint32_t len);
    static void UTxIrq(void* cthis_ptr);
    static void UErrorIrq(void* cthis_ptr);  
  /** @}*/

  /**
   * @defgroup RSxxx_Private_HWIntrfc RSxxx @ref HWInterface_t private functions 
   * @{
   */
    static bool ReadRxBuff( void* cthis_ptr,uint8_t* data,   size_t* len,size_t  max_len);
    static void SetRxBuff(  void* cthis_ptr,uint8_t* RxBuff, size_t  max_len);
    static void SetTxBuff(  void* cthis_ptr,uint8_t* RxBuff, size_t  max_len);
    static bool SendData(   void* cthis_ptr,uint8_t* data,   size_t len);
    static void Process(    void* cthis_ptr); 
    static bool IsFree(     void* cthis_ptr);
    static bool Connect(    void* cthis_ptr);
    #ifdef W_USE_RTOS
      static void _this_os_thread(  void* cthis_ptr);
    #endif
  /** @}*/
/** @}*/
#ifdef WINTERFACE_USE_INTERFACE_PARENT_LIB
static HwInterface_vtable_t vtable = {
    .ReadRxBuff = ReadRxBuff,
    .SetRxBuff = SetRxBuff,
    .SetTxBuff = SetTxBuff,
    .SendData = SendData,
    .IsFree = IsFree,
    .Process = Process,
    .Connect = Connect,

}/*!< setup @ref HWInterface_t vtable*/;
#endif

 bool RSxxx_init(RSxxx_t* cthis,UartInterface_t* hwinter,const RSxxx_sStaticCfg* cfg)
 {
    if((cfg->src == NULL)||(cfg->dst == NULL)||(hwinter == NULL))
      return false;

    #ifndef INC_FREERTOS_H    
      UartInterface_SetClbErr(cthis->hwinter,cthis,UErrorIrq);
      UartInterface_SetClbRx(cthis->hwinter,cthis,URxIrq);
      UartInterface_SetClbTx(cthis->hwinter,cthis,UTxIrq);
    #else 
      UNUSED(URxIrq);
      UNUSED(UTxIrq);
      UNUSED(UErrorIrq);
    #endif

    cthis->hwinter = hwinter;
    #ifdef WINTERFACE_USE_INTERFACE_PARENT_LIB
    cthis->parent.vtable = &vtable;
    #endif
    cthis->InternalSize = cfg->src_dst_size;

    cthis->RxBuffInternal = cfg->dst;
    cthis->TxBuffInternal = cfg->src;

    cthis->drdy   = false;

    cthis->RxBuff = NULL;
    cthis->RxBuff_Maxlen = 0;

    cthis->TxBuff = NULL;
    cthis->TxBuff_Maxlen = 0;

    cthis->Mode = RSxxx_eRSMode_RS232;  

    #ifdef W_USE_RTOS
      UartInterface_SetNotificationsThreadID(cthis->hwinter,cthis, cthis->ThreadID);
    #endif
    

    
    return true;
 }



 #ifndef WINTERFACE_STATIC_ALLOCATE
/**
 * @brief RSxxx default class constructor
 * @param hwuart pointer to platform @ref UART_HandleTypeDef
 * @param intbuffsize internal buffer size
 * @return RSxxx_t*
 */
RSxxx_t* RSxxx_ctor(UartInterface_t* hwinter,size_t intbuffsize)
{  
  if(hwinter == NULL) 
    return NULL;
  RSxxx_t *cthis;

  if((cthis = heap_malloc_cast(RSxxx_t)) == NULL)
    while(1);
  if((cthis->InternalSize = intbuffsize) == 0)
    while(1);

  const RSxxx_sStaticCfg cfg = 
  {
    .src = heap_malloc(cthis->InternalSize),
    .dst = heap_malloc(cthis->InternalSize),
    .src_dst_size = intbuffsize};
  
  RSxxx_init(cthis,hwinter,&cfg);

  //StartUartRx(cthis); 
  return cthis;
}
/**
 * @brief RSxxx class destructor
 * 
 * @param cthis pointer to @ref RSxxx_t
 */
void RSxxx_dtor(RSxxx_t *cthis)
{
  heap_free(cthis);
}

#ifdef RS4XX_USE_HW_PIN
bool RSxxx_InitRS4xx(RSxxx_t* cthis,UartInterface_t* hwinter,const RSxxx_sStaticCfg* cfg, RSxxx_eRSMode_t Mode,RS4xxDEnRE_t* DEnRE)
{

  cthis->Mode = Mode;
  cthis->DEnRE = *DEnRE;  
  RS4xxDEnRE_SetRxTPins(&cthis->DEnRE);

  return RSxxx_init(cthis,cthis->hwinter,cfg);
  
}
/**
 * @brief Class RSxxx RS4xx class constructor
 * @note  delegate to @ref RSxxx_ctor()
 * @param cnfg pointer to config struct @ref RSxxx_sInitConfig_t
 * @return pointer to @ref RSxxx_t, or NULL if memory not allocated
 */
RSxxx_t*  RSxxx_ctorRS4xx(RSxxx_sInitConfig_t* cnfg) //: RSxxx_ctor(hwuart)
{
    if((cnfg->Mode != RSxxx_eRSMode_RS422)&&(cnfg->Mode != RSxxx_eRSMode_RS485)) return NULL;
    if(cnfg->DEnRE == NULL) return NULL;
    
    __auto_type cthis =  RSxxx_ctor(cnfg->hwinter,cnfg->intbuffsize);
    
    if(cthis == NULL) 
      return cthis;

    cthis->Mode = cnfg->Mode;

    cthis->DEnRE = *cnfg->DEnRE;
    
    RS4xxDEnRE_SetRxTPins(&cthis->DEnRE);
    
    return cthis;
}
#endif /* RS4XX_USE_HW_PIN */
#endif /* WINTERFACE_STATIC_ALLOCATE */


#ifdef W_USE_RTOS
static void _this_os_thread(void* cthis_ptr)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;

  switch(UartInterface_GetIRQEvent(cthis->hwinter))
  {
    case UartInterface_eIRQTag_NoEvent: break;
    case UartInterface_eIRQTag_ClbRx:   URxIrq(cthis_ptr,UartInterface_GetRxCnt(cthis->hwinter));
                                        break;
    case UartInterface_eIRQTag_ClbTx:   UTxIrq(cthis_ptr);
                                        break;
    case UartInterface_eIRQTag_ClbErr:  UErrorIrq(cthis_ptr);
                                        break;
  }
}
#endif


/**
 * @brief Realization of @ref sUartInterface_Handle_t recive complete callback
 * @param cthis_ptr  pointer to @ref RSxxx_t
 * @param len       bytes received
 */
static void URxIrq(void* cthis_ptr,uint32_t len)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;
  
  if(len<=cthis->RxBuff_Maxlen)
  {
    cthis->Rxlen = len;
    memcpy(cthis->RxBuff,cthis->RxBuffInternal,len);
    cthis->drdy = true;
  }

  _this_start_rx(cthis);
};

/**
 * @brief Realization of @ref sUartInterface_Handle_t transmit complete callback
 * @param cthis_ptr  pointer to @ref RSxxx_t
 */
static void UTxIrq(void* cthis_ptr)
{
  
  
  #ifdef RS4XX_USE_HW_PIN
  __auto_type cthis = (RSxxx_t*)cthis_ptr;

  if(cthis->Mode == RSxxx_eRSMode_RS422)
    RS4xxDEnRE_SetTxSPin(&cthis->DEnRE,false);
    
  if(cthis->Mode == RSxxx_eRSMode_RS485)
  {
    RS4xxDEnRE_SetRxTPins(&cthis->DEnRE);
    _this_start_rx(cthis);
  }
  #else 
  W_UNUSED(cthis_ptr);
  #endif
};

/**
 * @brief Realization of @ref sUartInterface_Handle_t tx/rx error  callback
 * @param cthis_ptr  pointer to @ref RSxxx_t
 */
static void UErrorIrq(void* cthis_ptr)
{  
  //__auto_type* cthis = (RSxxx_t*)cthis_ptr;
  W_UNUSED(cthis_ptr); 
  
}



/**
 * @brief   Realization of @ref HWInterface_t Connect function
 * @warning drop to while(1) if error for bug catch;
 * @param   cthis_ptr  pointer to @ref RSxxx_t
 * @return  true      if everything ok
 */
static bool Connect(void* cthis_ptr)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;
  
  if(!UartInterface_SubscribeIrq(cthis->hwinter))
    while(1); //bugcatch
  
  UartInterface_StartRx(cthis->hwinter,cthis->RxBuffInternal,cthis->InternalSize);

  return true;
}

/**
 * @brief Realization of @ref HWInterface_t set external rx buffer pointer
 * 
 * @param cthis_ptr  pointer to @ref RSxxx_t
 * @param RxBuff    pointer to linked external rx buffer
 * @param max_len   size of external buffer
 */
static void SetRxBuff(void* cthis_ptr,uint8_t* RxBuff,size_t max_len)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;

  if(max_len>cthis->InternalSize) while(1);//error chk
  
  cthis->RxBuff = RxBuff;
  cthis->RxBuff_Maxlen = max_len;  
}

/**
 * @brief Realization of @ref HWInterface_t set external tx buffer pointer
 * 
 * @param cthis_ptr  pointer to @ref RSxxx
 * @param TxBuff    pointer to linked external tx buffer
 * @param max_len   size of external buffer 
 */
static void SetTxBuff(void* cthis_ptr,uint8_t* TxBuff,size_t max_len)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;
 
  if(max_len>cthis->InternalSize) while(1);//error chk

  cthis->TxBuff = TxBuff;
  cthis->TxBuff_Maxlen = max_len;
}

/**
 * @brief Realization of @ref HWInterface_t read rx buffer 
 * 
 * @param   cthis_ptr  pointer to @ref RSxxx
 * @param   data      pointer to read data  (unused at cthis class)
 * @param   len       size of read data     (unused at cthis class)
 * @param   max_len   max data size         (unused at cthis class)
 * @return  true      if data ready at cthis class
 * @return  false     if data unready
 */
static bool ReadRxBuff(void* cthis_ptr,uint8_t* data,size_t* len,size_t max_len)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;
  
  if(cthis->drdy)
  {
    *len = cthis->Rxlen;
    ResetDrdy(cthis);
    return true;
  }
  else return false;
}





/**
 * @brief Realization of @ref HWInterface_t SendData
 * 
 * @param cthis_ptr  pointer to @ref RSxxx
 * @param data      pointer to tx data
 * @param len       sizeof tx data
 * @return true     if packet move to send buffer
 * @return false    if buse or error
 */
static bool SendData(void* cthis_ptr,uint8_t* data,size_t len)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;

  if(cthis->Mode != RSxxx_eRSMode_RS232)
  {
    if(IsFree(cthis))
    {
      #ifdef RS4XX_USE_HW_PIN
      if(cthis->Mode == RSxxx_eRSMode_RS422)
        RS4xxDEnRE_SetTxSPin(&cthis->DEnRE,true);
      if(cthis->Mode == RSxxx_eRSMode_RS485)
        RS4xxDEnRE_SetTxTPins(&cthis->DEnRE);
      #endif
    }
    else
    {
      #ifdef RS4XX_USE_HW_PIN
      if(cthis->Mode == RSxxx_eRSMode_RS485)
      {
        if(!UartInterface_Reset(cthis->hwinter))
          while(1){}; //bug catch
        RS4xxDEnRE_SetTxTPins(&cthis->DEnRE);
      }
      else   
      #endif
        return false;
    }
  }
  else 
    if(!IsFree(cthis))
      return false;

  memcpy(cthis->TxBuffInternal,data,len);

  if(!UartInterface_StartTx(cthis->hwinter,cthis->TxBuffInternal,len))
  { 
    #ifdef RS4XX_USE_HW_PIN
    if(cthis->Mode == RSxxx_eRSMode_RS422)
        RS4xxDEnRE_SetTxSPin(&cthis->DEnRE,false);
    #endif
    return false;
  }
  else 
    return true;
  
}

/**
 * @brief Realization of @ref HWInterface_t IsFree
 * 
 * @param cthis_ptr pointer to @ref RSxxx
 * @return true    if free
 * @return false   buse
 */
static bool IsFree(void* cthis_ptr)
{
  __auto_type cthis = (RSxxx_t*)cthis_ptr;
  if(cthis->Mode!=RSxxx_eRSMode_RS485)
  {
    if(!UartInterface_IsFreeTx(cthis->hwinter))
      return false;
  }
  else
  {
    if(!UartInterface_IsFreeRxTx(cthis->hwinter))
      return false;
  }
  return true;
}

/**
 * @brief Realization of @ref HWInterface_t Process
 * 
 * @param cthis_ptr pointer to @ref RSxxx
 */
static void Process(void* cthis_ptr)
{ 
  #ifndef W_USE_RTOS
    UNUSED(cthis_ptr);
  #else
    _this_os_thread(cthis_ptr);
  #endif
}


/**
 * @brief Reset data ready flag
 * 
 * @param cthis pointer to @ref RSxxx
 */
static void ResetDrdy(RSxxx_t* cthis)
{
  UartInterface_CRITICAL_enter(cthis->hwinter);
    cthis->drdy = false;
  UartInterface_CRITICAL_exit(cthis->hwinter);
}

#ifdef RS4XX_USE_HW_PIN
/**
 * @brief Set RS4xx mode (full/half duplex)
 * @note  This func can't how swap from RS4xx to RS232.
 * @param cthis pointer to @ref RSxxx
 * @param Mode to set @ref RSxxx_eRSMode_t
 */
void MyStRSXXX_SetRS4xxMode(RSxxx_t* cthis, RSxxx_eRSMode_t Mode)
{
  if((( cthis->Mode == Mode)||
    (   cthis->Mode == RSxxx_eRSMode_RS232))||
    (   cthis       == NULL)) return;
  
  cthis->Mode = Mode;

  if(!UartInterface_Reset(cthis->hwinter))
    while(1){}; //bug catch

  RS4xxDEnRE_SetRxTPins(&cthis->DEnRE);
  _this_start_rx(cthis);
}
#endif
/** @}*/




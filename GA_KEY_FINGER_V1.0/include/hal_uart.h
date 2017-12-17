#ifndef __HAL_UART_H
#define __HAL_UART_H

#include "cgu.h"
#include "Hs32u2.h"

#ifdef __cplusplus
 extern "C" {
#endif 

#define HS32U2_UART_EMPCR   (* (volatile unsigned short * )0x00c20010)
//FALE /FCLE pin
#define HS32U2_GPDDRE  (* (volatile unsigned char * )0x00c00013)
#define HS32U2_GPDORE  (* (volatile unsigned char * )0x00c00007)



#ifdef __cplusplus
}
#endif
#endif //__HAL_UART_H

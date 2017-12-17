#ifndef __ECP_H__
#define __ECP_H__


#include "HS_types.h"


#define	ECP_MAX_WLEN	16
#define	ECP_RESULT_X	(((T_U32*)0x00B00200)+32)
#define	ECP_RESULT_Y	(((T_U32*)0x00B00200)+48)

typedef struct __TagECC_CTX
{
	T_U32	*p;
	T_U32	*a;
	T_U32	*b;
	T_U32	*G;
	T_U32	*N;
	T_U32	len;
	
	T_U32	Data[10];
		
	T_U32	*pP;
	T_U32	*pQ;
}ECC_CTX;


T_VOID InvsTU32(const T_U32 d, T_U32 *pdinv);

T_U32 add_immediate(T_U32 a[], const T_U32 iadd, T_U32 b[], T_U32 lng);

T_U32 sub_immediate(const T_U32 a[], const T_U32 isub, T_U32 b[], T_U32 lng);

T_U32 ECC_LoadPara(ECC_CTX *pECC_Ctx, T_U8 *pECCPara, T_U32 *pECCData);

T_U32 ECC_Init(ECC_CTX *pECC_Ctx, T_U32 *pECCData);

T_VOID ECP_SET_MODP(ECC_CTX *pECP_Ctx);

T_VOID ECP_SET_MODN(ECC_CTX *pECP_Ctx);

T_VOID MOD_Add(T_U32 *k, T_U32 *l, T_U32 len, T_U32 *sum);

T_VOID MOD_Sub(T_U32 *k, T_U32 *l, T_U32 len, T_U32 *sub);

T_VOID MOD_Mul(T_U32 *k, T_U32 *l, T_U32 len, T_U32 *mul);

T_VOID MOD_Exp(T_U32 *k, T_U32 klen, T_U32 *l, T_U32 llen, T_U32 *exp);

T_VOID ECP_kP(ECC_CTX *pECP_Ctx, T_U32 *k, T_U32 len);

T_VOID ECP_kP_ADD_lQ(ECC_CTX *pECP_Ctx, T_U32 *k, T_U32 *l, T_U32 len, T_U32 mode);


#endif
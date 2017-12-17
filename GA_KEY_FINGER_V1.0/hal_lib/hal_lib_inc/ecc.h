#ifndef __ECC_H__
#define __ECC_H__


//#include "types.h"
#include "ecp.h"
#include"hash.h"

#define SM1_Init() ((void (*)())(0x0003FC00))()

typedef unsigned int U32;
typedef unsigned char U8;


#define SM2_PRI_LEN 32
#define SM2_PUB_LEN 64

typedef struct sm3_ctxt {
 	HASH_CTX	Ctx;
} SM3_CTX;


U32 ECC_ProduceKeys(ECC_CTX *pECC_Ctx, U32 *pPubkey, U32 *pPrvkey);

U32 ECES_Encrypt (ECC_CTX	*pECC_Ctx,
					U32	*pPubkey, 
					U32	*pPlainData,
					U32	*pCipherData);
						
U32 ECES_Decrypt (ECC_CTX	*pECC_Ctx,
					U32	*pPrikey, 
					U32	*pCipherData, 
					U32	*pPlainData);

U32 ECES_Encrypt_WithTPrivkey (ECC_CTX *pECC_Ctx,					
					U32	*pTempPrivkey,
					U32	*pPubkey, 
					U32	*pPlainData,
					U32	*pCipherData);
					
U32 ECES_Decrypt_WithTPubkey (ECC_CTX	*pECC_Ctx,					
					U32	*pTempPubkey,
					U32	*pPrikey,					
					U32	*pPlainData,
					U32	*pCipherData);
					
U32 ECDSA_Sign (ECC_CTX	*pECC_Ctx, 
				  U32		*pPrikey,
				  U32		*pHash, 				    
				  U32		*pSign);

U32 ECDSA_Verify (ECC_CTX *pECC_Ctx, 
					U32	*pPubkey, 
					U32	*pHash,  
					U32	*pSign);					

void GetZ(ECC_CTX *pECC_Ctx, U32 *pID, U32 IDBLen, U32 *pPubkey, U32 *pResult);

void SM3_Output(U32 *pResult, U32 V[8], U32 Blen);

U32 SM2_Sign (ECC_CTX	*pECC_Ctx, U32 *pPrikey, U32 *pHash, U32 *pSign);

U32 SM2_Verify (ECC_CTX *pECC_Ctx, U32 *pPubkey, U32 *pHash, U32 *pSign);

U32 SM2_Encrypt (ECC_CTX	*pECC_Ctx,
					U32	*pPubkey, 
					U32	*pPlainData,
					U32	PlainDataBLen,
					U32	*pCipherData);
					
U32 SM2_Decrypt (ECC_CTX	*pECC_Ctx,
					U32	*pPrikey, 
					U32	*pCipherData,
					U32	CipherDataBLen,
					U32	*pPlainData);
					
U32 SM2_KeyExchange(ECC_CTX	*pECC_Ctx,
						U32	*pSelfPubkey, 
						U32	*pSelfPrikey,
						U32	*pSelfTempPubkey, 
						U32	*pSelfTempPrikey,
						U32	*pOtherPubkey,
						U32	*pOtherTempPubkey,
						U32	*pSelfID,
						U32	SelfIDLen,
						U32	*pOtherID,
						U32	OtherIDLen,
						U32	*pAgreedKey,
						U32	AgreedKeyLen,
						U32	Mode);						
						
unsigned int CMD_SM3_HASH(void );
unsigned int CMD_Generate_SM2KeyPair(void);
unsigned int CMD_SM2_Decrypt(void);
unsigned int CMD_SM2_Encrypt(void);
unsigned int CMD_SM2_Verify(void);
unsigned int CMD_SM2_Sign(void);
unsigned char CMD_SM1_Encrypt(unsigned char * pInBuf, unsigned int  Inlen,unsigned char * pOutBuf);
unsigned char CMD_SM1_Decrypt(unsigned char * pInBuf, unsigned int  Inlen,unsigned char * pOutBuf);
void MD5_Test(unsigned char *indata, unsigned char inlen, unsigned char *outdata, unsigned char outlen);

#endif



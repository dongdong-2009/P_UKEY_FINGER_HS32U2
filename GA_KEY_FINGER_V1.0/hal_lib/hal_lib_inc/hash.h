#ifndef	__HASH_H__
#define	__HASH_H__
#include "cgu.h"

#define HASH_BLOCK_SIZE		512

#define ALGORITHM_SM3		0
#define ALGORITHM_SHA_1	1
#define ALGORITHM_SHA_224	2
#define ALGORITHM_SHA_256	3

typedef void (*pHashBlock)(U8*, U32*);

typedef struct __tagHASH_CTX
{
	U32	HighBitCount;	//hash长度高位，以bit为单位
	U32	LowBitCount;	//hash长度高位，以bit为单位
	U32	TempBuf [(HASH_BLOCK_SIZE/32)];//缓冲区，保存未满512bit的数据
	U32	ABCDEFGH[8];
// 	U8	HashType;
	pHashBlock  HashBlock;
}HASH_CTX;


/***************************************************************
*
*摘要：本函数实现hash的初始化
*
*参数：
*		pHash_Ctx[IN/OUT]：上下文		
*		Type[IN]：hash类型，0表示SM3(256bit), 1表示SHA1, 2表示SHA224, 3表示SHA256
*
*返回值：0表示成功，-1表示不支持的hash类型
*
*备注：	无
*		
***************************************************************/
U32 Hash_Initialize(HASH_CTX *pHash_Ctx, U32 Type);

/***************************************************************
*
*摘要：本函数追加待hash数据并更新当前hash结果
*
*参数：
*		pHash_Ctx[IN/OUT]：上下文		
*		pData[IN]：待hash的追加数据
*		cBData[IN]：pData的byte长度
*
*返回值：无
*
*备注：	无
*		
***************************************************************/
void Hash_Update(HASH_CTX *pHash_Ctx, U8 *pData, U32 cBData);

/***************************************************************
*
*摘要：本函数结束一个hash过程
*
*参数：
*		pHash_Ctx[IN/OUT]：上下文
*
*返回值：无
*
*备注：	输出结果从pHash_Ctx.ABCDEFGH中取，对于SM3和SHA256，取全部8个字；
*		对于SHA1，取前5个字；对于SHA224，取前7个字
*		
***************************************************************/
void Hash_Finalize(HASH_CTX *pHash_Ctx);


#endif
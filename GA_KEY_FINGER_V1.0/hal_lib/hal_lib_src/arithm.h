#ifndef __ARITHM_H__
#define __ARITHM_H__


#define SM1_128_ECB_ENCRYPT		0x00000000
#define SM1_128_ECB_DECRYPT		0x00000002
#define SM1_192_ECB_ENCRYPT		0x00000008
#define SM1_192_ECB_DECRYPT		0x0000000A
#define SM1_256_ECB_ENCRYPT		0x00000010
#define SM1_256_ECB_DECRYPT		0x00000012
#define SM1_128_CBC_ENCRYPT		0x00000004
#define SM1_128_CBC_DECRYPT		0x00000006
#define SM1_192_CBC_ENCRYPT		0x0000000C
#define SM1_192_CBC_DECRYPT		0x0000000E
#define SM1_256_CBC_ENCRYPT		0x00000014
#define SM1_256_CBC_DECRYPT		0x00000016

#define DES_64_ECB_ENCRYPT		0x00000000	// 64 bit DES
#define DES_64_ECB_DECRYPT		0x00000002	
#define DES_128_ECB_ENCRYPT		0x00000010	// 128 bit TDES
#define DES_128_ECB_DECRYPT		0x00000012
#define DES_192_ECB_ENCRYPT		0x00000018	// 192 bit TDES
#define DES_192_ECB_DECRYPT		0x0000001A
#define DES_64_CBC_ENCRYPT		0x00000004
#define DES_64_CBC_DECRYPT		0x00000006
#define DES_128_CBC_ENCRYPT		0x00000014
#define DES_128_CBC_DECRYPT		0x00000016
#define DES_192_CBC_ENCRYPT		0x0000001C
#define DES_192_CBC_DECRYPT		0x0000001E

#define AES_128_ECB_ENCRYPT		0x00000000
#define AES_128_ECB_DECRYPT		0x00000080
#define AES_192_ECB_ENCRYPT		0x00000010
#define AES_192_ECB_DECRYPT		0x00000090
#define AES_256_ECB_ENCRYPT		0x00000020
#define AES_256_ECB_DECRYPT		0x000000A0
#define AES_128_CBC_ENCRYPT		0x00000040
#define AES_128_CBC_DECRYPT		0x000000C0
#define AES_192_CBC_ENCRYPT		0x00000050
#define AES_192_CBC_DECRYPT		0x000000D0
#define AES_256_CBC_ENCRYPT		0x00000060
#define AES_256_CBC_DECRYPT		0x000000E0

#define SSF33_ECB_ENCRYPT		0x00000000
#define SSF33_ECB_DECRYPT		0x00000002
#define SSF33_CBC_ENCRYPT		0x00000004
#define SSF33_CBC_DECRYPT		0x00000006

#define SHA_1					0x00000000
#define SHA_224					0x00000030
#define SHA_256					0x00000020


/***************************************************************
*
*摘要：本函数配置SM1模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		pKey[in]：密钥，其长度由CSR决定，不能为NULL
*		pIV[in]：IV数据指针，当不需要IV时，无意义，可为NULL
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void SM1_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV);

/***************************************************************
*
*摘要：本函数计算BlockNum块SM1
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在SM1_Setup之后运行
*		4、本函数不能做多于1块的CBC模式的SM1解密
*
***************************************************************/
asm void SM1_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

/***************************************************************
*
*摘要：本函数计算BlockNum块SM1
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在SM1_Setup之后运行
*		4、本函数可用于做多于1块的CBC模式的SM1解密
*
***************************************************************/
asm void SM1_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

/***************************************************************
*
*摘要：本函数配置DES模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		pKey[in]：密钥，其长度由CSR决定，不能为NULL
*		pIV[in]：IV数据指针，当不需要IV时，无意义，可为NULL
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void DES_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV);

/***************************************************************
*
*摘要：本函数计算BlockNum块DES
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在DES_Setup之后运行
*
***************************************************************/
asm void DES_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

/***************************************************************
*
*摘要：本函数配置AES模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		pKey[in]：密钥，其长度由CSR决定，不能为NULL
*		pIV[in]：IV数据指针，当不需要IV时，无意义，可为NULL
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void AES_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV);

/***************************************************************
*
*摘要：本函数计算BlockNum块AES
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在AES_Setup之后运行
*		4、本函数不能做多于1块的CBC模式的SM1解密
*
***************************************************************/
asm void AES_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

asm void AES_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

/***************************************************************
*
*摘要：本函数配置SSF33模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		pKey[in]：密钥，其长度由CSR决定，不能为NULL
*		pIV[in]：IV数据指针，当不需要IV时，无意义，可为NULL
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void SSF33_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV);

/***************************************************************
*
*摘要：本函数计算BlockNum块SSF33
*
*参数：
*		pInData[in]：待运算的数据
*		pOutData[out]：计算结果
*		BlockNum[in]：待运算的块数
*
*返回值：无
*
*备注：	1、本函数没有检测pInData和pOutData所指区域是否有效
*		2、若pInData和pOutData有重合，则必须满足pInData >=  pOutData
*		3、本函数必须在SSF33_Setup之后运行
*		4、本函数不能做多于1块的CBC模式的SM1解密
*
***************************************************************/
asm void SSF33_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

asm void SSF33_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum);

/***************************************************************
*
*摘要：本函数配置SHA模块
*
*参数：
*		CSR[in]：状态寄存器的配置
*		InitData[in]：hash初始值，若为NULL，则使用当前IP寄存器上存留值
*返回值：无
*
*备注：	本函数没有进行参数合法性检测，调用时需要确保参数的合法性
*
***************************************************************/
asm void SHA_Setup(unsigned int CSR, unsigned int *InitData);

/***************************************************************
*
*摘要：本函数计算BlockNum块hash
*
*参数：
*		pMsg[in]：待运算的数据
*		BlockNum[in]：待运算的块数
*		Result[out]：
*
*返回值：无
*
*备注：	1、本函数没有检测pMsg和Result所指区域是否有效
*		2、若pMsg和Result有重合，则必须满足pMsg >=  Result
*		3、本函数必须在SSF33_Setup之后运行
*		4、若Result = NULL，表示不输出当前结果
*		5、SHA_224的输出也为256位，此256位可以作为下次SHA_Setup的初始值，以便从中途计算hash；若要取最终hash结果，则取Result前7个字即可
*
***************************************************************/
asm void SHA_Run(unsigned int *pMsg, unsigned int BlockNum, unsigned int *Result);


void asm SM1_Oper_3_asm(unsigned int *plaintext, unsigned int *crypto, unsigned int data_len, unsigned int data_len_2);


#endif

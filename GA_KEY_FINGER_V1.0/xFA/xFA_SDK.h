// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _xFA_SDK_H_
#define _xFA_SDK_H_

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#define _IN_
#define _OUT_

#define def_maxMeSize               (248)  // 指纹特征值字节数
#define def_template_size           (1024) // 指纹注册模板字节数
#define def_FingerMaxCount          (10) // 最多 10 枚手指

#define def_no_size       (1)  // 存储指纹编号 1 字节
#define def_public_size   (16) // 存储指纹公有信息 16 字节
#define def_private_size  (16) // 存储指纹私有信息 16 字节

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// MOC 算法接口返回码
//

#define def_xFA_OK                  (0x9000) // 执行正确，比对成功，同一个指纹

#define def_xFA_MatchFalse          (0x9001) // 比对成功，不是同一个指纹
#define def_xFA_Func_NotFinished    (0x90FF) // 指定函数功能未完成
#define def_xFA_FPC1080_FingerOn    (0x90F0) // FPC1080 检测到手指
#define def_xFA_FPC1080_Finished    (0x90F1) // FPC1080 滑动采集结束
#define def_xFA_NoFinger_invalid    (0x90E0) // 指定编号的指纹不存在

#define def_xFA_Base_Er             (0x6A80) // 错误码开始
#define def_xFA_Unknown_Er          (def_xFA_Base_Er) // 未知错误
#define def_xFA_Ins_Er              (def_xFA_Base_Er + 0x0001) // 命令字错
#define def_xFA_Ret_Er              (def_xFA_Base_Er + 0x0002) // 返回时检查出错
#define def_xFA_Addr_Er             (def_xFA_Base_Er + 0x0003) // 地址错误
#define def_xFA_DataChk_Er          (def_xFA_Base_Er + 0x0004) // 数据校验错误，即数据不合法，指纹模板 或 指纹特征值 数据错误
#define def_xFA_FlashWrite_Er       (def_xFA_Base_Er + 0x0005) // 数据写入 Flash 错误
#define def_xFA_MOC_Er              (def_xFA_Base_Er + 0x0006) // MOC 返回比对失败错误，特征值数据错误
#define def_xFA_CRC_Er              (def_xFA_Base_Er + 0x0007) // 校验值错误
#define def_xFA_DataInfo_Er         (def_xFA_Base_Er + 0x0008) // 要写入的数据错误
#define def_xFA_FingerData_Er       (def_xFA_Base_Er + 0x0009) // 指纹模板 或 指纹特征值 数据错误

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _typ_xFA_VersionInfo
{
  unsigned int
    version; // 算法版本号
  char
    author[16], // 算法作者
    copyright[16], // 算法版权
    mobile[32], // 算法作者手机号
    email[32], // email
    QQ_WeiXin[48], // QQ 和 微信

    company[32], // 公司名称
    chip[32], // 芯片描述
    sensor[36]; // 支持的 sensor 类型描述
  unsigned short
    sensorType,
    sensorH,
    sensorW,
    sensorDpi;
}typ_xFA_VersionInfo; // 256 字节 <= 4 + 16 + 16 + 32 + 32 + 48 + 32 + 32 + 36 + 8

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// 读取算法版本等信息
//
// 成功返回 1，失败返回 0
//
extern
int xFA_ReadVersionInfo(typ_xFA_VersionInfo *info);

//
// 函数功能：指纹算法初始化，程序启动初始化一次即可
//
extern
void xFA_Init();

//
// 函数功能：检测手指是否按下
//
// 返回 0 表示没有检测到手指
// 返回 1 表示检测到手指
// 返回 -1 表示采集有问题
//
extern
int xFA_FingerDetect();

//
// 函数功能：指纹采集
//
// unsigned int timeout：超时时间参数，毫秒计数（如 8000 表示 8 秒），默认值 8000
//
// 返回 0 表示超时
// 返回 1 表示采集成功
// 返回 -1 表示采集有问题
//
extern
int xFA_GetImage(unsigned int timeout);

//
// 函数功能：指纹特征提取
//
// 参数返回：质量 Q、特征点个数 C、有效面积 V（用于应用层进行各种判断）
//
// 返回 0 表示失败
// 返回 1 表示成功
//
extern
int xFA_ProcessReturnQCV(unsigned char *XFA_Q, unsigned char *XFA_C, unsigned int *XFA_V);

//
// 函数功能：注册模板初始化
//
// 成功返回 1，失败返回 0
//
extern
int xFA_TemplateInit();

//
// 函数功能：将正确提取的指纹特征合并成指纹模板
//
// 在 xFA_ProcessReturnQCV 之后执行！
//
// int countThreshold：表示指纹注册次数，典型值为 3 次
// int sameFinger：表示注册是否必须为同一个手指，0 - 可以为不同手指，1 - 必须为同一个手指
// int *count：返回当前有效个数
//
// 函数返回：
// 0x9000：模板成功生成
// 0x9010：本次操作成功完成，但是模板最终没有完成，需要继续此操作
// 0x9011：没有初始化，请先调用 xFA_TemplateInit() 进行初始化
// 0x9012：表明模板非法 或 特征值非法，注册模板失败
// 0x9013：表明模板内部算法出现逻辑问题，需要调试，注册模板失败
// 0x9014：达到最大次数限制，注册模板失败
// 0x9016：模板初始化错误，可能是定义的模板 Buf 与 实际操作的 Buf 不一致哦！
// 0x9017：带加入的指纹特征校验失败！
// 0x9018：特征值 或 特征模板 中的数据有问题，比对时返回负值
// 0x9019：有问题，需要额外调试 4
// 0x9015：注册模板未知错误
//
extern
unsigned short xFA_AddToTemplate(int countThreshold, int sameFinger, int *count);

//
// 函数功能：检查指定编号的指纹
//
// int No：待检查的指定编号，No 限制为（0 - 9）
//
// 返回 0 表示失败
// 返回 1 表示成功
//
extern
int xFA_CheckAFinger(int No);

//
// 函数功能：检查指纹数据，遇到未存储的指纹区域跳过
//
// 数据正确返回 1,
// 数据错误返回 0
//
extern
int xFA_CheckAllFinger();

//
// 函数功能：读取指定编号的指纹的 No 号，public, private 信息
//
// int No：待读取的指定编号，No 限制为（0 - 9）
// unsigned char info[def_no_size + def_public_size + def_private_size]：读取的信息，No + public + private
//
// 返回 0 表示失败，指定编号的指纹不存在或数据非法
// 返回 1 表示成功
//
extern
int xFA_ReadAFingerInfo(_IN_ int No, _OUT_ unsigned char info[def_no_size + def_public_size + def_private_size]);

//
// 函数功能：读取存储的有效指纹的个数
//
// 返回存储的有效指纹个数，-1 为读取失败
//
extern
int xFA_ReadAllFingerCount();

//
// 函数功能：删除指定编号的指纹
//
// int No：待删除的指定编号，No 限制为（0 - 9）
//
// 返回 0 表示失败
// 返回 1 表示成功
//
extern
int xFA_EraseAFinger(int No);

//
// 函数功能：删除全部指纹
//
// 返回 0 表示失败
// 返回 1 表示成功
//
extern
int xFA_EraseAllFinger();

//
// 函数功能：将指纹信息（public 和 private）连同正确生成的指纹模板写入指定编号
//
// 在成功生成指纹模板后执行！即 xFA_AddToTemplate(...) 返回 0x9000 成功后可将指纹写入需要的编号处
//
// int No：待写入的指定编号，No 限制为（0 - 9）
// unsigned char info[def_no_size + def_public_size + def_private_size]：指纹编号 + public + private 信息
//
// 返回 0 表示失败
// 返回 1 表示成功
//
extern
int xFA_WriteTemplateToAFinger(int No, _IN_ unsigned char info[def_no_size + def_public_size + def_private_size]);

//
// 函数功能：将正确提取的指纹特征与指定编号的指纹进行比对，
//           如果 No 超过界限则全部保存的指纹进行比对
//
// 在 xFA_ProcessReturnQCV(...) 之后执行！
//
// int No：待比对的指定编号，No 限制为（0 - 9），
//         如果 No 超过界限（0 - 9）则与全部保存的指纹进行比对
//         由 No 来控制 MatchA 还是 MatchAll
// int sThreshold：比对相似度门限，典型值为 40，或者 30
//
// 返回 1 比对成功
// 返回 0 比对失败，不是同一个手指
// 返回 -1 为比对函数执行错误，可能为特征值 或 指纹模板数据非法
//
extern
int xFA_MatchFinger(int No, int sThreshold);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#endif // _xFA_SDK_H_

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

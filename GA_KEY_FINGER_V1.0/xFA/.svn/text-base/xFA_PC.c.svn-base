
//
// 信息显示 函数
//
void xMessageNormal(String tStr)
{
}

//
// 消息处理 函数
//
void ProcessMessages()
{
  //
  // 这里添加消息处理函数，以防止程序假死
  //
}

/*
注意：
    1、指纹注册 和 指纹验证模块参考代码见下面
    2、需要将 COS 端的 xFA_SDK.h 中的某些函数通过 USB 通讯在 PC 端封装成同样函数
*/
#include "xFA_SDK.h"

//
// 指纹注册模块
//
void EnrollFinger()
{
  int
    result,
    countThreshold = 3, // 注册需要采集的次数
    sameFinger = 1, // 注册时是否需要同一个手指
    count; // 注册成功采集的次数
  unsigned int
    timeout = 8000, // 采集指纹等待用户时间，默认 8 秒，1000 即为 1 秒
    V;
  unsigned char
    Q, C;
  String
    tStr;

  xMessageNormal("指纹注册中……");

  result = xFA_TemplateInit();
  if (1 != result)
  {
    xMessageNormal("fail - xFA_TemplateInit() !");
    goto gt_close;
  }
  xMessageNormal("ok - xFA_TemplateInit() .");
  count = 0;
  while (1)
  {
    //
    // 这里可以添加消息处理函数，以防止程序假死
    //
    ProcessMessages(); // 防止程序假死

    xMessageNormal(tStr.sprintf("第 %d 次指纹采集中（共 %d 次），请按手指……", count + 1, countThreshold));
    result = xFA_GetImage(timeout);
    if (1 == result)
    {
      xMessageNormal("指纹特征值提取中，请稍候……");

      result = xFA_ProcessReturnQCV(&Q, &C, &V);
      if (1 == result)
      {
        xMessageNormal(tStr.sprintf("ok -- Q = %d, C = %d, V = %d", Q, C, V));
        if (Q < 60 || C < 5 || V < 18000)
        {
          xMessageNormal("质量太差，请重新采集……");
          //
          // 手指检测
          //
          result = xFA_FingerDetect();
          if (1 == result)
          {
            xMessageNormal("请抬起手指……");
            while (1 == xFA_FingerDetect()) // 等待手指抬起来
            {
              ProcessMessages(); // 防止程序假死
            }
            continue;
          }
          else if (0 != result)
          {
            xMessageNormal("fail - xFA_FingerDetect(...)，可能设备有问题 !");
            goto gt_close;
          }
          continue;
        }

        xMessageNormal("模板生成中……");
        result = xFA_AddToTemplate(countThreshold, sameFinger, &count);
        switch (result)
        {
          case 0x9000 : // 0x9000：模板成功生成
          {
            xMessageNormal(tStr.sprintf("ok -- 指纹注册成功 ！[ %d / %d ]，可以进行写入……", count, countThreshold));
            goto gt_close;
          }
          case 0x9010 : // 0x9010：本次操作成功完成，但是模板最终没有完成，需要继续此操作
          {
            xMessageNormal(tStr.sprintf("未完成，请继续……（有效数 %d / 总数 %d）", count, countThreshold));
            //
            // 手指检测
            //
            result = xFA_FingerDetect();
            if (1 == result)
            {
              xMessageNormal("请抬起手指……");
              while (1 == xFA_FingerDetect()) // 等待手指抬起来
              {
                ProcessMessages(); // 防止程序假死
              }
              continue;
            }
            else if (0 != result)
            {
              xMessageNormal("fail - xFA_FingerDetect(...)，可能设备有问题 !");
              goto gt_close;
            }
            continue;
          }
          case 0x9011 : // 0x9011：没有初始化，请先调用 xFA_TemplateInit() 进行初始化
          {
            xMessageNormal("fail -- 请先调用 xFA_TemplateInit() 进行初始化……");
            goto gt_close;
          }
          case 0x9014 : // 0x9014：达到最大次数限制，注册模板失败
          {
            xMessageNormal("fail -- 指纹注册失败！（多次未成功，达到最大次数限制）");
            goto gt_close;
          }
          default :
          {
            // 0x9012：表明模板非法 或 特征值非法，注册模板失败
            // 0x9013：表明模板内部算法出现逻辑问题，需要调试，注册模板失败
            // 0x9016：模板初始化错误，可能是定义的模板 Buf 与 实际操作的 Buf 不一致哦！
            // 0x9017：带加入的指纹特征校验失败！
            // 0x9018：特征值 或 特征模板 中的数据有问题，比对时返回负值
            // 0x9019：有问题，需要额外调试 4
            // 0x9015：注册模板未知错误
            xMessageNormal(tStr.sprintf("fail -- 指纹注册失败！（返回码：0x%04X）", (unsigned short)result));
            goto gt_close;
          }
        }
      }
      else
      {
        xMessageNormal("fail -- xFA_ProcessReturnQCV(...) !");
        goto gt_close;
      }
    }
    else if (0 == result)
    {
      xMessageNormal("time out !");
      goto gt_close;
    }
    else
    {
      xMessageNormal("fail - xFA_GetImage(...)，可能设备有问题 !");
      goto gt_close;
    }
  }

gt_close:
  return;
}

void __fastcall TForm1::Button50Click(TObject *Sender)
{
  String
    tStr;
  int
    result,
    sThreshold = 40; // 比对门限，典型值 40，也可30
  unsigned int
    timeout = 8000;
  unsigned char
    Q, C;
  unsigned int
    V;


  xMessageNormal("指纹识别中……");
  xMessageNormal("请按手指……");
  result = xFA_GetImage(timeout);
  if (1 == result)
  {
    xMessageNormal("指纹特征值提取中，请稍候……");

    result = xFA_ProcessReturnQCV(&Q, &C, &V);
    if (1 == result)
    {
      xMessageNormal(tStr.sprintf("ok -- Q = %d, C = %d, V = %d", Q, C, V));
      xMessageNormal("比对中，请稍候……");
      result = xFA_MatchFinger(0xFF, sThreshold); // 0xFF 这里指与存储的全部指纹进行比对
      if (1 == result)
      {
        xMessageNormal("比对成功！（比对为相同指纹）");
      }
      else if (0 == result)
      {
        if (Q < 60 || C < 5 || V < 18000)
        {
          xMessageNormal("比对失败！（质量太差）");
        }
        else
        {
          xMessageNormal("比对失败！（比对为不同指纹）");
        }
      }
      else
      {
        xMessageNormal("比对函数执行错误 ！");
        goto gt_close;
      }
    }
    else
    {
      xMessageNormal("fail -- xFA_ProcessReturnQCV(...) !");
      goto gt_close;
    }
  }
  else if (0 == result)
  {
    xMessageNormal("time out !");
    goto gt_close;
  }
  else
  {
    xMessageNormal("fail - xFA_GetImage(...)，可能设备有问题 !");
    goto gt_close;
  }

gt_close:
  return;
}

void fingertest()
{
	int result;
	int count,num;
	unsigned int V,timeout=8000;int countThreshold=3;
	
	UART_printf("指纹注册中……");
	num=xFA_ReadAllFingerCount();
UART_printf("指纹数量  %d\r\n",num);

#if 0
  result = xFA_TemplateInit();
  if (1 != result)
  {
    UART_printf("fail - xFA_TemplateInit() !");
    goto gt_close;
  }
  UART_printf("ok - xFA_TemplateInit() .");
  count = 0;
  while (1)
  {
    //
    // 这里可以添加消息处理函数，以防止程序假死
    //
	 UART_printf("START\r\n");
    result = xFA_GetImage(timeout);
    if (1 == result)
    {
      UART_printf("指纹特征值提取中，请稍候……");

      result = xFA_ProcessReturnQCV(G_XFA_Data, G_XFA_Data+1, &V);
      if (1 == result)
      {
        if (G_XFA_Data[0] < 60 || G_XFA_Data[1] < 5 || V < 18000)
        {
          UART_printf("质量太差，请重新采集……");
          //
          // 手指检测
          //
          result = xFA_FingerDetect();
          if (1 == result)
          {
            UART_printf("请抬起手指……");
            while (1 == xFA_FingerDetect()) // 等待手指抬起来
            {
            }
            continue;
          }
          else if (0 != result)
          {
            UART_printf("fail - xFA_FingerDetect(...)，可能设备有问题 !");
            goto gt_close;
          }
          continue;
        }

        UART_printf("模板生成中……");
        result = xFA_AddToTemplate(countThreshold, 1, &count);
        switch (result)
        {
          case 0x9000 : // 0x9000：模板成功生成
          {
            UART_printf("ok -- 指纹注册成功 ，可以进行写入……");
            goto gt_success;
          }
          case 0x9010 : // 0x9010：本次操作成功完成，但是模板最终没有完成，需要继续此操作
          {
            UART_printf("未完成，请继续……（有效数 %d / 总数 %d）", count, countThreshold);
            //
            // 手指检测
            //
            result = xFA_FingerDetect();
            if (1 == result)
            {
              UART_printf("请抬起手指……");
              while (1 == xFA_FingerDetect()) // 等待手指抬起来
              {

              }
              continue;
            }
            else if (0 != result)
            {
              UART_printf("fail - xFA_FingerDetect(...)，可能设备有问题 !");
              goto gt_close;
            }
            continue;
          }
          case 0x9011 : // 0x9011：没有初始化，请先调用 xFA_TemplateInit() 进行初始化
          {
            UART_printf("fail -- 请先调用 xFA_TemplateInit() 进行初始化……");
            goto gt_close;
          }
          case 0x9014 : // 0x9014：达到最大次数限制，注册模板失败
          {
            UART_printf("fail -- 指纹注册失败！（多次未成功，达到最大次数限制）");
            goto gt_close;
          }
          default :
          {
            // 0x9012：表明模板非法 或 特征值非法，注册模板失败
            // 0x9013：表明模板内部算法出现逻辑问题，需要调试，注册模板失败
            // 0x9016：模板初始化错误，可能是定义的模板 Buf 与 实际操作的 Buf 不一致哦！
            // 0x9017：带加入的指纹特征校验失败！
            // 0x9018：特征值 或 特征模板 中的数据有问题，比对时返回负值
            // 0x9019：有问题，需要额外调试 4
            // 0x9015：注册模板未知错误
            UART_printf("fail -- 指纹注册失败！（返回码：0x%04X）", (unsigned short)result);
            goto gt_close;
          }
        }
      }
      else
      {
        UART_printf("fail -- xFA_ProcessReturnQCV(...) !");
        goto gt_close;
      }
    }
    else if (0 == result)
    {
      UART_printf("time out !");
      goto gt_close;
    }
    else
    {
      UART_printf("fail - xFA_GetImage(...)，可能设备有问题 !");
      goto gt_close;
    }
  }
gt_success:
#endif
  if(0)
  {
  	unsigned char buf[33]={0};
	
	
	buf[0]=1;
	if(xFA_WriteTemplateToAFinger(1,buf)==1)	
		 UART_printf("注册成功\r\n");
	else
		 UART_printf("注册失败\r\n");

	num=xFA_ReadAllFingerCount();
	UART_printf("指纹数量  %d\r\n",num);
  }

  num=xFA_ReadAllFingerCount();
	UART_printf("指纹数量  %d\r\n",num);

	if(1)		
	{
		int sThreshold=40;
		result = xFA_GetImage(timeout);
		if (1 == result)
		{
			UART_printf("指纹特征值提取中，请稍候……");
			result = xFA_ProcessReturnQCV(p_G_XFA_Q, p_G_XFA_C, &G_XFA_V);
			if (1 == result)
			{
				UART_printf("比对中，请稍候……");
				 result = xFA_MatchFinger(0xFF, sThreshold); // 0xFF 这里指与存储的全部指纹进行比对
				if (1 == result)
				{
		        		UART_printf("比对成功！（比对为相同指纹）");
		     		}
				else if (0 == result)
			      {
			        	if (*p_G_XFA_Q < 60 || *p_G_XFA_C < 5 || G_XFA_V < 18000)
					{
			          		UART_printf("比对失败！（质量太差）");
			        	}
			        	else
			        	{
			         		UART_printf("比对失败！（比对为不同指纹）");
			        	}
			      }
			
		    }
		    else
		    {
				UART_printf("fail -- xFA_ProcessReturnQCV(...) !");
		    }
		}
		
	}

gt_close:
	 UART_printf("fail -  !");
  return;
}

void sm4_test()
{
	unsigned char test[]={0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8};
	unsigned char iv[16]={0};
	unsigned char key[16]={0x0A,0xDB,0x9B,0x65,0x76,0xDC,0x86,0x66,0x1B,0x33,0x27,0xEB,0xE3,0xF2,0xED,0x7B};

	unsigned char out[16];

	hal_sm4_oper(test,32,key,iv,SYMALG_SENC|SYMALG_CBC,out);
	HAL_UART_SEND_ASC(out,32);
	hal_sm4_oper(test,32,key,iv,SYMALG_SENC|SYMALG_CBC,out);
	HAL_UART_SEND_ASC(out,32);
}

void sm2_test()
{
	unsigned char pub[64],pri[32];

	unsigned char buf[16],out[128]={0};
	unsigned char data[]={0,1,2,3,4,5,6,7,8};

	UART_printf("生产SM2公私钥\r\n");

	hal_sm2_init();
	UART_printf("生产SM2公私钥1\r\n");
	hal_alg_SM2producekeys(pub,pri);

	hal_alg_SM2encrypt(pub,data,8,out);

	hal_alg_SM2decrypt(pri,out,104,buf);
	
	HAL_UART_SEND_ASC(pub,64);
	HAL_UART_SEND_ASC(pri,32);
	HAL_UART_SEND_ASC(out,104);
	HAL_UART_SEND_ASC(buf,16);
}


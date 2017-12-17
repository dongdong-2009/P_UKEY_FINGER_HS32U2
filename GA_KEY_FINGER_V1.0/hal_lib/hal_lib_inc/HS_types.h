#ifndef __HS_TYPES_H__
#define __HS_TYPES_H__


#define HS_API				//API Function's Flag
#define IN					//Parameter's IN Flag
#define OUT					//Parameter's OUT Flag

#define	DEBUG					0

typedef void                    T_VOID;
typedef unsigned char           T_U8;
typedef char                    T_S8;
typedef unsigned short          T_U16;
typedef short                   T_S16;
typedef unsigned int			T_U32;
typedef long                    T_S32;
typedef unsigned int			T_BOOL;
typedef long                    T_RESULT;

#define	HS_FALSE				0
#define	HS_TRUE					1

#define	HS_NULL					0

#define RADIX_BITS		32
#define S16_MIN			(-32768)
#define S16_MAX			32767
#define U16_MAX			0xffff
#define S32_MIN			(-2147483647 - 1)
#define S32_MAX			2147483647
#define U32_MAX			0xffffffff

#define min(a, b)					(((a)<(b))?(a):(b))
#define max(a, b)					(((a)>(b))?(a):(b))

#define ChkDR(expr) {\
            dr = (expr);\
            if ( (T_RESULT)(dr)<0 )\
            {\
                goto ErrorExit;\
            }\
        }
        
#define ChkBOOL(fExpr,err){\
            if (!(fExpr))\
            {\
                dr = (err);\
                goto ErrorExit;\
            }\
        }


#endif

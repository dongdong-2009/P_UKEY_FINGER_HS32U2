#define FAEDINR		0x00b40000
#define FAEKINR  	0x00b40010
#define FAEIVINR	0x00b40020
#define FAEDOUTR	0x00b40030
#define FAECSR		0x00b40040


asm void SSF33_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV)
{
	subi     r0,20
	stm      r12
	
	lrw		r14, FAECSR
	ld.w	r13, (r14,0)
	bseti	r13, 3		//复位
	
	// 等待busy位清为0
_wait_done:
	ld.w	r13, (r14,0)
	btsti	r13, 0
	bt		_wait_done
	
	// 设置CSR
	st.w	r2,(r14,0)
	
	lrw		r14, FAEKINR	
	movi	r13, 4	// 记录128位密钥

	// 设置key	
_set_key:
	ld.w	r12, (r3,0)
	st.w	r12, (r14,0)
	addi	r3, 4
	addi	r14, 4
	decne	r13
	bt		_set_key
	
	// 若需要设置IV，则设置IV
	btsti	r2, 2
	bf		_ECB_mode
	lrw		r14, FAEIVINR
	movi	r13, 4
_CBC_mode:		
	ld.w	r12, (r4,0)
	st.w	r12, (r14,0)
	addi	r4, 4
	addi	r14, 4
	decne	r13
	bt		_CBC_mode
_ECB_mode:
	ldm      r12
	addi     r0,20
	
	jmp		r15
}

// 用汇编调用此函数时要注意，r5-r7被修改
asm void SSF33_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum)
{
	subi     r0,28
	stm      r10
	
//	tst		r4, r4
//	bf		_exit
	
	mov		r12, r4
	lrw		r11, FAECSR			
	lrw		r14, FAEDINR
	lrw		r10, FAEDOUTR
	
_package_loop:	
	//data in:
	ldq		r2
	stq		r14
	
_wait_done:
	ld.w	r13, (r11,0)
	btsti	r13, 0
	bt		_wait_done
	
	//_data out:
	ldq		r10
	stq		r3
	
	addi	r2, 16
	addi	r3, 16
	
	decne	r12
	bt		_package_loop

_exit:	
	ldm     r10
	addi    r0,28
	
	jmp		r15
}

asm void SSF33_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum)
{
	subi    r0,28
	stm     r10
	
//	tst		r4, r4
//	bf		_exit
	
	mov		r12, r4
	lrw		r11, FAECSR			
	lrw		r14, FAEDINR
	lrw		r10, FAEDOUTR
	
	ld.w	r13, (r2, 0)
	st.w	r13, (r14, 0)
	ld.w	r13, (r2, 4)
	st.w	r13, (r14, 4)
	ld.w	r13, (r2, 8)
	st.w	r13, (r14, 8)
	subi	r3, 16
	
_package_loop:
	ld.w	r13, (r2, 12)
	st.w	r13, (r14, 12)	
	addi	r2, 16
	addi	r3, 16
	
	cmpnei	r12, 1
	bf		_wait_done
	
	ld.w	r13, (r2, 0)
	st.w	r13, (r14, 0)
	ld.w	r13, (r2, 4)
	st.w	r13, (r14, 4)
	ld.w	r13, (r2, 8)
	st.w	r13, (r14, 8)
	
_wait_done:
	ld.w	r13, (r11,0)
	btsti	r13, 0
	bt		_wait_done
	
	//_data out:
	ldq		r10
	stq		r3	
	//addi	r3, 16
	
	decne	r12	
	bt		_package_loop
	
_exit:
	ldm     r10
	addi    r0,28
	
	jmp		r15
}

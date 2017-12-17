#define CAEDINR		0x00b30000
#define CAEIVINR	0x00b30010
#define CAEKINR		0x00b30020
#define CAEDOUTR	0x00b30040
#define CAECSR		0x00b30050


asm void SM1_Setup(unsigned int CSR, unsigned int *pKey, unsigned int *pIV)
{
	subi     r0,20
	stm      r12
	
	lrw		r14, CAECSR
	ld.w	r13, (r14,0)
	bseti	r13, 5		//复位
	
	// 清零IV
	lrw		r12, CAEIVINR
	movi	r13, 0
	st.w	r13, (r12,0)
	st.w	r13, (r12,4)
	st.w	r13, (r12,8)
	st.w	r13, (r12,12)
	
	// 清零Key
	lrw		r12, CAEKINR
	st.w	r13, (r12,0)
	st.w	r13, (r12,4)
	st.w	r13, (r12,8)
	st.w	r13, (r12,12)
	st.w	r13, (r12,16)
	st.w	r13, (r12,20)
	st.w	r13, (r12,24)
	st.w	r13, (r12,28)	
	
	// 等待busy位清为0
_wait_done:
	ld.w	r13, (r14,0)
	btsti	r13, 0
	bt		_wait_done
	
	// 设置CSR
	st.w	r2,(r14,0)
	
	lrw		r14, CAEKINR
	
	// 判断key长度
	btsti	r2, 4
	bf		_set_key_len192
	movi	r13, 8	// 记录256位密钥
	bt		_set_key;
_set_key_len192:
	btsti	r2, 3
	bf		_set_key_len128
	movi	r13, 6	// 记录192位密钥
	bt		_set_key;
_set_key_len128:
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
	lrw		r14, CAEIVINR
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
asm void SM1_Run_CBC_Decrypt(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum)
{
	subi    r0,28
	stm     r10
	
	tst		r4, r4
	bf		_exit
	
	mov		r12, r4
	lrw		r11, CAECSR			
	lrw		r14, CAEDINR
	lrw		r10, CAEDOUTR

_wait:
	ld.w	r13, (r11,0)
	btsti	r13, 0
	bt		_wait
	
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

asm void SM1_Run(unsigned int *pInData, unsigned int *pOutData, unsigned int BlockNum)
{
	subi    r0,28
	stm     r10
	
	tst		r4, r4
	bf		_exit
	
	mov		r12, r4
	lrw		r11, CAECSR			
	lrw		r14, CAEDINR
	lrw		r10, CAEDOUTR
	
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

void asm SM1_Oper_3_asm(unsigned int *plaintext, unsigned int *crypto, unsigned int data_len, unsigned int data_len_2)
{	
	
			// 保存现场			
			subi	r0, 30
			subi	r0, 30	
			stm     r1
			
			lsri	r4, 9
			mov		r14, r4
			mov		r15, r5
			
			subi	r15, 1
			
			lrw		r13, 0x00b30000			
			lrw		r12, 0x00b30040
			lrw		r9,  0x00b30050
			
			mov		r10, r2               // r10 = r2 = 输入输出地址
			mov		r11, r15
			
			ldq		r10
			stq		r13
			
			
			mov		r3, r10
			
			addi	r3, 16

	
data_len:		
			
	data_len_2:	
	
			ld.w	r1, (r3, 0)
			st.w	r1, (r13, 0)
			ld.w	r1, (r3, 4)
			st.w	r1, (r13, 4)

			
		busy:	
				ld.w	r8, (r9, 0)
				btsti	r8, 0
		bt		busy
			
			ldq		r12
			stq		r10
			
			ld.w	r1, (r3, 8)
			st.w	r1, (r13, 8)			
			ld.w	r1, (r3, 12)
			st.w	r1, (r13, 12)

			addi	r10, 16
			addi	r3, 16 
			
			decgt 	r11
	bt		data_len_2
			
			
			lrw		r8, 512						
			addu 	r2, r8			
			mov		r3, r2
			
			
			ld.w	r1, (r3, 0)
			st.w	r1, (r13, 0)
			ld.w	r1, (r3, 4)
			st.w	r1, (r13, 4)
			
			
			busy2:	
					ld.w	r8, (r9, 0)
					btsti	r8, 0
			bt		busy2
			
			ldq		r12
			stq		r10
			
			ld.w	r1, (r3, 8)
			st.w	r1, (r13, 8)
			ld.w	r1, (r3, 12)
			st.w	r1, (r13, 12)		

			
			mov		r10, r2		
			
			addi	r3, 16

			mov		r11, r15					
					

			decgt 	r14
bt		data_len
			
		
			
			ldm		r1
			addi	r0, 30
			addi	r0, 30	
			
			jmp		r15
}
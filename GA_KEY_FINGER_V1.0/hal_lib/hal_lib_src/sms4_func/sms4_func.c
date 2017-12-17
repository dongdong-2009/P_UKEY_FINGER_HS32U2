static unsigned char sms4_sbox[]={
0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05,
0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99,
0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62,
0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6,
0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8,
0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35,
0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87,
0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e,
0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1,
0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3,
0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f,
0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51,
0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8,
0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0,
0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84,
0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48
};

unsigned long FK[4]={0xA3B1BAC6,0x56AA3350,0x677D9197,0xB27022DC};

unsigned long CK[32]={
0x00070e15,0x1c232a31,0x383f464d,0x545b6269,
0x70777e85,0x8c939aa1,0xa8afb6bd,0xc4cbd2d9,
0xe0e7eef5,0xfc030a11,0x181f262d,0x343b4249,
0x50575e65,0x6c737a81,0x888f969d,0xa4abb2b9,
0xc0c7ced5,0xdce3eaf1,0xf8ff060d,0x141b2229,
0x30373e45,0x4c535a61,0x686f767d,0x848b9299,
0xa0a7aeb5,0xbcc3cad1,0xd8dfe6ed,0xf4fb0209,
0x10171e25,0x2c333a41,0x484f565d,0x646b7279
};

unsigned long SMS4_K[36];
unsigned long *sms4_ekey, sms4_dkey[32];

unsigned long sms4_tao(unsigned long a)
{
	register unsigned long b;
	
	b=(unsigned long)sms4_sbox[(unsigned char)(a>>24)];
	b<<=8;
	b|=(unsigned long)sms4_sbox[(unsigned char)(a>>16)];
	b<<=8;
	b|=(unsigned long)sms4_sbox[(unsigned char)(a>>8)];
	b<<=8;
	b|=(unsigned long)sms4_sbox[(unsigned char)a];
	return b;
}

unsigned long SMS4_T(unsigned long a)
{
	register unsigned long b, c;
	
	b=(unsigned long)sms4_sbox[(unsigned char)(a>>24)];
	b<<=8;
	b|=(unsigned long)sms4_sbox[(unsigned char)(a>>16)];
	b<<=8;
	b|=(unsigned long)sms4_sbox[(unsigned char)(a>>8)];
	b<<=8;
	c=b|=(unsigned long)sms4_sbox[(unsigned char)a];
	
	c^=((b<<2) | (b>>30));
	c^=((b<<10) | (b>>22));
	c^=((b<<18) | (b>>14));
	c^=((b<<24) | (b>>8));
	
	return c;
}

unsigned long SMS4_F(unsigned long *X, unsigned long rk)
{
	
	return (X[0] ^(SMS4_T(X[1]^X[2]^X[3]^rk)));
}


void sms4_key_expend(unsigned long *MK)
{
	unsigned long i, A,B;
	
	for(i=0;i<4;i++) SMS4_K[i]=MK[i]^FK[i];
	
	for(i=0;i<32;i++)
	{
		A = SMS4_K[i+1] ^ SMS4_K[i+2] ^ SMS4_K[i+3] ^CK[i];
		B = sms4_tao(A);
		SMS4_K[i+4] = SMS4_K[i] ^ (B ^ ((B<<13) | (B>>19)) ^ ((B<<23) | (B>>9)));
		sms4_dkey[31-i] = SMS4_K[i+4];
	}
	
	sms4_ekey = &SMS4_K[4];
}

/*unsigned long X[36];
void sms4_encrypt(unsigned long *plain, unsigned long *key, unsigned long *crypto)
{
	unsigned long i;

	memcpy(X, plain, 16);
	for(i=0;i<32;i++)
	{
		X[i+4] = X[i] ^ (SMS4_T(X[i+1]^X[i+2]^X[i+3]^rk[i]));
	}
	
	crypto[0] = X[35];
	crypto[1] = X[34];
	crypto[2] = X[33];
	crypto[3] = X[32];
}

void sms4_decrypt(unsigned long *crypto, unsigned long *key, unsigned long *plain)
{
	unsigned long i;

	memcpy(X, crypto, 16);
	for(i=0;i<32;i++)
	{
		X[i+4] = X[i] ^ (SMS4_T(X[i+1]^X[i+2]^X[i+3]^rk[31-i]));
	}
	
	plain[0] = X[35];
	plain[1] = X[34];
	plain[2] = X[33];
	plain[3] = X[32];
}*/

/*
buffer:
---------------------------------------------------
|| R4  | R5  | R6  | R7  || R8  | R9  | R10 | R11||
---------------------------------------------------
*/

asm void sms4_run(unsigned long *plain, unsigned long *crypto, unsigned long len, unsigned long mode)
{
	subi    r0,24
	subi    r0,20	
	stm     r6
	
	lrw		r11, sms4_sbox
	tst		r5, r5
	bt		_decrypt
	lrw		r8, sms4_ekey		//point to round_key
	ld.w	r13,(r8,0)
	br		_entry
	
_decrypt:
	lrw		r13, sms4_dkey		//point to round_key in reverse order
			
_entry:
	mov		r1, r4
	
_loop:		
	tst		r1, r1
	bf		_exit
	
	ldq		r2					//load plain(X0 - X3) -> (r4 - r7)
	
	movi	r12,8				//r12 = 8
	mov		r14,r13				//point to round key
	
_round:

	//x[i+4]: R4, input: R4, R5, R6, R7, buffer registers: R8, R9, R10
	
	ld.w	r8, (r14,0)			//round key -> r8
	xor		r8, r7				//round key ^ X(i+3) -> X(i+4)
	xor		r8, r6				//round key ^ X(i+3) ^ X(i+2) -> X(i+4)	
	xor		r8, r5				//round key ^ X(i+3) ^ X(i+2) ^ X(i+1) -> X(i+4)	
	
	mov		r9, r8				//ocupy next 3 empty registers: r9, r10, r11
	lsri	r9, 24
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 24
	mov		r10, r9
	
	mov		r9, r8
	lsri	r9, 16
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 16
	or		r10, r9	
	
	mov		r9, r8
	lsri	r9, 8
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 8
	or		r10, r9		
	
	mov		r9, r8
	zextb	r9
	addu	r9, r11	
	ld.b	r9, (r9,0)
	or		r10, r9	
	
	mov		r8, r10
	rotli	r10, 2
	xor		r8, r10
	rotli	r10, 8	
	xor		r8, r10	
	rotli	r10, 8
	xor		r8, r10
	rotli	r10, 6	
	xor		r8, r10	
	
	xor		r4, r8	
	addi	r14, 4				//point to next round key
			
	//x[i+5] R5, input: R5, R6, R7, R4, buffer registers: R8, R9, R10 
	ld.w	r8, (r14,0)			//round key -> r8
	xor		r8, r4				//round key ^ X(i+3) -> X(i+4)
	xor		r8, r7				//round key ^ X(i+3) ^ X(i+2) -> X(i+4)	
	xor		r8, r6				//round key ^ X(i+3) ^ X(i+2) ^ X(i+1) -> X(i+4)	
	
	mov		r9, r8				//ocupy next 3 empty registers: r9, r10, r11
	lsri	r9, 24
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 24
	mov		r10, r9
	
	mov		r9, r8
	lsri	r9, 16
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 16
	or		r10, r9	
	
	mov		r9, r8
	lsri	r9, 8
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 8
	or		r10, r9		
	
	mov		r9, r8
	zextb	r9
	addu	r9, r11	
	ld.b	r9, (r9,0)
	or		r10, r9	
	
	mov		r8, r10
	rotli	r10, 2
	xor		r8, r10
	rotli	r10, 8	
	xor		r8, r10	
	rotli	r10, 8
	xor		r8, r10
	rotli	r10, 6	
	xor		r8, r10
	
	xor		r5, r8
	addi	r14, 4				//point to next round key

	//x[i+5] R6, input: R6, R7, R4, R5, buffer registers: R8, R9, R10 
	ld.w	r8, (r14,0)		//round key -> r8
	xor		r8, r5				//round key ^ X(i+3) -> X(i+4)
	xor		r8, r4				//round key ^ X(i+3) ^ X(i+2) -> X(i+4)	
	xor		r8, r7				//round key ^ X(i+3) ^ X(i+2) ^ X(i+1) -> X(i+4)	
	
	mov		r9, r8				//ocupy next 3 empty registers: r9, r10, r11
	lsri	r9, 24
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 24
	mov		r10, r9
	
	mov		r9, r8
	lsri	r9, 16
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 16
	or		r10, r9	
	
	mov		r9, r8
	lsri	r9, 8
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 8
	or		r10, r9		
	
	mov		r9, r8
	zextb	r9
	addu	r9, r11	
	ld.b	r9, (r9,0)
	or		r10, r9	
	
	mov		r8, r10
	rotli	r10, 2
	xor		r8, r10
	rotli	r10, 8	
	xor		r8, r10	
	rotli	r10, 8
	xor		r8, r10
	rotli	r10, 6	
	xor		r8, r10
	
	xor		r6, r8	
	addi	r14, 4				//point to next round key
	
	//x[i+7] R7, input: R7, R4, R5, R6, buffer registers: R8, R9, R10
	ld.w	r8, (r14,0)		//round key -> r8
	xor		r8, r6			//round key ^ X(i+3) -> X(i+4)
	xor		r8, r5				//round key ^ X(i+3) ^ X(i+2) -> X(i+4)	
	xor		r8, r4				//round key ^ X(i+3) ^ X(i+2) ^ X(i+1) -> X(i+4)	
	
	mov		r9, r8				//ocupy next 3 empty registers: r9, r10, r11
	lsri	r9, 24
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 24
	mov		r10, r9
	
	mov		r9, r8
	lsri	r9, 16
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 16
	or		r10, r9	
	
	mov		r9, r8
	lsri	r9, 8
	zextb	r9	
	addu	r9, r11	
	ld.b	r9, (r9,0)
	lsli	r9, 8
	or		r10, r9		
	
	mov		r9, r8
	zextb	r9
	addu	r9, r11	
	ld.b	r9, (r9,0)
	or		r10, r9	
	
	mov		r8, r10
	rotli	r10, 2
	xor		r8, r10
	rotli	r10, 8	
	xor		r8, r10	
	rotli	r10, 8
	xor		r8, r10
	rotli	r10, 6	
	xor		r8, r10
	
	xor		r7, r8
	addi	r14, 4				//point to next round key
	
	decne	r12
	bt		_round	
	
	st.w	r7,(r3,0)
	st.w	r6,(r3,4)	
	st.w	r5,(r3,8)
	st.w	r4,(r3,12)	

	addi	r3,16
	addi	r2,16
	subi	r1,16
	br		_loop
	
_exit:
	ldm     r6
	addi    r0,20
	addi    r0,24	
	jmp		r15	
}

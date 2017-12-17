
#define ENCRYPT		0
#define DECRYPT		1

void sms4_key_expend(unsigned long *MK);
void sms4_run(unsigned long *plain, unsigned long *crypto, unsigned long len, unsigned long mode);

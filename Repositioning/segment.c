char g_charA = 'A';			//存储在 .data段
const char g_charB = 'B';	//存储在 .rodata段
const char g_charC;			//存储在 .bss段
int g_intA = 0;				//存储在 .bss段
int g_intB;					//存储在 .bss段

void delay (volatile int time)
{
	while(time--);
}


int main (void)
{	

	return 0;
}

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "syscalls.h"
#include "vmwos.h"

#define MAX_PRINT_SIZE 256

int vsprintf(char *buffer, char *string, va_list ap) {

	char int_buffer[18];
	int int_pointer=0;

	int buffer_pointer=0;
	int i;
	unsigned long x;
	uint64_t lx;
	char pad_value,pad_len,printed_size;

	while(1) {
		if (*string==0) break;

		if (*string=='%') {
			string++;

			pad_len=0;
			pad_value=' ';
			printed_size=0;

			/* Padding */
			if ((*string>='0') && (*string<='9')) {
				if (*string=='0') pad_value='0';
				else pad_value=' ';
				pad_len=*string-'0';
				string++;
				while((*string>='0') && (*string<='9')) {
					pad_len*=10;
					pad_len+=*string-'0';
					string++;
				}
			}

			/* Unsigned integer */
			if ((*string=='d') || (*string=='i')) {
				string++;
				x=va_arg(ap, unsigned long);
				if (x&0x80000000) {
					buffer[buffer_pointer]='-';
					buffer_pointer++;
					printed_size++;
					if (buffer_pointer==MAX_PRINT_SIZE) break;

					x=~x;
					x++;
				}
				int_pointer=9;
				do {
					int_buffer[int_pointer]=(x%10)+'0';
					int_pointer--;
					printed_size++;
					x/=10;
				} while(x!=0);

				if (pad_len>printed_size) {
					for(i=0;i<pad_len-printed_size;i++) {
						buffer[buffer_pointer]=
							pad_value;
						buffer_pointer++;
						if (buffer_pointer
							==MAX_PRINT_SIZE) break;
					}
				}

				for(i=int_pointer+1;i<10;i++) {
					buffer[buffer_pointer]=int_buffer[i];
					buffer_pointer++;
					if (buffer_pointer==MAX_PRINT_SIZE) break;
				}
			}
			/* long long x (FIXME!) */
			else if (*string=='l') {
				string++;
				if (*string!='l'); // FIXME: indicate error
				string++;
				if (*string!='x'); // FIXME: indicate error
				string++;

				lx=va_arg(ap, uint64_t);
				int_pointer=17;
				do {
					if ((lx%16)<10) {
						int_buffer[int_pointer]=
								(lx%16)+'0';
					}
					else {
						int_buffer[int_pointer]=
								(lx%16)-10+'a';
					}
					int_pointer--;
					lx/=16;
				} while(lx!=0);
				for(i=int_pointer+1;i<18;i++) {
					buffer[buffer_pointer]=int_buffer[i];
					buffer_pointer++;
					if (buffer_pointer==MAX_PRINT_SIZE)
						break;
				}
			}
			/* Hex */
			else if ((*string=='x') || (*string=='p')) {
				string++;
				x=va_arg(ap, unsigned long);
				int_pointer=9;
				do {
					if ((x%16)<10) {
						int_buffer[int_pointer]=(x%16)+'0';
					}
					else {
						int_buffer[int_pointer]=(x%16)-10+'a';
					}
					printed_size++;
					int_pointer--;
					x/=16;
				} while(x!=0);

				if (pad_len>printed_size) {
					for(i=0;i<pad_len-printed_size;i++) {
						buffer[buffer_pointer]=
							pad_value;
						buffer_pointer++;
						if (buffer_pointer==
							MAX_PRINT_SIZE) break;
					}
				}

				for(i=int_pointer+1;i<10;i++) {
					buffer[buffer_pointer]=int_buffer[i];
					buffer_pointer++;
					if (buffer_pointer==
							MAX_PRINT_SIZE) break;
				}
			}
			/* char */
			else if (*string=='c') {
				string++;
				x=va_arg(ap, unsigned long);
				buffer[buffer_pointer]=x;
				buffer_pointer++;
				if (buffer_pointer==MAX_PRINT_SIZE) break;
			}
			/* %% */
			else if (*string=='%') {
				string++;
				buffer[buffer_pointer]='%';
				buffer_pointer++;
				if (buffer_pointer==MAX_PRINT_SIZE) break;
			}
			/* string */
			else if (*string=='s') {
				char *s;
				string++;
				s=(char *)va_arg(ap, long);
				while(*s) {
					buffer[buffer_pointer]=*s;
					s++;
					buffer_pointer++;
					if (buffer_pointer==
						MAX_PRINT_SIZE) break;
				}
			}
		}
		else {
			buffer[buffer_pointer]=*string;
			buffer_pointer++;
			if (buffer_pointer==MAX_PRINT_SIZE) break;
			string++;
		}
		if (buffer_pointer==MAX_PRINT_SIZE-1) break;
	}

	return buffer_pointer;
}

int printf(char *string,...) {

	char buffer[MAX_PRINT_SIZE];
	int result;

	va_list argp;
	va_start(argp, string);

	result=vsprintf(buffer,string,argp);

	va_end(argp);

	write(1,buffer,result);

        return result;

}

int sprintf(char *string, char *fmt, ...) {

	int result;

	va_list argp;
	va_start(argp, fmt);

	result=vsprintf(string,fmt,argp);

	va_end(argp);

	/* NUL terminate */
	string[result]='\0';

	return result;

}

#if 0

int main(int argc, char **argv) {

	char *p = (char *)0xdeadbeef;

	printf("Hello World!\n");
	printf("Trying 12345\n");
	printf("\t%d\n",12345);
	printf("\t%i\n",12345);
	printf("Trying -12345\n");
	printf("\t%d\n",-12345);
	printf("\t%i\n",-12345);
	printf("Trying 0xdeadbeef\n");
	printf("\t%x\n",0xdeadbeef);
	printf("\t%p\n",p);
	printf("Trying c 65 (A)\n");
	printf("\t%c\n",65);
	printf("Trying s HELLO WORLD\n");
	printf("\t%s\n","HELLO WORLD");

	printf("Trying %%5x padding, should be *  b0b*\n");
	printf("\t*%5x*\n",0xb0b);

	printf("Trying %%5d padding, should be *  123*\n");
	printf("\t*%5d*\n",123);

	printf("Trying %%05x padding, should be *00b0b*\n");
	printf("\t*%05x*\n",0xb0b);

	printf("Trying %%05d padding, should be *00123*\n");
	printf("\t*%05d*\n",123);

	printf("Trying %%llx, should be 0xdeadbeefcafebabe\n");
	printf("\t%llx\n",0xdeadbeefcafebabeULL);


}
#endif

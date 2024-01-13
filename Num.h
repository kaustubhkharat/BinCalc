#ifndef NUM_H
#define NUM_H 1

typedef struct digit{
	int val;
	struct digit *next,*prev;
}digit;

typedef struct{
	int sign;
	digit *number,*tail;
}num;

void init(num *n, int sign);
void append(num *n, int val);
void appendAtBegin(num *n, int val);
void atoNum(num *n, char *s);
void removeTrailingZeroes(num *n);
int  cmpNum(num *n1, num *n2);
void add(num* n1, num* n2, num *res);
void sub(num* n1, num* n2, num *res);
void MulBy10(num *n, int pow);
void cpyNum(num *n1, num *n2);
void mul(num* n1, num* n2, num *res);
void divide(num* n1, num* n2, num *res);
void delNum(num *n);
void printNum(num n);

#endif

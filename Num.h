#ifndef NUM_H
#define NUM_H 1

typedef struct digit{
	int val;
	struct digit* next;
}digit;

typedef struct{
	int sign;
	digit *number;
}num;

void init(num *n);
void add(num n1, num n2, num *res);
void sub(num n1, num n2, num *res);
void mul(num n1, num n2, num *res);
void div(num n1, num n2, num *res);

#endif

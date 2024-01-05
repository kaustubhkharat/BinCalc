#include <stdlib.h>
#include "Num.h"

#define SIGN(x) (x<0)?-1:1
/**
*typedef struct digit{
*	int val;
*	struct digit* next;
*}digit;
*
*typedef struct{
*	int sign;
*	digit *number;
*}num;
**/

void init(num *n, int sign){
	n->sign=SIGN(sign);
	n->number=NULL;
	return;
}

void append(num *n, int val){
	digit *p,*nn;
	nn=(digit*)malloc(sizeof(digit));
	nn->val=val;
	nn->next=NULL;
	p=n->number;
	if (p==NULL){
		n->number=nn;
		return;
	}
	while (p->next) p=p->next;
	p->next=nn;
	return;
}

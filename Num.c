#include <stdlib.h>
#include <stdio.h>
#include "Num.h"

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
	n->sign=sign;
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

void add(num* n1, num* n2, num *res){
	if (n1->sign==-1&&n2->sign==1){
		n1->sign=1;
		sub(n2, n1, res);
		return;
	}
	if (n1->sign==1&&n2->sign==-1){
		n2->sign=1;
		sub(n1, n2, res);
		return;
	}
	int sum, carry=0;
	res->sign=n1->sign;
	digit *p,*q;
	
	p=n1->number;
	q=n2->number;

	while (p&&q){
		sum = p->val+q->val+carry;
		carry = sum/10;
		sum %= 10;
		append(res, sum);
		p=p->next;
		q=q->next;
	}
	while (p){
		sum=p->val+carry;
		carry = sum/10;
		sum %= 10;
		append(res, sum);
		p=p->next;
	}
	while (q){
		sum=q->val+carry;
		carry=sum/10;
		sum %= 10;
		append(res, sum);
		q=q->next;
	}
	if (carry) append (res, carry);
	return;
}

void sub(num* n1, num* n2, num *res){
	if (n1->sign==1&&n2->sign==-1){
		n2->sign=1;
		add(n1, n2, res);
		return;
	}
	if (n1->sign==-1&&n2->sign==1){
		n2->sign=-1;
		add(n1, n2, res);
		return;
	}
	int diff, borrow=0;
	digit *p,*q;
	p=n1->number;
	q=n2->number;
	while (p&&q){
		diff = p->val-q->val-borrow;
		if (diff < 0){
			borrow = 1;
			diff += 10;
		}else{
			borrow = 0;
		}
		append(res, diff);
		p=p->next;
		q=q->next;
	}
	if (p){
		res->sign = n1->sign;
	}
	if (q){
		res->sign = -1*n2->sign;
	}
	while (p){
		diff = p->val-borrow;
		if (diff < 0){
			borrow = 1;
			diff += 10;
		}else{
			borrow = 0;
		}
		append(res, diff);
		p=p->next;
	}
	while (q){
		diff = q->val+borrow;
		borrow=diff/10;
		diff %= 10;
		append(res, diff);
		q=q->next;
	}
	if (borrow){
		append(res, borrow);
	}
	return;
}

void mul(num n1, num n2, num *res){
	return;
}

void divide(num n1, num n2, num *res){
	return;
}

void delNum(num *n){
	digit *p,*q;
	p=n->number;

	while (p->next){
		q=p->next;
		free(p);
		p=q;
	}

	free(p);
	return;
}

void printNum(num n){
	digit *p;
	int i=0, arr[100];
	
	p=n.number;

	while (p){
		arr[i++] = p->val;
		p=p->next;
	}
	if (n.sign==-1) printf("-"); 
	for (;i>=0;i--){
		printf("%d",arr[i]);
	}
	printf("\n");
	return;
}

int main(){
	num n1, n2,res;
	init(&n1, 1);
	init(&n2, 1);
	init(&res, 1);
	// n1 = 21 n2 = 321
	append(&n1, 1);
	append(&n1, 2);
	append(&n2, 1);
	append(&n2, 2);
	append(&n2, 3);

	printNum(n1);
	printNum(n2);
	sub(&n1, &n2, &res);
	printNum(res);

	delNum(&n1);
	delNum(&n2);
	delNum(&res);

	return 0;
}

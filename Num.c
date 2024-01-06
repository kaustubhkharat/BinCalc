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
		diff = q->val-borrow;
		if (diff < 0){
			borrow = 1;
			diff += 10;
		}else{
			borrow = 0;
		}
		append(res, diff);
		q=q->next;
	}
	if (borrow){
		append(res, borrow);
	}
	return;
}

void MulBy10(num *n, int pow){
	int i;
	digit *nn;
	for (i=0;i<pow;i++){
		nn=(digit*)malloc(sizeof(digit));
		nn->val=0;
		nn->next=n->number;
		n->number=nn;
	}
	return;
}

void cpyNum(num *n1, num *n2){
	digit *p;
	p=n2->number;
	while (p){
		append(n1, p->val);
		p=p->next;
	}
	return;
}

void mul(num *n1, num *n2, num *res){
	digit *p,*q,*r;
	int mulres, carry=0, i=0, k=0;
	num rowC, rowP, rowRes;
	init(&rowC, 1);
	init(&rowP, 1);
	init(&rowRes, 1);
	res->sign = n1->sign * n2->sign;
	p=n1->number;
	q=n2->number;
	
	while (q){		
		delNum(&rowRes);
		init(&rowRes);
		while(p){
			mulres = p->val * q->val + carry;
			carry = mulres/10;
			mulres %= 10;

			append(&rowC, mulres);
			p=p->next;
		}
		MulBy10(&rowC, k);
		k++;
		add(rowC, rowP, rowRes);
		delNum(&rowP);
		init(&rowP, 1);
		cpyNum(&rowP, &rowRes);
		delNum(&rowC);
		init(&rowC, 1);
		q=q->next;
	}
	numCpy(&rowRes, res);
	delNum(&rowRes);
	init(&rowRes, 1);
	return;
}

void divide(num* n1, num* n2, num *res){
	num q,add1,divres,temp,temp2;
	init(&q, 1);
	init(&temp, 1);
	init(&temp2, 1);
	init(&add1, 1);
	init(&divres, 1);
	append(&add1, 1);
	append(&q, 1);

	res->sign = n1->sign*n2->sign;
	if (res->sign < 0){
		if (n1->sign < 0){
			n1->sign = 1;
		}
		if (n2->sign < 0){
			n2->sign = 1;
		}
	}

	mul(n2, &q, &divres);
	sub(n1, &divres, &temp);
	while (temp.sign > 0){
		delNum(&temp);
		init(&temp, 1);
		delNum(&divres);
		init(&divres, 1);
		mul(n2, &q, &divres);
		sub(n1, &divres, &temp);
		add(&q, &add1, &temp2);
		numCpy(&q, &temp2);
		delNum(&temp2);
		init(&temp2, 1);
	}
	numCpy(&q, res);
	delNum(&q);
	init(&q);
	return;
}
void delNum(num *n){
	digit *p,*q;
	p=n->number;

	if (p==NULL) return;
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
	i--;
	for (;i>=0;i--){
		printf("%d",arr[i]);
	}
	printf("\n");
	return;
}

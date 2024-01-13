#include <stdlib.h>
#include <stdio.h>
#include "Num.h"

/*
typedef struct digit{
	int val;
	struct digit *next,*prev;
}digit;

typedef struct{
	int sign;
	digit *number,*tail;
}num;
*/

void init(num *n, int sign){
	n->sign=sign;
	n->number=NULL;
	n->tail=NULL;
	return;
}

void atoNum(num *n, char *s){
	int i=0;
	if (s[0]=='-'){
		n->sign = -1;
		i=1;
	}
	while (s[i]!='\0'){
		appendAtBegin(n, s[i]-'0');
		i++;
	}

	return;
}

void removeTrailingZeroes(num *n){
	digit *p,*q;
	p=n->tail;

	while (p&&(p->val==0)){
		q=p->prev;
		free(p);
		p=q;
	}
	n->tail=p;
	p->next=NULL;
	return;
}

void append(num *n, int val){
	digit *p,*nn;
	nn=(digit*)malloc(sizeof(digit));
	nn->val=val;
	nn->next=NULL;
	p=n->tail;
	if (p==NULL){
		nn->next=NULL;
		nn->prev=NULL;
		n->number=nn;
		n->tail=nn;
		return;
	}
	p->next=nn;
	nn->prev=p;
	nn->next=NULL;
	n->tail=nn;
	return;
}

void appendAtBegin(num* n, int val){
	digit *p,*nn;
	nn=(digit*)malloc(sizeof(digit));
	nn->val=val;
	p=n->number;
	if (p==NULL){
		nn->next=NULL;
		nn->prev=NULL;
		n->number=nn;
		n->tail=nn;
		return;
	}
	p->prev=nn;
	nn->next=p;
	n->number=nn;
	nn->prev=NULL;
	return;
}

int cmpNum(num *n1, num *n2){
	int c1=0,c2=0;
	digit *p,*q;

	if (n1&&n2==NULL) return 1;
	if (n1==NULL&&n2) return -1;
	
	p=n1->number;
	q=n2->number;
	
	if (n1->sign==1&&n2->sign==-1) return 1;
	if (n1->sign==-1&&n2->sign==1) return -1;

	while (p){
		c1++;
		p=p->next;
	}

	while (q){
		c2++;
		q=q->next;
	}

	if (c1 > c2){
		return n1->sign;
	}
	if (c1 < c2){
		return -1*n1->sign;
	}
	if (c1 == c2){
		p=n1->tail;
		q=n2->tail;

		while (p&&q&&(p->val==q->val)){
			p=p->prev;
			q=q->prev;
		}

		if(p==NULL) return 0;

		if (p->val > q->val){
			return n1->sign;
		}
		if (p->val < q->val){
			return -1*n1->sign;
		}
	}
	return 0;
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

	if (cmpNum(n1, n2) == -1){
		p=n2->number;
		q=n1->number;
		res->sign = -1;
	}
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
	if (pow==0) return;
	for (i=0;i<pow;i++){
		appendAtBegin(n, 0);
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
	digit *p,*q;
	int mulres, carry=0, k=0;
	num rowC, rowP, rowRes;
	init(&rowC, 1);
	init(&rowP, 1);
	init(&rowRes, 1);
	res->sign = n1->sign * n2->sign;
	p=n1->number;
	q=n2->number;
	while (q){		
		delNum(&rowRes);
		init(&rowRes, 1);
		while(p){
			mulres = (p->val * q->val) + carry;
			carry = mulres/10;
			mulres %= 10;
			append(&rowC, mulres);
			p=p->next;
		}
		if (carry) append(&rowC, carry);
		MulBy10(&rowC, k++);
		add(&rowC, &rowP, &rowRes);
		delNum(&rowP);
		init(&rowP, 1);
		cpyNum(&rowP, &rowRes);
		delNum(&rowC);
		init(&rowC, 1);
		p=n1->number;
		q=q->next;
		carry=0;
	}
	cpyNum(res, &rowRes);
	delNum(&rowRes);
	init(&rowRes, 1);
	return;
}

num* singleDiv(num *n1, num *n2){
	num *i,t;
	i=(num*)malloc(sizeof(num));
	init(i, 1);
	init(&t, 1);
	removeTrailingZeroes(n1);
	removeTrailingZeroes(n2);
	append(i, 1);
	mul(n2, i, &t);
	while (cmpNum(n1, &t) > 0){
		i->number->val+=1;
		delNum(&t);
		init(&t, 1);
		mul(n2, i, &t);
	}
	delNum(&t);
	init(&t, 1);
	i->number->val -= 1;
	return i;
}

void divide(num* n1, num* n2, num *res){
	digit *q;
	num *r,*row,*temp,*temp2;
	r=(num*)malloc(sizeof(num));
	row=(num*)malloc(sizeof(num));
	temp2=(num*)malloc(sizeof(num));
	init(temp2, 1);
	init(row, 1);
	init(r, 1);
	res->sign=n1->sign*n2->sign;
	n1->sign=1;
	n2->sign=1;
	q=n1->tail;
	while (q&&cmpNum(r, n2)==-1){
		appendAtBegin(r, q->val);
		q=q->prev;
	}
	if (q==NULL){
		append(res, 0);
		return;
	}
	if (q==NULL && cmpNum(n1, n2) == 1){
		free(r);
		r=singleDiv(n1, n2);
		append(res, r->number->val);
	}
	while (q){
		temp=singleDiv(r,n2);
		appendAtBegin(res, temp->number->val);
		mul(n2, temp, temp2);
		sub(r, temp2, row);
		appendAtBegin(row, q->val);
		q=q->prev;
		delNum(temp2);
		delNum(temp);
		delNum(r);
		init(temp2, 1);
		init(temp, 1);
		init(r, 1);
		cpyNum(r, row);
		delNum(row);
		init(row, 1);
		delNum(temp);
		free(temp);
	}
	temp=singleDiv(r, n2);
	appendAtBegin(res, temp->number->val);
	delNum(r);
	delNum(row);
	delNum(temp2);
	free(r);
	free(row);
	free(temp2);
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

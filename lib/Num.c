#include <stdlib.h>
#include <stdio.h>
#include "Num.h"

/*
typedef struct digit{
	int val;
	struct digit *next,*prev;
}digit;

typedef struct{
	int sign,len;
	digit *number,*tail;
}num;
*/

void init(num *n, int sign){
	n->sign=sign;
	n->len=0;
	n->number=NULL;
	n->tail=NULL;
	return;
}

void atoNum(num *n, char *s){
	int i=0;
	n->sign=1;
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
		n->len--;
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
	n->len++;
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
	n->len++;
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

int cmpNum(num *n1, num *n2){ //n1-n2 sign
	digit *p,*q;

	if (n1&&n2==NULL) return 1;
	if (n1==NULL&&n2) return -1;
	printf("n1 length: %d n1:",n1->len);
	printNum(*n1);
	printf("n2 length:%d n2:",n2->len);
	printNum(*n2);
	if (n1->sign==1&&n2->sign==-1) return 1;
	if (n1->sign==-1&&n2->sign==1) return -1;
	
	if (n1->len > n2->len) return 1;
	if (n1->len < n2->len) return -1;

	p=n1->tail;
	q=n2->tail;

	while (p){
		if (p->val > q->val){
			return n1->sign;
		}
		if (p->val < q->val){
			return -1*n1->sign;
		}
		p=p->prev;
		q=q->prev;
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
	int diff, borrow=0,tmp;
	digit *p,*q;
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
	tmp=cmpNum(n1, n2);
	printf("value of compare: %d\n",tmp);
	if (tmp == -1){
		p=n2->number;
		q=n1->number;
		res->sign = -1;
	}else{
		p=n1->number;
		q=n2->number;
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
	removeTrailingZeroes(res);
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
	p=n.tail;
	if (n.sign==-1) printf("-");
	while (p){
		printf("%d",p->val);
		p=p->prev;
	}
	printf("\n");
	return;
}

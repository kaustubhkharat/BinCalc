#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Num.h"
#include "stack.h"

int isNum(char *s){
	int l;
	l=strlen(s);
	if (isdigit(s[0])) return 1;
	if ((l>1)&&(s[0]=='-')&&(isdigit(s[1]))) return -1;
	return 0;
}

num* eval(char *postfix[], int l){
	num *n1, *n2, *nres;
	int i=0;
	stack s;
	init_stack(&s);
	while (i<l){
		if (isNum(postfix[i])){
			n1=(num*)malloc(sizeof(num));
			atoNum(n1, postfix[i]);
			push(&s, (void*) n1);
		}
		if (strcmp(postfix[i], "+")==0){
			n1 = (num*) pop(&s);
			n2 = (num*) pop(&s);
			nres=(num*)malloc(sizeof(num));
			init(nres, 1);
			add(n1, n2, nres);
			push(&s, (void*) nres);
			delNum(n1);
			delNum(n2);
		}

		if (strcmp(postfix[i], "-")==0){
			n1 = (num*) pop(&s);
			n2 = (num*) pop(&s);
			nres=(num*)malloc(sizeof(num));
			init(nres, 1);
			sub(n1, n2, nres);
			push(&s, (void*) nres);
			delNum(n1);
			delNum(n2);
		}

		if (strcmp(postfix[i], "*")==0){
			n1 = (num*) pop(&s);
			n2 = (num*) pop(&s);
			nres=(num*)malloc(sizeof(num));
			init(nres, 1);
			mul(n1, n2, nres);
			push(&s, (void*) nres);
			delNum(n1);
			delNum(n2);
		}

		if (strcmp(postfix[i], "/")==0){
			n1 = (num*) pop(&s);
			n2 = (num*) pop(&s);
			nres=(num*)malloc(sizeof(num));
			init(nres, 1);
			divide(n1, n2, nres);
			push(&s, (void*) nres);
			delNum(n1);
			delNum(n2);
		}
		i++;
	}
	nres = (num*) pop(&s);
	return nres;
}

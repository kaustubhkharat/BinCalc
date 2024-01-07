#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Num.h"
#include "stack.h"

int isOp(char s){
	switch (s){
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
		default:
			return 0;
	}
	return 0;
}

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

int precedence(char s){
	switch (s){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return 0;
	}
	return 0;
}

int infixToPostfix(char *infix, char *postfix[]){
	int i=0,j=0,k=0;
	char *op;
	stack s;
	init_stack(&s);

	while (infix[i]){
		if (isdigit(infix[i])||((infix[i]=='-') && isdigit(infix[i+1]))){
			if (infix[i]=='-'){
				postfix[j][k]=infix[i];
				i++;
				k++;
			}
			while (isdigit(infix[i])){
					postfix[j][k] = infix[i];
					i++;
					k++;
			}
			j++;
			k=0;
		}
		if (isOp(index[i])){
				


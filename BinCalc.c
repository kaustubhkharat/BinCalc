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

int isNum(char s[]){
	int l;
	l=strlen(s);
	if (isdigit(s[0])) return 1;
	if ((l>1)&&(s[0]=='-')&&(isdigit(s[1]))) return -1;
	return 0;
}

void eval(char *postfix[], int l, num *res){
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
			sub(n2, n1, nres);
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
			divide(n2, n1, nres);
			push(&s, (void*) nres);
			delNum(n1);
			delNum(n2);
		}
		i++;
	}
	nres = (num*) pop(&s);
	cpyNum(res, nres);
	delNum(nres);
	return;
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

int infixToPostfix(char infix[], char *postfix[]){
	int flag=1,i=0,j=0,k=0;
	char *op1, *op2;
	stack s;
	init_stack(&s);

	while (infix[i]){
		if (infix[i]==' ') i++;
		if (isdigit(infix[i])){
			op1 = (char *)malloc(100*sizeof(char));
			while (isdigit(infix[i])){
				op1[k++]=infix[i++];
			}
			op1[k]=0;
			postfix[j++]=op1;
			k=0;
			flag=0;
		}
		if ((flag==1) && (infix[i]=='-')){
			op1=(char*)malloc(100*sizeof(char));
			op1[0]='-';
			i++;
			k++;
			while (isdigit(infix[i])){
				op1[k++]=infix[i++];
			}
			op1[k]=0;
			postfix[j++]=op1;
			k=0;
			flag=0;
		}
		if (infix[i]=='('){
			op1=(char*)malloc(2*sizeof(char));
			strcpy(op1, "(");
			push(&s, (void*)op1);
		}
		if (infix[i]==')'){
			op1=(char*)pop(&s);
			while (op1&&strcmp(op1, "(")){
				postfix[j++]=op1;
				op1 = (char*) pop(&s);
			}
		}
		if ((flag==0)&&isOp(infix[i])){
			op2 = (char*) pop(&s);
			while (op2&&(precedence(op2[0]) >= precedence(infix[i]))){
				postfix[j++]=op2;
				op2=(char*)pop(&s);
			}
			if (op2&&(precedence(op2[0])<precedence(infix[i]))){
				push(&s, (void*) op2);
			}
			flag=1;
			op1=(char*)malloc(2*sizeof(char));
			if (infix[i]=='+') strcpy(op1, "+");
			if (infix[i]=='-') strcpy(op1, "-");
			if (infix[i]=='*') strcpy(op1, "*");
			if (infix[i]=='/') strcpy(op1, "/");
			push(&s, (void*) op1);
		}
		i++;
	}

	op2=(char*)pop(&s);

	while (op2){
		postfix[j++]=op2;
		op2=(char*)pop(&s);
	}
	return j;
}

int main(){
	char *postfix[1000],infix[1000];
	int l,i;
	num *r;
	r=(num*)malloc(sizeof(num));
	init(r, 1);
	printf("enter \"quit\" to terminate the program\n");
	scanf("%s",infix);
	while (strcmp(infix, "quit")){
		l=infixToPostfix(infix,postfix);
		eval(postfix,l,r);
		printNum(*r);
		delNum(r);
		free(r);
		for (i=0;i<l;i++) free(postfix[i]);
		scanf("%s",infix);
	}
	return 0;
}

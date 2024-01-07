#include <stdlib.h>
#include "stack.h"

/*
typedef struct Node{
	void *val;
	struct Node *next;
}Node;

typedef Node *stack;
*/

void init_stack(stack *s){
	*s=NULL;
	return;
}

void push(stack *s, void *val){
	Node *nn;
	nn=(Node*)malloc(sizeof(Node));
	nn->val=val;
	nn->next=*s;
	*s=nn;
	return;
}

void *pop(stack *s){
	if (*s==NULL) return NULL;
	void *val;
	Node *p;

	p=*s;
	val=p->val;
	*s=p->next;
	free(p);
	return val;
}

void *peek(stack *s){
	if (*s==NULL) return NULL;
	Node *p;
	p=*s;
	return p->val;
}

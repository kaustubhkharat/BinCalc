#ifndef STACK_H
#define STACK_H 1

typedef struct Node{
	void *val;
	struct Node *next;
}Node;

typedef Node *stack;

void init_stack(stack *s);
void push(stack *s, void *val);
void *pop(stack *s);
void *peek(stack *s);

#endif

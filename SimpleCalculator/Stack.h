#ifndef _STACK_H_
#define _STACK_H_

#include "Expression.h"

typedef ItemData Data;

typedef struct _Stack
{
	int top;
	int size;

	Data datas[MAX_EXP_LEN];

} Stack;

void Init(Stack* stack);
void Push(Stack* stack, Data newItem);
Data Pop(Stack* stack);

#endif


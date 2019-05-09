#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"


void Init(Stack* stack)
{
	stack->top = -1;
	stack->size = 0;
}

void Push(Stack* stack, Data newItem)
{
	if (stack->top+1 >= MAX_EXP_LEN)
	{
		printf("ERROR!! - Can't Push Anymore");
		exit(1);
	}

	stack->size++;
	stack->top++;
	stack->datas[stack->top] = newItem;
}

Data Pop(Stack* stack)
{
	Data toReturn;

	if (stack->top <= -1)
	{
		printf("ERROR!! - Can't Pop Anymore");
		exit(1);
	}
	
	toReturn = stack->datas[stack->top];
	stack->top--;
	stack->size--;

	return toReturn;
}

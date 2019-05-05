#include <stdio.h>
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
		//TODO : ���������� ���α׷� ���� �Լ��� �ٲ���ֱ�
		printf("ERROR!!");
		return;
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
		//TODO : ���������� ���α׷� ���� �Լ��� �ٲ���ֱ�
		printf("ERROR!!");
		exit(0);
	}
	
	toReturn = stack->datas[stack->top];
	stack->top--;
	stack->size--;

	return toReturn;
}

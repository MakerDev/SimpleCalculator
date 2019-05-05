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
		//TODO : 리눅스에서 프로그램 종료 함수로 바꿔써주기
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
		//TODO : 리눅스에서 프로그램 종료 함수로 바꿔써주기
		printf("ERROR!!");
		exit(0);
	}
	
	toReturn = stack->datas[stack->top];
	stack->top--;
	stack->size--;

	return toReturn;
}

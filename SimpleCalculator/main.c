#include <stdio.h>

#include "Stack.h"
#include "Calculator.h"
#include "Expression.h"
#include "calc_token.h"


int GetStatement(Item* infixexpression);


int main()
{
	int isEOF = 0;
	int number = 0;

	Item infixExpression[MAX_EXP_LEN];
	Item postfixExpression[MAX_EXP_LEN];

	/*
	-를 지원하는 방법 :
	숫자뒤에 온 -는 무조건 연산자 -다.
	그런데 연산자( '(' 포함) 뒤에 온 -는 부호를 결정하는 -다. 그런데 ')'다음의 -는 연산자임
	따라서 -가 연산자뒤에 올때마다 부호 변수에 -1을 곱해주고 다음 Number
	*/

	while (1)
	{
		if (isEOF = GetStatement(infixExpression))
		{
			break;
		}



		ConvertInfixToPostfix(infixExpression, postfixExpression);
		PrintExpression(postfixExpression);
		printf("Result : %d\n", CalculatePostfix(postfixExpression));
	}


	return 0;
}



int GetStatement(Item* infixexpression)
{
	int i = 0;

	while (1)
	{
		if (i >= MAX_EXP_LEN)
		{
			//TODO : 프로그램 종료해버리기
			puts("Too Long Statement");
			return -1;
		}
		
		
		infixexpression[i].token = GetToken(&(infixexpression[i].value));


		if (infixexpression[i].token == EOFILE)
		{
			return 1;

		}
		else if (infixexpression[i].token == END)
		{
			return 0;
		}

		i++;
	}
}

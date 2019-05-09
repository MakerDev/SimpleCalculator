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
	-�� �����ϴ� ��� :
	���ڵڿ� �� -�� ������ ������ -��.
	�׷��� ������( '(' ����) �ڿ� �� -�� ��ȣ�� �����ϴ� -��. �׷��� ')'������ -�� ��������
	���� -�� �����ڵڿ� �ö����� ��ȣ ������ -1�� �����ְ� ���� Number
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
			//TODO : ���α׷� �����ع�����
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

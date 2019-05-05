#include <stdio.h>

#include "Stack.h"
#include "Calculator.h"
#include "Expression.h"
#include "calc_token.h"



int main()
{
	int isDone = 0;
	int number = 0;
	
	Item infixExpression[MAX_EXP_LEN];

	int i = 0;

	/*
	-�� �����ϴ� ��� :
	���ڵڿ� �� -�� ������ ������ -��.
	�׷��� ������( '(' ����) �ڿ� �� -�� ��ȣ�� �����ϴ� -��. �׷��� ')'������ -�� ��������
	���� -�� �����ڵڿ� �ö����� ��ȣ ������ -1�� �����ְ� ���� Number
	*/

	int wasLastTokenNumberOrRParen = 0;
	int sign = 1;
	
	while (!isDone)
	{
		if (i >= MAX_EXP_LEN)
		{
			return 0;
		}

		switch (GetToken(&number))
		{
		case NUMBER:
			infixExpression[i].type = Number;
			infixExpression[i].data.number = number*sign;
			wasLastTokenNumberOrRParen = 1;
			sign = 1;
			break;

		case PLUS:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '+';
			wasLastTokenNumberOrRParen = 0;

			break;

		case MINUS:
			if (!wasLastTokenNumberOrRParen)
			{
				sign *= -1;
				i--;	//infixExpression�� �߰��Ǵ°� �����Ƿ�
				break;
			}

			infixExpression[i].type = Op;
			infixExpression[i].data.op = '-';
			wasLastTokenNumberOrRParen = 0;

			break;

		case DIVIDE:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '/';
			wasLastTokenNumberOrRParen = 0;

			break;

		case TIMES:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '*';
			wasLastTokenNumberOrRParen = 0;

			break;

		case LPAREN:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '(';
			wasLastTokenNumberOrRParen = 0;

			break;

		case RPAREN:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = ')';
			wasLastTokenNumberOrRParen = 1;

			break;

		case END:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '\0';
			i = -1;

			int result = CalculateInfixExpression(infixExpression);
			printf(" ��� : %d\n", result);

			break;

		case EOFILE:
			isDone = 1;
			break;

		default:
			break;
		}

		i++;
	}

	return 0;
}

#include <stdio.h>

#include "Stack.h"
#include "Calculator.h"
#include "Expression.h"
#include "calc_token.h"


void GetStatement(Item* infixexpression);


int main()
{
	int isDone = 0;
	int number = 0;
	
	Item infixExpression[MAX_EXP_LEN];

	int i = 0;

	/*
	-를 지원하는 방법 :
	숫자뒤에 온 -는 무조건 연산자 -다.
	그런데 연산자( '(' 포함) 뒤에 온 -는 부호를 결정하는 -다. 그런데 ')'다음의 -는 연산자임
	따라서 -가 연산자뒤에 올때마다 부호 변수에 -1을 곱해주고 다음 Number
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
				i--;	//infixExpression에 추가되는게 없으므로
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
			sign = 1;

			int result = CalculateInfixExpression(infixExpression);
			printf(" 결과 : %d\n", result);

			break;

		case EOFILE:
			isDone = 1;
			break;
			

		/*
		case ASSIGN:
			infixExpression[i].type = Op;
			infixExpression[i].data.op = '=';
			wasLastTokenNumberOrRParen = 0;

			break;

		case ALPABET:
			infixExpression[i].type = Variable;
			infixExpression[i].data.op = (char)number;  //number에 알파벳의 아스키 코드를 넣어 반환했다고 가정
			wasLastTokenNumberOrRParen = 0;

			break;
		*/

		default:
			
			break;
		}

		i++;
	}

	return 0;
}



//TODO : 이 함수 완성해서 쓰기
void GetStatement(Item * infixexpression)
{
	//여기서 메인 안 쪽의 switch-case문 옮겨넣기
}

#include <stdio.h>
#include <stdlib.h>
#include "Expression.h"
#include "Stack.h"
#include "Calculator.h"

int CalculateInfixExpression(const Item* infixExpression)
{
	Item postfixExp[MAX_EXP_LEN];

	ConvertInfixToPostfix(infixExpression, postfixExp);
	PrintExpression(postfixExp);

	return CalculatePostfix(postfixExp);
}

void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp)
{
	Stack sOperators;

	Init(&sOperators);

	while (1)
	{
		if (infixExp->type == Op)
		{
			char currentOp = infixExp->data.op;

			if (currentOp == '\0')
			{
				break;
			}

			if (currentOp == ')')
			{
				//'('가 없을 경우 대비
				while (sOperators.size > 0)
				{
					char top = Pop(&sOperators).op;

					if (top == '(')
					{
						break;
					}

					postfixExp->type = Op;
					postfixExp->data.op = top;
					++postfixExp;
				}
			}
			else if (currentOp == '(')
			{
				ItemData current;
				current.op = currentOp;
				Push(&sOperators, current);
			}
			else
			{
				int currentPriority = GetPriority(currentOp);

				while (sOperators.size > 0 && GetPriority(sOperators.datas[sOperators.top].op) >= currentPriority)
				{
					char top = Pop(&sOperators).op;

					postfixExp->type = Op;
					postfixExp->data.op = top;
					++postfixExp;
				}

				ItemData current;
				current.op = currentOp;
				Push(&sOperators, current);
			}
		}
		else    //숫자인 경우
		{
			postfixExp->type = Number;
			(postfixExp)->data.number = infixExp->data.number;
			postfixExp++;
		}

		infixExp++;
	}


	while (sOperators.size > 0)
	{
		char top = Pop(&sOperators).op;

		postfixExp->type = Op;
		postfixExp->data.op = top;
		++postfixExp;
	}

	postfixExp->type = Op;
	postfixExp->data.op = '\0';
}



int CalculatePostfix(const Item* postfixExpression)
{
	Stack sNumbers;
	ItemData numToPush;

	Init(&sNumbers);

	while (1)
	{
		if (postfixExpression->type == Op && postfixExpression->data.op == '\0')
			break;

		if (postfixExpression->type == Number)
		{
			numToPush.number = postfixExpression->data.number;
			Push(&sNumbers, numToPush);
		}
		else
		{
			int num1 = Pop(&sNumbers).number;
			int num2 = Pop(&sNumbers).number;

			switch (postfixExpression->data.op)
			{
			case '+':
				numToPush.number = num2 + num1;
				Push(&sNumbers, numToPush);
				break;

			case '-':
				numToPush.number = num2 - num1;
				Push(&sNumbers, numToPush);
				break;

			case '*':
				numToPush.number = num2 * num1;
				Push(&sNumbers, numToPush);
				break;

			case '/':
				numToPush.number = num2 / num1;
				Push(&sNumbers, numToPush);
				break;

			default:
				break;
			}
		}

		postfixExpression++;
	}

	return Pop(&sNumbers).number;
}


int GetPriority(char op)
{
	int priority = 0;

	switch (op)
	{
	case '(':	//스택에 들어간 뒤에는 가장 우선 순위가 낮은 것으로 취급됨.
		priority = 0;
		break;

	case '+':
	case '-':
		priority = 1;
		break;

	case '*':
	case '/':
		priority = 2;
		break;

	default:
		priority = -1;
		break;
	}

	return priority;
}


void PrintExpression(const Item* exp)
{
	while (1)
	{
		if (exp->type == Op)
		{
			if (exp->data.op == '\0')
			{
				printf("\n");
				return;
			}

			printf("%c", exp->data.op);
		}
		else
		{
			printf("%d", exp->data.number);
		}

		exp++;
	}
}

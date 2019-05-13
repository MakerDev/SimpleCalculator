#include <stdio.h>
#include <stdlib.h>

#include "Expression.h"
#include "calc_token.h"
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

	int wasLastTokenOperator = 1;
	int sign = 1;


	while (1)
	{
		if (infixExp->token == NUMBER)
		{
			*postfixExp = *infixExp;
			postfixExp->value *= sign;
			postfixExp++;

			sign = 1;
			wasLastTokenOperator = 0;
		}
		else
		{
			switch (infixExp->token)
			{
			case END:
				MoveOperatorsToPostfixExp(&sOperators, *infixExp, &postfixExp);
				*postfixExp = *infixExp;

				return;

			case LPAREN:
				Push(&sOperators, *infixExp);
				break;

			default:
				if (wasLastTokenOperator && infixExp->token == MINUS)
				{
					sign *= -1;
					break;
				}

				MoveOperatorsToPostfixExp(&sOperators, *infixExp, &postfixExp);

				break;
			}

			if (infixExp->token == RPAREN)
			{
				wasLastTokenOperator = 0;
				sign = 1;
			}
			else
			{
				wasLastTokenOperator = 1;
			}
		}

		infixExp++;
	}

	*postfixExp = *infixExp;
}

void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp)
{
	int i = 0;

	while (stack->top > -1 && (GetPriority(stack->datas[stack->top].token) >= GetPriority(currentItem.token)))
	{

		Item data = Pop(stack);

		//current가 RPAREN일때만 성립하고, 이 경우 LPAREN은 제거되어야 함.
		if (data.token == LPAREN)
		{
			break;
		}

		**postfixExp = data;
		(*postfixExp)++;
	}

	if (currentItem.token != RPAREN)
	{
		Push(stack, currentItem);
	}
}


int CalculatePostfix(const Item* postfixExpression)
{
	Stack sNumbers;
	Data dataToPush;

	int num1, num2;
	Init(&sNumbers);

	while (postfixExpression->token != END)
	{
		if (postfixExpression->token == NUMBER)
		{
			Push(&sNumbers, *postfixExpression);
		}
		else
		{
			num1 = Pop(&sNumbers).value;
			num2 = Pop(&sNumbers).value;

			switch (postfixExpression->token)
			{
			case PLUS:
				dataToPush.value = num2 + num1;

				Push(&sNumbers, dataToPush);

				break;

			case MINUS:
				dataToPush.value = num2 - num1;

				Push(&sNumbers, dataToPush);

				break;

			case TIMES:
				dataToPush.value = num2 * num1;

				Push(&sNumbers, dataToPush);

				break;

			case DIVIDE:
				dataToPush.value = num2 / num1;

				Push(&sNumbers, dataToPush);

				break;


			default:
				break;
			}
		}


		postfixExpression++;
	}

	return Pop(&sNumbers).value;

}

//스택에 있는 연산자의 우선순위인지 새로 추가하려는 연산자의 우선순위인지
int GetPriority(CalcToken token)
{
	int priority = 0;

	switch (token)
	{
	case END:
		priority = -1;
		break;

	case RPAREN:
		priority = 0;
		break;

	case LPAREN:	//스택에 들어간 뒤에는 가장 우선 순위가 낮은 것으로 취급됨.

		priority = 1;

		break;

	case PLUS:
	case MINUS:
		priority = 2;
		break;

	case TIMES:
	case DIVIDE:
		priority = 3;
		break;

	default:
		break;
	}

	return priority;
}


void PrintExpression(const Item* exp)
{
	while (1)
	{

		switch (exp->token)
		{
		case NUMBER:
			printf("%d ", exp->value);
			break;

		case PLUS:
			printf("+ ");
			break;

		case MINUS:
			printf("- ");
			break;

		case TIMES:
			printf("* ");
			break;

		case DIVIDE:
			printf("/ ");
			break;

		case LPAREN:
			printf("( ");
			break;

		case RPAREN:
			printf(") ");
			break;

		case END:
			printf("\n");
			return;

		default:
			break;
		}



		exp++;
	}
}

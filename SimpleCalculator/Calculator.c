#include <stdio.h>
#include <stdlib.h>

#include "Expression.h"
#include "calc_token.h"
#include "Stack.h"
#include "Calculator.h"

//TODO : �������� ��������
Item* VariableTable[26];

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
		if (infixExp->token == NUMBER)
		{
			*postfixExp = *infixExp;
			postfixExp++;
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
				MoveOperatorsToPostfixExp(&sOperators, *infixExp, &postfixExp);

				break;
			}
		}

		infixExp++;
	}

	*postfixExp = *infixExp;
}


//This Gets the pointer of postfix by getting the middle element's address not the first one.
void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp)
{
	int i = 0;

	while (stack->top > -1 && (GetPriority(stack->datas[stack->top].token, 1) >= GetPriority(currentItem.token, 0)))
	{

		Item data = Pop(stack);

		//current�� RPAREN�϶��� �����ϰ�, �� ��� LPAREN�� ���ŵǾ�� ��.
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

//���ÿ� �ִ� �������� �켱�������� ���� �߰��Ϸ��� �������� �켱��������
int GetPriority(CalcToken token, int isInStack)
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

	case LPAREN:	//���ÿ� �� �ڿ��� ���� �켱 ������ ���� ������ ��޵�.

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

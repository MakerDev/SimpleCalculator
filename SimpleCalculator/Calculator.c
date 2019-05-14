#include <stdio.h>
#include <stdlib.h>

#include "Calculator.h"
#include "calc_token.h"
#include "TableManager.h"
#include "Statement.h"
#include "Stack.h"



int CalculateInfixExpression(const Item* infixExpression)
{
	Item postfixExp[MAX_EXP_LEN];

	if (infixExpression->token == ASSIGN)
	{
		switch (infixExpression[1].token)
		{
		case VAR:
			AssignVariable(infixExpression);
			break;

		case FUNC:
			AssignFunction(infixExpression);
			break;

		default:
			break;
		}

		return -1;
	}

	ConvertInfixToPostfix(infixExpression, postfixExp);

	return CalculatePostfix(postfixExp);
}

void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp)
{
	Stack sOperators;

	Init(&sOperators);

	while (1)
	{
		if (infixExp->token == NUMBER || infixExp->token == VAR || infixExp->token == FUNC)
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

			case ASSIGN:


			default:
				MoveOperatorsToPostfixExp(&sOperators, *infixExp, &postfixExp);

				break;
			}
		}

		infixExp++;
	}

	*postfixExp = *infixExp;
}

void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp)
{
	int i = 0;

	while (stack->top > -1 && ((GetPriority(stack->datas[stack->top].token, 1)) >= GetPriority(currentItem.token, 0)))
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
		else if (postfixExpression->token == VAR)
		{
			dataToPush = *postfixExpression;
			dataToPush.value = GetValueOfVariable(dataToPush.value);

			Push(&sNumbers, dataToPush);
		}
		else if (postfixExpression->token == FUNC)
		{
			dataToPush = *postfixExpression;
			dataToPush.value = GetValueOfFunction(dataToPush.value);

			Push(&sNumbers, dataToPush);
		}
		else
		{
			num1 = Pop(&sNumbers).value;

			switch (postfixExpression->token)
			{
			case PLUS:
				num2 = Pop(&sNumbers).value;
				dataToPush.value = num2 + num1;

				Push(&sNumbers, dataToPush);

				break;

			case MINUS:
				num2 = Pop(&sNumbers).value;
				dataToPush.value = num2 - num1;

				Push(&sNumbers, dataToPush);

				break;

			case TIMES:
				num2 = Pop(&sNumbers).value;
				dataToPush.value = num2 * num1;

				Push(&sNumbers, dataToPush);

				break;

			case DIVIDE:
				num2 = Pop(&sNumbers).value;
				dataToPush.value = num2 / num1;

				Push(&sNumbers, dataToPush);

				break;

			case UNARYMINUS:
				dataToPush.token = NUMBER;
				dataToPush.value = num1 * (-1);

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
int GetPriority(CalcToken token, int isInStack)
{
	int priority = 0;

	switch (token)
	{
	case END:
		priority = 0;
		break;

	case RPAREN:
		priority = 1;
		break;

	case LPAREN:	//스택에 들어간 뒤에는 가장 우선 순위가 낮은 것으로 취급됨.
		priority = 2;
		break;

	case PLUS:
	case MINUS:
		priority = 3;
		break;

	case TIMES:
	case DIVIDE:
		priority = 4;
		break;

	case UNARYMINUS:
		if (isInStack)
		{
			priority = 5;
		}
		else
		{
			priority = 6;
		}

	default:
		break;
	}

	return priority;
}

StatementType GetStatement(Item * infixexpression)
{
	int i = 0;
	int wasLastTokenOperator = 1;


	while (1)
	{
		if (i >= MAX_EXP_LEN)
		{
			puts("Too Long Statement");
			exit(1);
		}

		infixexpression[i].token = GetToken(&(infixexpression[i].value));

		CalcToken token = infixexpression[i].token;

		if (token == EOFILE)
		{
			FreeFuncTable(-1);

			return END_OF_FILE;
		}
		else if (token == END)
		{
			if (infixexpression[0].token == ASSIGN)
			{
				return ASSIGNMENT;
			}
			else
			{
				return EXPRESSION;
			}
		}

		if (token == MINUS && wasLastTokenOperator)
		{
			infixexpression[i].token = UNARYMINUS;
		}

		if (token == NUMBER || token == VAR || token == FUNC || token == RPAREN)
		{
			wasLastTokenOperator = 0;
		}
		else
		{
			wasLastTokenOperator = 1;
		}

		i++;
	}


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

		case UNARYMINUS:
			printf("_ ");
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

		case VAR:
			printf("%c ", exp->value + 97);
			break;

		case FUNC:
			printf("%c ", exp->value + 65);
			break;

		case ASSIGN:
			printf("= ");
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



#include <stdio.h>
#include <stdlib.h>

#include "calc_token.h"
#include "Expression.h"
#include "Stack.h"
#include "Calculator.h"



int CalculateInfixExpression(const Item* infixExpression)
{
	Item postfixExp[MAX_EXP_LEN];

	//TODO : 프린트 없애기

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

void PrintExpression(const Item * exp)
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

VarTablePointer GetVariableTable()
{
	static int VariableTable[SIZE_OF_TABLE][2];
	static int isTableInitialized = 0;

	if (!isTableInitialized)
	{
		//초기에는 어떤 변수도 존재하지 않음.
		for (int i = 0; i < SIZE_OF_TABLE; i++)
		{
			VariableTable[i][0] = 0;
		}

		isTableInitialized = 1;
	}

	return VariableTable;
}

FunctionTablePointer GetFuncTable()
{
	static Item* FunctionTable[SIZE_OF_TABLE];
	static int isTableInitialized = 0;

	if (!isTableInitialized)
	{
		//초기에는 어떤 변수도 존재하지 않음.
		for (int i = 0; i < SIZE_OF_TABLE; i++)
		{
			FunctionTable[i] = NULL;
		}

		isTableInitialized = 1;
	}

	return FunctionTable;
}

void AssignVariable(const Item * assignmentStatement)
{
	VarTablePointer VariableTable = GetVariableTable();

	int varIndex = assignmentStatement[1].value;
	int value;
	value = CalculateInfixExpression(&assignmentStatement[2]);

	VariableTable[varIndex][0] = 1;
	VariableTable[varIndex][1] = value;
}

void FreeFuncTable(int index)
{
	FunctionTablePointer FuncTable = GetFuncTable();

	int i = 0;


	if (index == -1)
	{
		while (FuncTable[i] != NULL)
		{
			free(FuncTable[i]);
			FuncTable[i] = NULL;
			i++;
		}
	}
	else
	{
		free(FuncTable[index]);
	}

}

int GetValueOfVariable(int var)
{
	const VarTablePointer VarTable = GetVariableTable();

	if (!VarTable[var][0])
	{
		printf("ERROR! 변수 %c가 정의되지 않았습니다.\n", var + 97);
		exit(1);
	}

	return VarTable[var][1];
}


void AssignFunction(const Item * assignmentStatement)
{
	FunctionTablePointer FuncTable = GetFuncTable();

	int funcIndex = assignmentStatement[1].value;

	if (FuncTable[funcIndex] != NULL)
	{
		FreeFuncTable(funcIndex);
	}

	FuncTable[funcIndex] = (Item*)malloc(sizeof(Item) * MAX_SIZE_OF_FUNC);

	int i = 2;

	while (1)
	{
		if(FuncTable[funcIndex]!=NULL)
			FuncTable[funcIndex][i - 2] = assignmentStatement[i];

		if (assignmentStatement[i].token == END)
			break;

		i++;
	}

}

int GetValueOfFunction(int func)
{
	const Item** FuncTable = GetFuncTable();

	if (FuncTable[func] == NULL)
	{
		printf("ERROR! 함수 %c가 정의되지 않았습니다.\n", func + 65);
		exit(1);
	}

	int value = CalculateInfixExpression(FuncTable[func]);

	return value;
}

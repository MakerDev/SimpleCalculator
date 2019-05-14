#include <stdio.h>
#include <stdlib.h>

#include "TableManager.h"
#include "Calculator.h"


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

void AssignVariable(const Item* assignmentStatement)
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
		if (FuncTable[funcIndex] != NULL)
			FuncTable[funcIndex][i - 2] = assignmentStatement[i];

		if (assignmentStatement[i].token == END)
			break;

		i++;
	}

}

int GetValueOfFunction(int func)
{
	const FunctionTablePointer FuncTable = GetFuncTable();

	if (FuncTable[func] == NULL)
	{
		printf("ERROR! 함수 %c가 정의되지 않았습니다.\n", func + 65);
		exit(1);
	}

	int value = CalculateInfixExpression(FuncTable[func]);

	return value;
}
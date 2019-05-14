#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Stack.h"
#include "Expression.h"

#define SIZE_OF_TABLE 26
#define MAX_SIZE_OF_FUNC 50

typedef enum _StatementType {
	END_OF_FILE, ASSIGNMENT, EXPRESSION
} StatementType;

typedef int(*VarTablePointer)[2];
typedef Item** FunctionTablePointer;

int CalculateInfixExpression(const Item* infixExpression);  //그냥 infix를 넣으면 바로 결과 주는 함수
void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp);
int CalculatePostfix(const Item* postfixExpression);
int GetPriority(CalcToken token, int isInStack);
void PrintExpression(const Item* exp);
void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp);
StatementType GetStatement(Item* infixexpression);

VarTablePointer GetVariableTable();
FunctionTablePointer GetFuncTable();

void AssignVariable(const Item* assignmentStatement);
int GetValueOfVariable(int var);
void AssignFunction(const Item* assignmentStatement);
int GetValueOfFunction(int func);
void FreeFuncTable(int index);

#endif

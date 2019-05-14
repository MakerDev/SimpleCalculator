#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Stack.h"
#include "Statement.h"


int CalculateInfixExpression(const Item* infixExpression);  //그냥 infix를 넣으면 바로 결과 주는 함수
void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp);
int CalculatePostfix(const Item* postfixExpression);
int GetPriority(CalcToken token, int isInStack);
void PrintExpression(const Item* exp);
void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp);
StatementType GetStatement(Item* infixexpression);

#endif

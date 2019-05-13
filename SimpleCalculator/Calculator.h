#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Expression.h"

int CalculateInfixExpression(const Item* infixExpression);  //�׳� infix�� ������ �ٷ� ��� �ִ� �Լ�
void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp);
int CalculatePostfix(const Item* postfixExpression);
int GetPriority(CalcToken token);
void PrintExpression(const Item* exp);
void MoveOperatorsToPostfixExp(Stack* stack, Item currentItem, Item** postfixExp);

#endif

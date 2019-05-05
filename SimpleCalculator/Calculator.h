#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Expression.h"

int CalculateInfixExpression(const Item* infixExpression);  //그냥 infix를 넣으면 바로 결과 주는 함수
void ConvertInfixToPostfix(const Item* infixExp, Item* postfixExp);
int CalculatePostfix(const Item* postfixExpression);
int GetPriority(char op);
void PrintExpression(const Item* exp);

#endif

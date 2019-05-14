#include <stdio.h>

#include "Calculator.h"
#include "Expression.h"



int main()
{
	StatementType tyepOfStatement;
	int number = 0;
	int result;
	Item infixStatement[MAX_EXP_LEN];

	while (1)
	{
		tyepOfStatement = GetStatement(infixStatement);

		switch (tyepOfStatement)
		{
		case END_OF_FILE:
			return 0;

		case EXPRESSION:
			result = CalculateInfixExpression(infixStatement);
			printf("Result : %d\n", result);
			break;

		case ASSIGNMENT:
			CalculateInfixExpression(infixStatement);
			break;

		default:
			break;
		}
	}


	return 0;
}




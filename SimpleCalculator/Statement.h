#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "calc_token.h"

#define MAX_EXP_LEN 255

typedef enum _StatementType {
	END_OF_FILE, ASSIGNMENT, EXPRESSION
} StatementType;

typedef struct _Item {
	CalcToken token;
	int value;
} Item;

#endif 

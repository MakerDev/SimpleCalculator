#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "calc_token.h"

#define MAX_EXP_LEN 255

typedef struct _Item {
	CalcToken token;
	int value;
} Item;


#endif 

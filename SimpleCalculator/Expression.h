#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "calc_token.h"

#define MAX_EXP_LEN 255

//Variable은 a=3 or b=a*3이런 거고, 이 경우 Item의 데이터는 op에 알파벳이 들어가면 된다.
typedef enum _eType
{
	Op, Number, Variable

} eType;

typedef union _Data {
	int number;
	char op;

} ItemData;

//typedef struct _Item {
//	eType type;
//	ItemData data;
//} Item;

typedef struct _Item {
	CalcToken token;
	int value;
} Item;


#endif 

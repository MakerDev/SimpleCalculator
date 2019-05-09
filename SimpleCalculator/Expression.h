#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "calc_token.h"

#define MAX_EXP_LEN 255

//Variable�� a=3 or b=a*3�̷� �Ű�, �� ��� Item�� �����ʹ� op�� ���ĺ��� ���� �ȴ�.
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

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#define MAX_EXP_LEN 255

typedef enum _eType
{
	Op, Number

} eType;

typedef union _Data {
	int number;
	char op;

} ItemData;

typedef struct _Item {
	eType type;
	ItemData data;
} Item;


#endif 

#ifndef _TABLE_MANAGER_H_
#define _TABLE_MANAGER_H_

#include "Expression.h"

#define SIZE_OF_TABLE 26
#define MAX_SIZE_OF_FUNC 50

typedef int(*VarTablePointer)[2];
typedef Item** FunctionTablePointer;

VarTablePointer GetVariableTable();
FunctionTablePointer GetFuncTable();

void AssignVariable(const Item* assignmentStatement);
int GetValueOfVariable(int var);
void AssignFunction(const Item* assignmentStatement);
int GetValueOfFunction(int func);
void FreeFuncTable(int index);


#endif // !_TABLE_MANAGER_H_

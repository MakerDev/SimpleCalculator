#ifndef CALC_TOKEN_H
#define CALC_TOKEN_H

typedef enum {
    NUMBER, PLUS, MINUS, TIMES, DIVIDE, LPAREN,
    RPAREN, ASSIGN, VAR, FUNC, END, EOFILE
} CalcToken;

CalcToken GetToken(int *number);

#endif

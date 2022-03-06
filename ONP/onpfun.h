#ifndef _ONPFUN_H
#define _ONPFUN_H

void skipSpaces();
double getNum();
int getNum1();
int isDigit(char c);
int prior(char cOper);
int isOper(char cOper);
char getOper();
void onp();
double evalONP(char cOper, double arg1, double arg2);
double calcONP();

#endif
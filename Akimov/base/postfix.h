#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
public:
  TPostfix() : infix("a + b") {}
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  void SetInfix(const string& expr) { infix = expr; }
  string ToPostfix();
  double Calculate(map<char, double> variables);
private:
  int GetPriority(char op);
  bool IsOperator(char c);
  double StringToNumber(const string& str);
};

#endif
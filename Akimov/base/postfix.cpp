#include "postfix.h"
#include "stack.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int TPostfix::GetPriority(char op)
{
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool TPostfix::IsOperator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

string TPostfix::ToPostfix() {
  TStack<char> operators(MaxStackSize);
  stringstream output;
  string currentToken;
  for (char current : infix)
  {
    if (isspace(current)) continue;
    if (isalnum(current) || current == '.')
      currentToken += current;
    else
    {
      if (!currentToken.empty())
      {
        output << currentToken << ' ';
        currentToken.clear();
      }
      if (IsOperator(current))
      {
        while (!operators.isEmpty() && GetPriority(operators.peek()) >= GetPriority(current))
          output << operators.pop() << ' ';
        operators.push(current);
      }
      else if (current == '(')
        operators.push(current);
      else if (current == ')')
      {
        while (!operators.isEmpty() && operators.peek() != '(')
          output << operators.pop() << ' ';
        operators.pop();
      }
      else
        throw invalid_argument("Invalid character encountered: " + string(1, current));
    }
  }
  if (!currentToken.empty())
    output << currentToken << ' ';
  while (!operators.isEmpty())
    output << operators.pop() << ' ';
  postfix = output.str();
  return postfix;
}

double TPostfix::StringToNumber(const string& str)
{
  double result;
  stringstream ss(str);
  ss >> result;
  if (ss.fail()) throw invalid_argument("Invalid number format: " + str);
  return result;
}

double TPostfix::Calculate(map<char, double> variables)
{
  TStack<double> stack(MaxStackSize);
  stringstream ss(postfix);
  string token;
  while (ss >> token)
  {
    if (isalnum(token[0]))
    {
      char var = token[0];
      if (variables.find(var) == variables.end())
        throw invalid_argument("Unknown variable: " + token);
      stack.push(variables[var]);
    }
    else if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1))
      stack.push(StringToNumber(token));
    else if (IsOperator(token[0]))
    {
      double b = stack.pop();
      double a = stack.pop();
      switch (token[0])
      {
      case '+': stack.push(a + b); break;
      case '-': stack.push(a - b); break;
      case '*': stack.push(a * b); break;
      case '/':
        if (b == 0) throw invalid_argument("Division by zero");
        stack.push(a / b);
        break;
      default: throw invalid_argument("Invalid operator");
      }
    }
    else
      throw invalid_argument("Invalid token: " + token);
  }
  return stack.pop();
}
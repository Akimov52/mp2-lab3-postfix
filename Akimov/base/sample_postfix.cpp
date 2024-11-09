#include <iostream>
#include <string>
#include <sstream>
#include "postfix.h"
#include <map>
#include <stdexcept>

using namespace std;

int main()
{
  setlocale(LC_ALL, "Russian");
  string expression;
  cout << "Введите арифметическое выражение (например, a + b * (c - d)): ";
  getline(cin, expression);
  TPostfix postfix;
  try
  {
    postfix.SetInfix(expression);
    string postfixExpression = postfix.ToPostfix();
    cout << "Постфиксная форма: " << postfixExpression << endl;
  }
  catch (const invalid_argument& e)
  {
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
  }
  map<char, double> variables;
  cout << "Введите значения переменных (например, a=5, b=3, c=8):" << endl;
  string varInput;
  while (true)
  {
    cout << "Введите переменную и её значение (или 'end' для завершения): ";
    getline(cin, varInput);
    if (varInput == "end") break;
    size_t pos = varInput.find('=');
    if (pos != string::npos)
    {
      char var = varInput[0];
      double value;
      stringstream ss(varInput.substr(pos + 1));
      ss >> value;
      if (ss)
        variables[var] = value;
      else
        cout << "Ошибка ввода значения. Повторите попытку." << endl;
    }
    else
      cout << "Ошибка ввода формата. Используйте формат 'a=5'. Повторите попытку." << endl;
  }
  try
  {
    double result = postfix.Calculate(variables);
    cout << "Результат вычисления: " << result << endl;
  }
  catch (const invalid_argument& e)
  {
    cerr << "Ошибка вычисления: " << e.what() << endl;
    return 1;
  }
  catch (const runtime_error& e) {
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
  }
  return 0;
}
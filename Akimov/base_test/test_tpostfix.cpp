#include "postfix.h"
#include <gtest.h>
#include <map>

using namespace std;

TEST(TPostfix, can_set_and_get_infix_expression)
{
  TPostfix expr;
  expr.SetInfix("a+b");
  EXPECT_EQ(expr.GetInfix(), "a+b");
}

TEST(TPostfix, can_convert_simple_infix_to_postfix)
{
  TPostfix expr;
  expr.SetInfix("a+b");
  EXPECT_EQ(expr.ToPostfix(), "a b + ");
}

TEST(TPostfix, can_convert_complex_infix_to_postfix)
{
  TPostfix expr;
  expr.SetInfix("a+b*(c-d)");
  EXPECT_EQ(expr.ToPostfix(), "a b c d - * + ");
}

TEST(TPostfix, can_calculate_simple_expression)
{
  TPostfix expr;
  expr.SetInfix("a+b");
  expr.ToPostfix();
  map<char, double> vars = { {'a', 2}, {'b', 3} };
  EXPECT_EQ(expr.Calculate(vars), 5);
}

TEST(TPostfix, throws_when_dividing_by_zero)
{
  TPostfix expr;
  expr.SetInfix("a/b");
  expr.ToPostfix();
  map<char, double> vars = { {'a', 10}, {'b', 0} };
  ASSERT_ANY_THROW(expr.Calculate(vars));
}

TEST(TPostfix, throws_on_invalid_character)
{
  TPostfix expr;
  expr.SetInfix("a+b$");
  ASSERT_ANY_THROW(expr.ToPostfix());
}
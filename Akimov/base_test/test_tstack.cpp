#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
  ASSERT_NO_THROW(TStack<int> st(10));
}

TEST(TStack, cant_create_stack_with_negative_size)
{
  ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cant_create_stack_with_too_large_size)
{
  ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, can_push_element)
{
  TStack<int> st(10);
  ASSERT_NO_THROW(st.push(1));
}

TEST(TStack, can_pop_element)
{
  TStack<int> st(10);
  st.push(1);
  EXPECT_EQ(st.pop(), 1);
}

TEST(TStack, cant_pop_from_empty_stack)
{
  TStack<int> st(10);
  ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, is_empty_returns_true_for_new_stack)
{
  TStack<int> st(10);
  EXPECT_TRUE(st.isEmpty());
}

TEST(TStack, is_full_returns_true_when_stack_is_full)
{
  TStack<int> st(2);
  st.push(1);
  st.push(2);
  EXPECT_TRUE(st.isFull());
}

TEST(TStack, peek_returns_top_element_without_removing)
{
  TStack<int> st(10);
  st.push(42);
  EXPECT_EQ(st.peek(), 42);
  EXPECT_EQ(st.getSize(), 1);
}
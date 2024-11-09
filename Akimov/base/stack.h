#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

using namespace std;

template <class T>
class TStack
{
  T* pMem;
  int size;
  int top;
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }

  ~TStack()
  {
    delete[] pMem;
  }

  bool isEmpty() const
  {
    return top == -1;
  }

  bool isFull() const
  {
    return top == size - 1;
  }

  void push(const T& value)
  {
    if (isFull())
      throw overflow_error("Stack overflow");
    pMem[++top] = value;
  }

  T pop()
  {
    if (isEmpty())
      throw underflow_error("Stack underflow");
    return pMem[top--];
  }

  T peek() const
  {
    if (isEmpty())
      throw runtime_error("Stack is empty");
    return pMem[top];
  }

  int getSize() const
  {
    return top + 1;
  }
};

#endif
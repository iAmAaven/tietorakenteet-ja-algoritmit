#pragma once

const int maxstack = 10;

enum Error_code
{
    success,
    overflow,
    underflow
};

typedef char Stack_entry;

class Stack
{
public:
    Stack();
    bool empty() const;
    Error_code pop();
    Error_code top(Stack_entry &item) const;
    Error_code push(const Stack_entry &item);
    Error_code clear();
    friend Error_code copy_stack_friend(Stack &dest, Stack &source);

private:
    int count;
    Stack_entry entry[maxstack];
};

Error_code copy_stack_simple(Stack &dest, Stack &source);
Error_code copy_stack_methods(Stack &dest, Stack &source);
Error_code copy_stack_friend(Stack &dest, Stack &source);
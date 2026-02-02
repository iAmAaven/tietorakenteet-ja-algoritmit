#pragma once

const int maxstack = 10;

enum Error_code
{
    success,
    overflow,
    underflow
};

typedef char Stack_entry;

class Extended_stack
{
public:
    Extended_stack();
    Error_code pop();
    Error_code push(const Stack_entry &item);
    Error_code top(Stack_entry &item) const;
    bool empty() const;
    void clear();      // Reset the stack to be empty.
    bool full() const; // If the stack is full, return true; else return false.
    int size() const;  // Return the number of entries in the stack.

private:
    int count;
    Stack_entry entry[maxstack];
};
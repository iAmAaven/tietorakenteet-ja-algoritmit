#include "stack.h"

Stack::Stack()
/*
Pre: None.
Post: The stack is initialized to be empty.
*/
{
    count = 0;
}

bool Stack::empty() const
/*
Pre: None.
Post: If the Stack is empty, true is returned. Otherwise false is returned.
*/
{
    // Optimoitu versio luennon materiaalista
    return count == 0;
}

Error_code Stack::push(const Stack_entry &item)
/*
Pre: None.
Post: If the Stack is not full, item is added to the top of the Stack. If the Stack is
full, an Error code of overflow is returned and the Stack is left unchanged.
*/
{
    // Optimoitu versio luennon materiaalista
    if (count >= maxstack)
        return overflow;
    entry[count++] = item;
    return success;
}

Error_code Stack::pop()
/*
Pre: None.
Post: If the Stack is not empty, the top of the Stack is removed. If the Stack is
empty, an Error code of underflow is returned.
*/
{
    // Optimoitu versio luennon materiaalista
    if (count == 0)
        return underflow;
    --count;
    return success;
}

Error_code Stack::top(Stack_entry &item) const
/*
Pre: None.
Post: If the Stack is not empty, the top of the Stack is returned in item. If the Stack
is empty an Error code of underflow is returned.
*/
{
    // Optimoitu versio luennon materiaalista
    if (count == 0)
        return underflow;
    item = entry[count - 1];
    return success;
}
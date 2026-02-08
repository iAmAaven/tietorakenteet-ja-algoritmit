#include "stack.h"

Error_code copy_stack_simple(Stack &dest, Stack &source);
Error_code copy_stack_methods(Stack &dest, Stack &source);
Error_code copy_stack_friend(Stack &dest, Stack &source);

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

Error_code Stack::clear()
/*
Pre: None.
Post: The stack is reset to empty.
*/
{
    count = 0;
    return success;
};

// Exercise 1a
Error_code copy_stack_simple(Stack &dest, Stack &source)
{
    dest = source;
    return success;
}

// Exercise 1b
Error_code copy_stack_methods(Stack &dest, Stack &source)
{
    Stack tmp;
    Stack_entry entry;
    dest.clear();

    while (!source.empty())
    {
        source.top(entry);
        tmp.push(entry);
        source.pop();
    }

    while (!tmp.empty())
    {
        tmp.top(entry);
        dest.push(entry);
        source.push(entry);
        tmp.pop();
    }

    return success;
}

// Exercise 1c
Error_code copy_stack_friend(Stack &dest, Stack &source)
{
    dest.count = source.count;
    for (int i = 0; i < source.count; i++)
    {
        dest.entry[i] = source.entry[i];
    }
    return success;
}

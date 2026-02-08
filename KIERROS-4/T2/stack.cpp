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

Error_code copy_stack_simple(Stack &dest, Stack &source)
{
    dest = source;
    return success;
}

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

Error_code copy_stack_friend(Stack &dest, Stack &source)
{
    dest.count = source.count;
    for (int i = 0; i < source.count; i++)
    {
        dest.entry[i] = source.entry[i];
    }
    return success;
}

// Exercise 2a
bool full(Stack &s)
{
    Stack_entry dummy = 0;
    Error_code result = s.push(dummy);
    if (result == overflow)
        return true;
    if (result == success)
        s.pop();
    return false;
}

// Exercise 2b
Error_code pop_top(Stack &s, Stack_entry &t)
{
    Error_code result = s.top(t);
    if (result != success)
        return result;
    return s.pop();
}

// Exercise 2c
void clear(Stack &s)
{
    while (!s.empty())
        s.pop();
}

// Exercise 2d
int size(Stack &s)
{
    int count = 0;
    Stack tmp;
    Stack_entry e;
    while (!s.empty())
    {
        s.top(e);
        tmp.push(e);
        s.pop();
        count++;
    }
    while (!tmp.empty())
    {
        tmp.top(e);
        s.push(e);
        tmp.pop();
    }
    return count;
}

// Exercise 2e
void delete_all(Stack &s, Stack_entry x)
{
    Stack tmp;
    Stack_entry e;
    while (!s.empty())
    {
        s.top(e);
        s.pop();
        if (e != x)
            tmp.push(e);
    }
    while (!tmp.empty())
    {
        tmp.top(e);
        s.push(e);
        tmp.pop();
    }
}

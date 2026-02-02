#include "stack.h"

Extended_stack::Extended_stack()
{
    count = 0;
}

bool Extended_stack::empty() const
{
    return count == 0;
}

Error_code Extended_stack::push(const Stack_entry &item)
{
    if (count >= maxstack)
        return overflow;
    entry[count++] = item;
    return success;
}

Error_code Extended_stack::pop()
{
    if (count == 0)
        return underflow;
    --count;
    return success;
}

Error_code Extended_stack::top(Stack_entry &item) const
{
    if (count == 0)
        return underflow;
    item = entry[count - 1];
    return success;
}

// (a) clear
void Extended_stack::clear()
{
    count = 0;
}

// (b) full
bool Extended_stack::full() const
{
    return count == maxstack;
}

// (c) size
int Extended_stack::size() const
{
    return count;
}
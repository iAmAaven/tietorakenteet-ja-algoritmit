#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Stack source, s2, s3, s4;
    Stack_entry item;

    source.push('A');
    source.push('B');
    source.push('C');

    copy_stack_simple(s2, source);
    cout << "Simple: ";
    while (!s2.empty())
    {
        s2.top(item);
        cout << item << " ";
        s2.pop();
    }
    cout << endl;

    copy_stack_methods(s3, source);
    cout << "Methods: ";
    while (!s3.empty())
    {
        s3.top(item);
        cout << item << " ";
        s3.pop();
    }
    cout << endl;

    copy_stack_friend(s4, source);
    cout << "Friend: ";
    while (!s4.empty())
    {
        s4.top(item);
        cout << item << " ";
        s4.pop();
    }
    cout << endl;

    return 0;
}

/*

    Which of these is easiest to write?
        copy_stack_simple()

    Which will run most quickly if the stack is nearly full?
        copy_stack_simple() or copy_stack_friend()

    Which will run most quickly if the stack is nearly empty?
        copy_stack_simple() or copy_stack_friend()

    Which would be the best method if the implementation might be changed?
        copy_stack_methods() -> Only uses public methods

    In which could we pass the parameter source as a constant reference?
        Only copy_stack_simple() and copy_stack_friend()

*/
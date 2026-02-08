#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Stack s;
    Stack_entry t;

    cout << endl;
    // Test Exercise 2a
    cout << "Testing full()..." << endl;
    for (int i = 0; i < maxstack; ++i)
        s.push('A' + i);
    cout << "Is stack full? " << (full(s) ? "Yes" : "No") << endl;

    cout << endl;
    // Test Exercise 2b
    cout << "Testing pop_top()..." << endl;
    Error_code res = pop_top(s, t);
    cout << "pop_top result: " << (res == success ? "success" : "error") << ", value: " << t << endl;

    cout << endl;
    // Test Exercise 2d
    cout << "Testing size()..." << endl;
    cout << "Stack size: " << size(s) << endl;

    cout << endl;
    // Test Exercise 2e
    cout << "Testing delete_all()..." << endl;
    delete_all(s, 'B');
    cout << "Stack size after deleting 'B': " << size(s) << endl;

    cout << endl;
    // Test Exercise 2c
    cout << "Testing clear()..." << endl;
    clear(s);
    cout << "Stack size after clear: " << size(s) << endl;
    cout << endl;

    return 0;
}

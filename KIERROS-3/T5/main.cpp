#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Extended_stack s;

    cout << "Pushing elements onto the stack..." << endl;
    for (int i = 0; i < maxstack; ++i)
    {
        s.push('A' + i);
        cout << "Size after push: " << s.size() << endl;
    }

    cout << "Is stack full? " << (s.full() ? "Yes" : "No") << endl;

    s.clear();
    cout << "Stack cleared." << endl;
    cout << "Size after clear: " << s.size() << endl;
    cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << endl;

    s.push('Z');
    cout << "Pushed 'Z' after clear. Size: " << s.size() << endl;

    return 0;
}
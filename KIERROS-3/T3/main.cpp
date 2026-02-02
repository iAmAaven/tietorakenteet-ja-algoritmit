#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
    Stack s;
    string line;
    cout << "Enter a line of text: ";
    getline(cin, line);

    for (char c : line)
    {
        if (s.push(c) == overflow)
        {
            cout << "Stack overflow, cannot reverse entire line." << endl;
            break;
        }
    }

    Stack_entry ch;
    cout << "Reversed: ";
    while (!s.empty())
    {
        s.top(ch);
        cout << ch;
        s.pop();
    }
    cout << endl;
    return 0;
}
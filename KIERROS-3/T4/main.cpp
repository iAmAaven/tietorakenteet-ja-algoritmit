#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    Stack s;
    int prev, curr;
    bool first = true;

    cout << "Enter a sequence of increasing integers (end with a non-increasing value):" << endl;

    while (true)
    {
        cin >> curr;
        if (!first && curr <= prev)
            break;
        if (s.push(static_cast<Stack_entry>(curr)) == overflow)
        {
            cout << "Stack overflow, cannot store more numbers." << endl;
            break;
        }
        prev = curr;
        first = false;
    }

    cout << "Numbers in decreasing order:" << endl;
    Stack_entry value;
    while (!s.empty())
    {
        s.top(value);
        cout << static_cast<int>(value) << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}
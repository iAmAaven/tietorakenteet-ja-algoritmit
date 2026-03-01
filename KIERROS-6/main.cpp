#include "queue.h"
#include <iostream>
using namespace std;

static char analyze_line()
{
    Extended_queue left;
    bool found_colon = false;
    bool mismatch = false;
    bool right_is_longer = false;

    char ch;
    while (cin.get(ch))
    {
        if (ch == '\r')
            continue;
        if (ch == '\n')
            break;

        if (!found_colon)
        {
            if (ch == ':')
                found_colon = true;
            else
                left.append(ch);
        }
        else
        {
            if (left.empty())
                right_is_longer = true;
            else
            {
                Queue_entry expected;
                left.retrieve(expected);
                left.serve();
                if (expected != ch)
                    mismatch = true;
            }
        }
    }

    if (!found_colon)
        return 'N';
    if (right_is_longer)
        return 'R';
    if (!left.empty())
        return 'L';
    return mismatch ? 'D' : 'S';
}

int main()
{
    cout << analyze_line();
    return EXIT_SUCCESS;
}
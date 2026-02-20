#include <iostream>
#include <cstdlib>
#include "queue.h"
using namespace std;

void introduction()
{
    cout << "=======================\n";
    cout << "  Extended Queue Demo \n";
    cout << "=======================\n\n";
    cout << "This program demonstrates the Extended_queue data structure.\n";
    cout << "Type 'H' for help on available commands.\n\n";
}

char get_command()
{
    char command;
    cout << "Enter command (H for help): ";
    cin >> command;
    if (command >= 'A' && command <= 'Z')
        command = command - 'A' + 'a';
    return command;
}

void help()
{
    cout << endl
         << "This program allows the user to enter one command" << endl
         << "(but only one) on each input line." << endl
         << "For example, if the command S is entered, then" << endl
         << "the program will serve the front of the queue." << endl
         << endl
         << " The valid commands are:" << endl
         << "A - Append the next input character to the extended queue" << endl
         << "S - Serve the front of the extended queue" << endl
         << "R - Retrieve and print the front entry." << endl
         << "# - The current size of the extended queue" << endl
         << "C - Clear the extended queue (same as delete)" << endl
         << "P - Print the extended queue" << endl
         << "H - This help screen" << endl
         << "Q - Quit" << endl
         << "Press <Enter> to continue." << flush;

    char c;
    do
    {
        cin.get(c);
    } while (c != '\n');
}

bool do_command(char c, Extended_queue &q)
{
    bool cont = true;
    Queue_entry x;
    switch (c)
    {
    case 'a':
        cout << "Enter a character to append: ";
        cin >> x;
        if (q.append(x) == overflow)
            cout << "Queue is full. Cannot append." << endl;
        else
            cout << "'" << x << "' appended." << endl;
        break;
    case 's':
        if (q.serve() == underflow)
            cout << "Queue is empty. Cannot serve." << endl;
        else
            cout << "Front entry served (removed)." << endl;
        break;
    case 'r':
        if (q.retrieve(x) == underflow)
            cout << "Queue is empty." << endl;
        else
            cout << "Front entry: " << x << endl;
        break;
    case '#':
        cout << "Queue size: " << q.size() << endl;
        break;
    case 'c':
        q.clear();
        cout << "Queue cleared." << endl;
        break;
    case 'p':
    {
        if (q.empty())
        {
            cout << "Queue is empty." << endl;
        }
        else
        {
            cout << "Queue contents: ";
            Extended_queue temp = q;
            for (int i = 0; i < temp.size(); ++i)
            {
                temp.retrieve(x);
                cout << x << (i < temp.size() - 1 ? " " : "");
                temp.serve();
            }
            cout << endl;
        }
        break;
    }
    case 'h':
        help();
        break;
    case 'q':
        cout << "Exiting program." << endl;
        cont = false;
        break;
    default:
        cout << "Invalid command. Type 'H' for help." << endl;
    }
    return cont;
}

class Stack
{
public:
    Stack() : top(-1) {}
    bool empty() const { return top == -1; }
    Error_code push(int item)
    {
        if (top >= maxstack - 1)
            return overflow;
        lifo_stack[++top] = item;
        return success;
    }
    Error_code pop()
    {
        if (top < 0)
            return underflow;
        top--;
        return success;
    }
    Error_code peek(int &item) const
    {
        if (top < 0)
            return underflow;
        item = lifo_stack[top];
        return success;
    }

private:
    int top;
    int lifo_stack[300];
    static const int maxstack = 300;
};

int main()
{
    int prices[5] = {10, 30, 20, 50, 30};
    Extended_queue fifo;
    Stack lifo;

    for (int i = 0; i < 100; ++i)
        fifo.append(prices[0]), lifo.push(prices[0]);
    for (int i = 0; i < 100; ++i)
        fifo.append(prices[1]), lifo.push(prices[1]);
    for (int i = 0; i < 100; ++i)
        fifo.append(prices[3]), lifo.push(prices[3]);

    int fifo_gain = 0, lifo_gain = 0;
    int buy_price;

    for (int i = 0; i < 200; ++i)
    {
        fifo.retrieve(buy_price);
        fifo_gain += (i < 100 ? prices[2] : prices[4]) - buy_price;
        fifo.serve();
    }

    for (int i = 0; i < 200; ++i)
    {
        lifo.peek(buy_price);
        lifo_gain += (i < 100 ? prices[2] : prices[4]) - buy_price;
        lifo.pop();
    }

    cout << "FIFO gain/loss: $" << fifo_gain << endl;
    cout << "LIFO gain/loss: $" << lifo_gain << endl;
    return EXIT_SUCCESS;
}
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

void moveStackToQueue(Stack &s, Extended_queue &q)
{
    int item;
    while (!s.empty() && !q.full())
    {
        if (s.peek(item) == success)
        {
            q.append(item);
            s.pop();
        }
        else
            break;
    }
}

void moveQueueToStack(Extended_queue &q, Stack &s)
{
    int item;
    while (!q.empty() && s.push(0) != overflow)
    {
        s.pop();
        if (q.serve_and_retrieve(item) == success)
            s.push(item);
        else
            break;
    }
}

void moveStackToStackPreserveOrder(Stack &from, Stack &to)
{
    Stack temp;
    int item;
    while (!from.empty() && temp.push(0) != overflow)
    {
        temp.pop();
        if (from.peek(item) == success)
        {
            temp.push(item);
            from.pop();
        }
        else
            break;
    }

    while (!temp.empty() && to.push(0) != overflow)
    {
        to.pop();
        if (temp.peek(item) == success)
        {
            to.push(item);
            temp.pop();
        }
        else
            break;
    }
}

void moveStackToStackReverseOrder(Stack &from, Stack &to)
{
    int item;
    while (!from.empty() && to.push(0) != overflow)
    {
        to.pop();
        if (from.peek(item) == success)
        {
            to.push(item);
            from.pop();
        }
        else
            break;
    }
}

void reverseQueueWithStack(Extended_queue &q)
{
    Stack temp;
    int item;
    while (!q.empty() && temp.push(0) != overflow)
    {
        temp.pop();
        if (q.serve_and_retrieve(item) == success)
            temp.push(item);
        else
            break;
    }

    while (!temp.empty() && !q.full())
    {
        if (temp.peek(item) == success)
        {
            q.append(item);
            temp.pop();
        }
        else
            break;
    }
}

void reverseStackWithQueue(Stack &s)
{
    Extended_queue temp;
    int item;

    while (!s.empty() && !temp.full())
    {
        if (s.peek(item) == success)
        {
            temp.append(item);
            s.pop();
        }
        else
            break;
    }

    while (!temp.empty() && s.push(0) != overflow)
    {
        s.pop();
        if (temp.serve_and_retrieve(item) == success)
            s.push(item);
        else
            break;
    }
}

int main()
{
    // A PART --------------------------------
    Stack s1;
    Extended_queue q1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    moveStackToQueue(s1, q1);
    int x;
    cout << "(a) Stack->Queue: ";
    while (!q1.empty())
    {
        q1.serve_and_retrieve(x);
        cout << x << ' ';
    }
    cout << endl;

    // B PART --------------------------------
    Extended_queue q2;
    Stack s2;
    q2.append(4);
    q2.append(5);
    q2.append(6);
    moveQueueToStack(q2, s2);
    cout << "(b) Queue->Stack: ";
    while (!s2.empty())
    {
        s2.peek(x);
        cout << x << ' ';
        s2.pop();
    }
    cout << endl;

    // C PART --------------------------------
    Stack s3_from, s3_to;
    s3_from.push(7);
    s3_from.push(8);
    s3_to.push(9);
    moveStackToStackPreserveOrder(s3_from, s3_to);
    cout << "(c) Stack->Stack (preserve): ";
    while (!s3_to.empty())
    {
        s3_to.peek(x);
        cout << x << ' ';
        s3_to.pop();
    }
    cout << endl;

    // D PART --------------------------------
    Stack s4_from, s4_to;
    s4_from.push(10);
    s4_from.push(11);
    s4_to.push(12);
    moveStackToStackReverseOrder(s4_from, s4_to);
    cout << "(d) Stack->Stack (reverse): ";
    while (!s4_to.empty())
    {
        s4_to.peek(x);
        cout << x << ' ';
        s4_to.pop();
    }
    cout << endl;

    // E PART --------------------------------
    Extended_queue q5;
    q5.append(13);
    q5.append(14);
    reverseQueueWithStack(q5);
    cout << "(e) Queue reversed: ";
    while (!q5.empty())
    {
        q5.serve_and_retrieve(x);
        cout << x << ' ';
    }
    cout << endl;

    // F PART --------------------------------
    Stack s6;
    s6.push(15);
    s6.push(16);
    reverseStackWithQueue(s6);
    cout << "(f) Stack reversed: ";
    while (!s6.empty())
    {
        s6.peek(x);
        cout << x << ' ';
        s6.pop();
    }
    cout << endl;

    return EXIT_SUCCESS;
}
#include <iostream>
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

int main()
{
    Extended_queue test_queue;
    introduction();
    while (do_command(get_command(), test_queue))
        ;
    return EXIT_SUCCESS;
}

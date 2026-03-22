#include <iostream>
using namespace std;

// Recursive version
void move_recursive(int count, int start, int finish, int temp)
{
    if (count > 0)
    {
        move_recursive(count - 1, start, temp, finish);
        cout << "Move disk " << count << " from " << start << " to " << finish << "." << endl;
        move_recursive(count - 1, temp, finish, start);
    }
}

// Iterative (tail recursion removed) version
void move_iterative(int count, int start, int finish, int temp)
{
    int swap;
    while (count > 0)
    {
        move_iterative(count - 1, start, temp, finish);
        cout << "Move disk " << count << " from " << start << " to " << finish << "." << endl;
        count--;
        swap = start;
        start = temp;
        temp = swap;
    }
}

int main()
{
    int disks;
    const int MIN_DISKS = 1;
    const int MAX_DISKS = 15;
    while (true)
    {
        cout << "Enter number of disks (" << MIN_DISKS << "-" << MAX_DISKS << "): ";
        cin >> disks;
        if (cin.fail() || disks < MIN_DISKS || disks > MAX_DISKS)
        {
            cout << "Invalid input. Please enter an integer between " << MIN_DISKS << " and " << MAX_DISKS << "." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
            break;
    }

    cout << "\nRecursive version output:" << endl;
    move_recursive(disks, 1, 3, 2);

    cout << "\nIterative (tail recursion removed) version output:" << endl;
    move_iterative(disks, 1, 3, 2);

    return EXIT_SUCCESS;
}

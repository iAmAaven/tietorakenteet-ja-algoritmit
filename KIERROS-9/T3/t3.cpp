#include <iostream>
using namespace std;

int factorial(int n)
/*
Pre:  n is a nonnegative integer.
Post: Return the value of the factorial of n.
*/
{
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

// Global counters for statistics
long long move_count = 0;
long long call_count = 0;

void move(int count, int start, int finish, int temp)
{
    call_count++;
    if (count > 0)
    {
        move(count - 1, start, temp, finish);
        move_count++;
        move(count - 1, temp, finish, start);
    }
}

/*
Pre:  None.
Post: The simulation of the Towers of Hanoi has terminated.
*/
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

    move_count = 0;
    call_count = 0;

    // Timing start
    clock_t start_time = clock();
    move(disks, 1, 3, 2);
    clock_t end_time = clock();

    double elapsed_secs = double(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "\nDisks: " << disks << endl;
    cout << "Number of transfer orders: " << move_count << endl;
    cout << "Number of move() calls: " << call_count << endl;
    cout << "Elapsed time (s): " << elapsed_secs << endl;

    return EXIT_SUCCESS;
}
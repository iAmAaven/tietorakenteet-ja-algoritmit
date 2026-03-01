#include "stack.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

void introduction()
/*
Post: Prints a welcome message and brief description of the program.
*/
{
    cout << "Welcome to the Postfix Calculator!" << endl;
}

void instructions()
/*
Post: Prints instructions for using the calculator.
*/
{
    cout << "Commands:" << endl;
    cout << "  [?] Push a number to the stack" << endl;
    cout << "  [=] Print the top value of the stack" << endl;
    cout << "  [+] [-] [*] [/] [%] [^] Perform math operations" << endl;
    cout << "  [v] Square root" << endl;
    cout << "  [x] Exchange the top two values" << endl;
    cout << "  [s] Sum all values in the stack" << endl;
    cout << "  [a] Average of all values in the stack" << endl;
    cout << "  [q] Quit the program" << endl;
}

char get_command()
{
    char command;
    bool waiting = true;
    cout << "Select command and press <Enter>: ";

    while (waiting)
    {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
            command == '-' || command == '*' || command == '/' ||
            command == '%' || command == '^' || command == 'v' ||
            command == 'x' || command == 's' || command == 'a' || command == 'q')
            waiting = false;
        else
        {
            instructions();
            cout << "Please enter a valid command: ";
        }
    }
    return command;
}

void do_math_operation(char command, Stack &numbers, double &p, double &q)
{
    double result = 0;
    switch (command)
    {
    case '+':
        numbers.pop();
        result = q + p;
        break;
    case '-':
        numbers.pop();
        result = q - p;
        break;
    case '*':
        numbers.pop();
        result = q * p;
        break;
    case '/':
        numbers.pop();
        result = q / p;
        break;
    case '%':
        numbers.pop();
        if (p == 0)
            cout << "Error: Can't divide by zero" << endl;
        else
            result = fmod(q, p);
        break;
    case '^':
        numbers.pop();
        result = pow(q, p);
        break;
    case 'v':
        if (p < 0)
            cout << "Error: Can't take square root of negative number" << endl;
        else
            result = sqrt(p);
        break;
    default:
        break;
    }

    if (numbers.push(result) == overflow)
        cout << "Warning: Stack full, lost result" << endl;
}

bool do_command(char c, Stack &numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/
{
    double p, q;
    if (c == '?')
    {
        cout << "Enter a real number: " << flush;
        cin >> p;
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
    }
    else if (c == '=')
    {
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == 'v')
    {
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
        {
            numbers.pop();
            if (numbers.top(q) == underflow && c != 'v')
            {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }
            else
                do_math_operation(c, numbers, p, q);
        }
    }
    else if (c == 'x')
    {
        double first, second;
        if (numbers.top(first) == underflow)
            cout << "Stack empty" << endl;
        else
        {
            numbers.pop();
            if (numbers.top(second) == underflow)
            {
                cout << "Stack has just one entry" << endl;
                numbers.push(first);
            }
            else
            {
                numbers.pop();
                if (numbers.push(first) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
                if (numbers.push(second) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
    }
    else if (c == 's')
    {
        double sum = 0, value;
        int count = 0;
        while (numbers.top(value) != underflow)
        {
            numbers.pop();
            sum += value;
            ++count;
        }
        if (count == 0)
            cout << "Stack empty" << endl;
        else if (numbers.push(sum) == overflow)
            cout << "Warning: Stack full, lost result" << endl;
    }
    else if (c == 'a')
    {
        double sum = 0, value;
        int count = 0;
        while (numbers.top(value) != underflow)
        {
            numbers.pop();
            sum += value;
            ++count;
        }
        if (count == 0)
            cout << "Stack empty" << endl;
        else
        {
            double avg = sum / count;
            if (numbers.push(avg) == overflow)
                cout << "Warning: Stack full, lost result" << endl;
        }
    }
    else if (c == 'q')
    {
        cout << "Calculation finished.\n";
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
/*
Post: The program has executed simple arithmetic
      commands entered by the user, or in promptless mode if -p is not given.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/
{
    Stack stored_numbers;
    bool dc_mode = false;
    if (argc > 1 && string(argv[1]) == "-p")
        dc_mode = true;

    if (dc_mode == false)
    {
        introduction();
        instructions();
        while (do_command(get_command(), stored_numbers))
            ;
    }
    else
    {
        string line;
        while (getline(cin, line))
        {
            istringstream iss(line);
            string token;
            double value;
            bool valid = false;
            while (iss >> token)
            {
                try
                {
                    size_t idx;
                    value = stod(token, &idx);
                    if (idx == token.size())
                    {
                        if (stored_numbers.push(value) == overflow)
                            cout << "Warning: Stack full, lost number" << endl;
                        valid = true;
                        continue;
                    }
                }
                catch (...)
                {
                }

                char c = token[0];
                if (token.size() == 1 &&
                    (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' ||
                     c == '%' || c == '^' || c == 'v' || c == 'x' || c == 's' || c == 'a'))
                {
                    if (c == '=')
                    {
                        double top_value;
                        if (stored_numbers.top(top_value) == underflow)
                            cout << "Stack empty" << endl;
                        else
                            cout << top_value << endl;
                        valid = true;
                    }
                    else
                    {
                        do_command(c, stored_numbers);
                        valid = true;
                    }
                }
                else if (token.size() == 1 && c == 'q')
                {
                    return 0;
                }
            }
            double top_value;
            if (stored_numbers.top(top_value) == underflow)
                cout << "Stack empty" << endl;
            else
                cout << top_value << endl;
        }
    }
    return EXIT_SUCCESS;
}
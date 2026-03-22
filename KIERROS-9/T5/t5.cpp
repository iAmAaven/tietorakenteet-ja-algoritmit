#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

long long fib_call_count = 0;
long long max_depth = 0;

// Recursive Fibonacci with call counting and depth tracking
int fibonacci(int n, long long depth = 1)
{
    fib_call_count++;
    if (depth > max_depth)
        max_depth = depth;
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1, depth + 1) + fibonacci(n - 2, depth + 1);
}

int main()
{
    const int MIN_N = 0;
    const int MAX_N = 35; // Reasonable upper limit for console/Excel
    cout << left << setw(6) << "n" << setw(18) << "fib(n)" << setw(18) << "calls" << setw(18) << "max depth" << setw(18) << "time (s)" << endl;
    cout << string(70, '-') << endl;
    for (int n = MIN_N; n <= MAX_N; ++n)
    {
        fib_call_count = 0;
        max_depth = 0;
        clock_t start = clock();
        int result = fibonacci(n);
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << left << setw(6) << n << setw(18) << result << setw(18) << fib_call_count << setw(18) << max_depth << setw(18) << elapsed << endl;
        if (elapsed > 10.0)
            break; // Stop if calculation takes too long
    }
    return 0;
}

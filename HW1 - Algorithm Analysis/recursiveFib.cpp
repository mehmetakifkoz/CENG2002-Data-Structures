#include <iostream>

using namespace std;

int Fib(int n)
{
    if (n < 3)
        return 1;
    return Fib(n - 1) + Fib(n - 2);
}

int main()
{
    for (int i = 0; i < 100000000; i++)
    {
        Fib(9);
    }

    return 0;
}

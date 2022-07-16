#include <iostream>

using namespace std;

int Fib(int n)
{
    int a = 1, b = 1, temp;

    for (int i = 0; i < n - 2; i++)
    {
        temp = a;
        a = b;
        b += temp;
    }

    return b;
}

int main()
{
    // for (int i = 0; i < 1000000000; i++)
    // {
    //     Fib(9);
    // }

    cout << Fib(9);

    return 0;
}

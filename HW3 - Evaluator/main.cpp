#include <iostream>
#include "lstack.h"
using namespace std;

int EvaluatePostfix(string exp);
int Perform(char operation, int op1, int op2);

int main(int argc, char const *argv[])
{
    cout << EvaluatePostfix("2 3 * 5 4 * + 9 -");
    return 0;
}

int EvaluatePostfix(string exp)
{
    LStack<int> S;
    for (int i = 0; i < exp.length() - 1; i++)
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            S.push(exp[i]);
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {
            int op2 = S.pop();
            int op1 = S.pop();
            int res = Perform(exp[i], op1, op2);
            S.push(res);
        }
    }
    return S.topValue();
}

int Perform(char operation, int op1, int op2)
{
    if (operation == '+')
        return op1 + op2;
    else if (operation == '-')
        return op1 - op2;
    else if (operation == '*')
        return op1 * op2;
    else if (operation == '/')
        return op1 / op2;
}

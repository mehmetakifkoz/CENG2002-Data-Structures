// HW #2 Mehmet Akif KOZ 192010010023

// Dynamic 2D array in C++ using new and delete operators
#include <iostream>
using namespace std;
template <typename E>
class Array2D
{
private:
    E **p; // pointer for 2d array
    int r; // number of rows
    int c; // number of columns

public:
    Array2D(int rows, int columns)
    {
        r = rows;
        c = columns;
        p = new E *[r];
        for (int i = 0; i < r; i++)
            p[i] = new E[c];
    }

    void del()
    {
        for (int i = 0; i < r; i++)
            delete p[i];
        delete p;
    }

    void setValue(int row, int column, E value)
    {
        p[row][column] = value;
    };

    E getValue(int row, int column)
    {
        return p[row][column];
    }

    void print()
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << p[i][j] << " ";
            }
            cout << endl;
        }
    };
};

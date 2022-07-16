// Dynamic 2D array in C++ using new and delete operators
#include <iostream>
#include <time.h> // Used by timing functions
using namespace std;

// Timing variables and functions
unsigned tstart = 0; // Time at beginning of timed section

// Initialize the program timer
void Settime() { tstart = (unsigned)clock(); }

// Return the elapsed time since the last call to Settime
double Gettime()
{
    unsigned tcurr = (unsigned)clock();
    return (double)(tcurr - tstart) / (double)CLOCKS_PER_SEC;
}

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

    int getNumberOfRows()
    {
        return r;
    };

    int getNumberOfColumns()
    {
        return c;
    };

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

    void setRandom()
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                p[i][j] = rand();
            }
        }
    };

    void sort(void (*method)(E *array, int n))
    {
        for (int i = 0; i < r; i++)
        {
            method(p[i], c);
        }
    }

    double getRandomTime(void (*method)(E *array, int n))
    {
        this->setRandom();
        Settime();
        this->sort(method);
        return (Gettime() / r) * 1000; // average in milliseconds
    }

    double getSortedTime(void (*method)(E *array, int n), void (*sortMethod)(E *array, int n))
    {
        this->setRandom();
        this->sort(sortMethod);
        Settime();
        this->sort(method);
        return (Gettime() / r) * 1000; // average in milliseconds
    }
};

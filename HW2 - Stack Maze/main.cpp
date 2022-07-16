// HW #2 Mehmet Akif KOZ 192010010023

#include <iostream>
#include <unistd.h>
#include "LStack.h"
#include "Array2D.h"
using namespace std;

struct Location
{
    int r; // row
    int c; // column
};

int getNumberOfRows(FILE *fp);
int getNumberOfColumns(FILE *fp);
void setMaze(FILE *fp, Array2D<char> maze);

void goNorth(Location &cl, LStack<char> &oh);
void goSouth(Location &cl, LStack<char> &oh);
void goWest(Location &cl, LStack<char> &oh);
void goEast(Location &cl, LStack<char> &oh);
char goBack(Location &cl, LStack<char> &oh);

int main()
{
    FILE *fp = fopen("maze_sample.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open the file for reading!");
        exit(1);
    }

    int rows = getNumberOfRows(fp);
    int columns = getNumberOfColumns(fp);
    Array2D<char> maze(rows, columns);
    setMaze(fp, maze);

    Location cl; // Current Location
    cl.r = 0;
    cl.c = 0;
    LStack<char> oh; // Operation History

    maze.print();
    cout << endl;
    usleep(2000000);

    while (maze.getValue(cl.r, cl.c) != '0') // setting maze enterance
    {
        goEast(cl, oh);
    }
    maze.setValue(cl.r, cl.c, '+');
    maze.print();
    cout << endl;
    usleep(2000000);

    while (cl.r != rows - 1)
    {
        if (cl.r > 0 && maze.getValue(cl.r - 1, cl.c) == '0')
        {
            goNorth(cl, oh);
            maze.setValue(cl.r, cl.c, '+');
        }
        else if (cl.r < rows - 1 && maze.getValue(cl.r + 1, cl.c) == '0')
        {
            goSouth(cl, oh);
            maze.setValue(cl.r, cl.c, '+');
        }
        else if (cl.c > 0 && maze.getValue(cl.r, cl.c - 1) == '0')
        {
            goWest(cl, oh);
            maze.setValue(cl.r, cl.c, '+');
        }
        else if (cl.c < columns - 1 && maze.getValue(cl.r, cl.c + 1) == '0')
        {
            goEast(cl, oh);
            maze.setValue(cl.r, cl.c, '+');
        }
        else
        {
            maze.setValue(cl.r, cl.c, '-');
            goBack(cl, oh);
        }
        maze.print();
        cout << endl;
        usleep(2000000);
    }

    fclose(fp);
    return 0;
}

int getNumberOfRows(FILE *fp)
{
    rewind(fp);
    int numberOfRows = 0;
    int c = fgetc(fp);
    while (c != EOF)
    {
        c = fgetc(fp);
        if (c == '\n')
        {
            numberOfRows++;
        }
    }
    return numberOfRows;
}

int getNumberOfColumns(FILE *fp)
{
    rewind(fp);
    int numberOfColumns = 0;
    char c = fscanf(fp, "%c ", &c);
    while (c != EOF)
    {
        c = fscanf(fp, "%c ", &c);
        numberOfColumns++;
    }
    return numberOfColumns / getNumberOfRows(fp);
}

void setMaze(FILE *fp, Array2D<char> maze)
{
    int rows = getNumberOfRows(fp);
    int columns = getNumberOfColumns(fp);
    int i = 0;
    int j = 0;
    rewind(fp);
    char c;
    fscanf(fp, "%c ", &c);
    while (i < columns)
    {
        if (j == rows)
        {
            i++;
            j = 0;
            continue;
        }
        maze.setValue(i, j, c);
        j++;
        fscanf(fp, "%c ", &c);
    }
}

void goNorth(Location &cl, LStack<char> &oh)
{
    cl.r--;
    oh.push('N');
}

void goSouth(Location &cl, LStack<char> &oh)
{
    cl.r++;
    oh.push('S');
}

void goWest(Location &cl, LStack<char> &oh)
{
    cl.c--;
    oh.push('W');
}

void goEast(Location &cl, LStack<char> &oh)
{
    cl.c++;
    oh.push('E');
}

char goBack(Location &cl, LStack<char> &oh)
{
    char deo = oh.pop(); // deo => deadEndOperation
    if (deo == 'N')
    {
        cl.r++;
    }
    else if (deo == 'S')
    {
        cl.r--;
    }
    else if (deo == 'W')
    {
        cl.c++;
    }
    else if (deo == 'E')
    {
        cl.c--;
    }
    return deo;
}

#include <iostream>
#include <climits>
using namespace std;
#define V 10

// Node with labe and weight
class Node
{
public:
    char label; // Label for this node
    int weight; // The connection weight
    Node *next; // Pointer to next node
    // Constructors
    Node(const char &label, const int &weight, Node *next = NULL)
    {
        this->label = label;
        this->weight = weight;
        this->next = next;
    }
    Node(Node *nextval = NULL)
    {
        next = nextval;
    }
};

void setMatrix(int matrix[V][V]);
void printMatrix(int matrix[V][V]);

Node *generateList(int matrix[V][V]);
void printList(Node *list);

void help(int start, bool visited[V], int matrix[V][V]);
bool isConnected(int matrix[V][V]);

int getNumberOfClusters(int matrix[V][V]);
bool *getClusterStart(int matrix[V][V]);
int getClusterSize(int start, int matrix[V][V]);
void printClusterSize(int matrix[V][V]);

void BFS(int start, bool visited[V], int matrix[V][V]);
void printBFS(int matrix[V][V]);

void DFS(int start, bool visited[V], int matrix[V][V]);
void printDFS(int matrix[V][V]);

// minimum-spanning tree
int minCost(int cost[], bool visited[]);
void printMST(int parent[], int graph[V][V]);
void prim(int graph[V][V]);

// shortest path
int minimumDist(int dist[], bool visited[]);
void printSolution(int dist[], int pred[]);
void dijkstra(int graph[V][V], int start);

int main()
{
    cout << "******************************** Adjacency Matrix ********************************";
    cout << endl
         << endl
         << endl;
    int matrix[V][V];
    setMatrix(matrix);
    printMatrix(matrix);

    cout << "******************************************* Adjacency List *******************************************" << endl;
    Node *list = generateList(matrix);
    printList(list);
    cout << endl;
    cout << endl;

    string connected = isConnected(matrix) ? "yes" : "no";
    cout << "Is the generated graph connected? " << connected << endl;
    if (!isConnected(matrix))
    {
        printf("The graph has %d clusters.\n", getNumberOfClusters(matrix));
        printClusterSize(matrix);
    }
    cout << endl;
    cout << endl;

    printBFS(matrix);
    cout << endl;

    printDFS(matrix);
    cout << endl;

    cout << "**************** Minimum-Spanning Tree ****************" << endl;
    prim(matrix);
    cout << endl;
    cout << endl;

    cout << "******************** Shortest Path ********************" << endl;
    dijkstra(matrix, 0);
    cout << endl;
    cout << endl;

    return 0;
}

void setMatrix(int matrix[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
                continue;
            }
            matrix[i][j] = ((rand() % 100) < 60) ? ((rand() % 10) + 1) : 0;
            // 60% probability to fill the weight with a random number in range 1-10
        }
    }
}

void printMatrix(int matrix[V][V])
{
    for (int i = 0; i < V; i++)
        cout << '\t' << (char)(i + 65);
    cout << endl
         << endl
         << endl;
    for (int i = 0; i < V; i++)
    {
        cout << (char)(i + 65);
        for (int j = 0; j < V; j++)
        {
            cout << '\t' << matrix[i][j];
        }
        cout << endl
             << endl
             << endl;
    }
}

Node *generateList(int matrix[V][V])
{
    Node *curr; // Access to current element
    static Node list[V];

    for (int i = 0; i < V; i++)
    {
        list[i].label = (char)(i + 65);
        list[i].weight = 0;
        list[i].next = NULL;
        curr = &list[i];

        for (int j = 0; j < V; j++)
        {
            if (matrix[i][j] == 0)
                continue;
            curr = curr->next = new Node((char)(j + 65), matrix[i][j], NULL);
        }
    }

    return list;
}

void printList(Node list[V])
{
    Node *curr; // Access to current element

    for (int i = 0; i < V; i++)
    {
        cout << list[i].label;
        struct Node *curr = &list[i];
        while (curr != NULL)
        {
            if (curr->weight != 0)
                printf(" ---%d---> %c", curr->weight, curr->label);
            curr = curr->next;
        }
        cout << endl;
    }
}

void help(int start, bool visited[V], int matrix[V][V])
{
    // Set current node as visited
    visited[start] = true;

    // For every node of the graph
    for (int i = 0; i < V; i++)
    {
        // If some node is adjacent to the current node
        // and it has not already been visited
        if (matrix[start][i] != 0 && (!visited[i]))
        {
            help(i, visited, matrix);
        }
    }
}

bool isConnected(int matrix[V][V])
{
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
        // reset visited status
        for (int j = 0; j < V; j++)
        {
            visited[j] = false;
        }

        // search for connection
        help(i, visited, matrix);

        for (int k = 0; k < V; k++)
        {
            // if there is any node
            // that is not visisted
            if (!visited[k])
            {
                return false;
            }
        }
    }
    return true;
}

int getNumberOfClusters(int matrix[V][V])
{
    int count = 0;
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            count++;
        }
        help(i, visited, matrix);
    }
    return count;
}

bool *getClusterStart(int matrix[V][V])
{
    static bool clusterStart[V];
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        clusterStart[i] = false;
        visited[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            clusterStart[i] = true;
        }
        help(i, visited, matrix);
    }
    return clusterStart;
}

int getClusterSize(int start, int matrix[V][V])
{
    int size = 0;
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    help(start, visited, matrix);
    for (int i = 0; i < V; i++)
    {
        if (visited[i])
        {
            size++;
        }
    }
    return size;
}

void printClusterSize(int matrix[V][V])
{
    bool *clusterStart = getClusterStart(matrix);
    for (int i = 0; i < V; i++)
    {
        if (clusterStart[i] == true)
        {
            cout << (char)(i + 65) << ": " << getClusterSize(i, matrix) << endl;
        }
    }
}

// breadth first search
void BFS(int start, bool visited[V], int matrix[V][V])
{
    cout << (char)(start + 65) << ' ';

    // Set current node as visited
    visited[start] = true;

    // For every node of the graph
    for (int i = 0; i < V; i++)
    {
        // If some node is adjacent to the current node
        // and it has not already been visited
        if (matrix[start][i] != 0 && (!visited[i]))
        {
            DFS(i, visited, matrix);
        }
    }
}

void printBFS(int matrix[V][V])
{
    cout << "Breadth First Search" << endl;

    bool *clusterStart = getClusterStart(matrix);
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            visited[j] = false;
        }
        if (clusterStart[i] == true)
        {
            DFS(i, visited, matrix);
            cout << endl;
        }
    }

    cout << endl;
}

// depth first search
void DFS(int start, bool visited[V], int matrix[V][V])
{
    // Set current node as visited
    visited[start] = true;

    // For every node of the graph
    for (int i = 0; i < V; i++)
    {
        // If some node is adjacent to the current node
        // and it has not already been visited
        if (matrix[start][i] != 0 && (!visited[i]))
        {
            DFS(i, visited, matrix);
        }
    }

    cout << (char)(start + 65) << ' ';
}

void printDFS(int matrix[V][V])
{
    cout << "Depth First Search" << endl;

    bool *clusterStart = getClusterStart(matrix);
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            visited[j] = false;
        }
        if (clusterStart[i] == true)
        {
            DFS(i, visited, matrix);
            cout << endl;
        }
    }

    cout << endl;
}

int minCost(int cost[], bool visited[])
{
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false && cost[v] < min)
        {
            min = cost[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int parent[], int graph[V][V])
{
    cout << "Edge \t\tWeight\n";
    for (int i = 1; i < V; i++)
    {
        char v1 = parent[i] + 65;
        char v2 = i + 65;
        cout << v1 << " --> " << v2 << " \t" << graph[i][parent[i]] << " \n";
    }
}

void prim(int graph[V][V])
{
    int parent[V];
    int cost[V];
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
        cost[i] = INT_MAX; //as infinite
        parent[i] = -1;
        visited[i] = false;
    }
    cost[0] = 0;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minCost(cost, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && visited[v] == false && graph[u][v] < cost[v])
            {
                parent[v] = u;
                cost[v] = graph[u][v];
            }
    }

    printMST(parent, graph);
}

int minimumDist(int dist[], bool visited[])
{
    int min = INT_MAX;
    int index;
    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false && dist[v] <= min)
        {
            min = dist[v];
            index = v;
        }
    }
    return index;
}

void printSolution(int dist[], int pred[])
{
    int j;
    cout << "Vertice \t Distance \t Path\n";
    for (int i = 0; i < V; i++)
    {

        if (i != 0)
        {
            char c = 65 + i;
            cout << c << "\t\t" << dist[i] << "\t\t";
            cout << c;
            j = i;
            do
            {
                j = pred[j];
                char p = 65 + j;
                cout << "<--" << p;
            }
            while (j != 0);
        }
        cout << endl;
    }
}

void dijkstra(int graph[V][V], int start)
{
    int dist[V];
    bool visited[V];
    int pred[V];
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
        pred[i] = INT_MAX;
    }
    dist[start] = 0;
    pred[start] = 0;

    for (int c = 0; c < V; c++)
    {
        int u = minimumDist(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
        {

            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }
    printSolution(dist, pred);
}

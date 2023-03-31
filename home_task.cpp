#include <iostream>
#include <vector>

using namespace std;

bool isValidEdge(int u, int v, vector<bool> inMST)
{
    if (u == v)
        return false;
    if (inMST[u] == false && inMST[v] == false)
        return false;
    else if (inMST[u] == true && inMST[v] == true)
        return false;
    return true;
}

void Prim(vector < vector<int> > cost, int v)
{
    vector<bool> inMST(v, false);
    inMST[0] = true;

    int edge_count = 0, mincost = 0;
    while (edge_count < v - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (cost[i][j] < min) {
                    if (isValidEdge(i, j, inMST)) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            printf("Edge %d:(%d, %d) cost: %d \n",
                edge_count++, a, b, min);
            mincost = mincost + min;
            inMST[b] = inMST[a] = true;
        }
    }
    printf("\nMinimum cost= %d \n", mincost);
}

int main()
{
    vector < vector<int> > cost = {
        { INT_MAX, 2, INT_MAX, 6, INT_MAX },
        { 2, INT_MAX, 3, 8, 5 },
        { INT_MAX, 3, INT_MAX, INT_MAX, 7 },
        { 6, 8, INT_MAX, INT_MAX, 9 },
        { INT_MAX, 5, 7, 9, INT_MAX },
    };

    int v = cost.size();

    Prim(cost, v);
}
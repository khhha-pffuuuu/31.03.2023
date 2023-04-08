#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


class Graph
{
public:
    vector < vector < vector < int > > > Edges;
    int Vertecies;

    Graph(vector < vector < vector < int > > > input_edges, int v) {
        Edges = input_edges;
        Vertecies = input_edges.size();
    }
};


int find_wrong_index(vector < int > parent, vector < int > dist)
{
    int v = parent.size();
    int wrong_index = -1;

    vector < bool > isChecked(v, false);

    for (int i = 0; i < v; i++) {
        if (parent[i] != -1) {
            if (!(isChecked[parent[i]] == true && isChecked[i] == true)) {
                isChecked[parent[i]] = true;
                isChecked[i] = true;
            }
            else {
                if (dist[parent[i]] < dist[i]) {
                    wrong_index = i;
                }
                else if (dist[parent[i]] > dist[i]) {
                    wrong_index = parent[i];
                }
                else {
                    if (parent[i] != parent[i - 1]) {
                        wrong_index = i;
                    }
                    else {
                        wrong_index = parent[i];
                    }
                }
            }
        }
        else {
            wrong_index = i;
        }
    }

    return wrong_index;
}


void print(vector < int > parent, vector < int > dist)
{
    int v = parent.size();
    int wrong_index = find_wrong_index(parent, dist);
    int summary_weight = 0;

    for (int i = 0; i < v; i++) {
        if (i != wrong_index) {
            printf("%d - %d, weight is %d\n", parent[i], i, dist[i]);
            summary_weight += dist[i];
        }
    }

    printf("\nSummary weight is %d\n", summary_weight);
}


void Prim(Graph graph)
{
    int v = graph.Vertecies;

    priority_queue < pair <int, int> > pq;
    vector <int> parent(v, -1);
    vector <int> dist(v, INT_MAX);

    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();

        for (int i = 1; i < graph.Edges[u].size(); i++) {
            int v = graph.Edges[u][i][0];
            int w = graph.Edges[u][i][1];
            if (w < dist[v]) {
                dist[v] = w;
                pq.push(make_pair(v, w));
                parent[v] = u;
            }
        }
    }

    print(parent, dist);
}

int main()
{
    Graph graph({
        { {0, 0}, {1, 1}, {2, 1} },
        { {1, 0}, {0, 1}, {2, 1} },
        { {2, 0}, {0, 1}, {1, 1} }
        }, 3);

    Prim(graph);
}
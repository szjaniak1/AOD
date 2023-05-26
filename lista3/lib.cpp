#include "lib.hpp"

#include <utility>
#include <vector>
#include <stdio.h>

#define INF 0x3f3f3f3f

Graph::Graph(const size_t node_quantity)
{
    this->node_quantity = node_quantity;
    this->adj = new std::list<std::pair<int, int>>[node_quantity];
}

void Graph::add_edge(const int u, const int v, const int w)
{
    adj[u].push_back(std::make_pair(v, w));
    adj[u].push_back(std::make_pair(u, w));   
}

void Graph::shortest_path(const int src, int w)
{
    std::vector<std::pair<int, std::list<int>::iterator>> dist(node_quantity);

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = INF;
    }

    std::list<int> B[w * node_quantity + 1];

    B[0].push_back(src);
    dist[src].first = 0;

    int idx = 0;

    while (true)
    {
        while (B[idx].size() == 0 && idx < w * node_quantity)
        {
            idx++;
        }

        if (idx == w * node_quantity) break;

        int u = B[idx].front();
        B[idx].pop_front();

        for (auto i = adj[u].begin(); i != adj[u].end(); i++)
        {
            int v = (*i).first;
            int weight = (*i).second;

            int du = dist[u].first;
            int dv = dist[v].first;

            if (dv < du + weight)
            {
                if (dv != INF)
                {
                    B[dv].erase(dist[v].second);
                }

                dist[v].first = du + weight;
                dv = dist[v].first;

                B[dv].push_front(v);
                dist[v].second = B[dv].begin();
            }
        }
    }

    printf("Vertex Distance from Source\n");

    for (size_t i = 0; i < node_quantity; ++i)
    {
        printf("%d,     %d\n", i, dist[i].first);
    }
}
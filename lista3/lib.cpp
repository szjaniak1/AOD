#include "lib.hpp"

#include <utility>
#include <vector>
#include <stdio.h>

#define INF 0x3f3f3f3f

Graph::Graph(const size_t node_quantity, const size_t max_weight)
{
    this->node_quantity = node_quantity;
    this->max_weight = max_weight;
    this->adj = new std::list<std::pair<size_t, size_t>>[node_quantity];
}

void Graph::add_edge(const size_t vert1, const size_t vert2, const size_t weight)
{
    if (weight > this->max_weight) this->max_weight = weight;
    adj[vert1].push_back(std::make_pair(vert2, weight));
    adj[vert2].push_back(std::make_pair(vert1, weight));   
}

size_t Graph::min_distance(const std::vector<std::pair<int, std::list<size_t>::iterator> > dist, const bool visited[])
{
    size_t min = INF, min_index;

    for (size_t v = 0; v < node_quantity; v++)
    {
        if (visited[v] == false && dist[v].first <= min)
        {
            min = dist[v].first, min_index = v;
        }
    }

    return min_index;
}

void Graph::dijkstra_classic_ss(const size_t src)
{
    std::vector<std::pair<int, std::list<size_t>::iterator> > dist(node_quantity);
    bool visited[node_quantity];

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = INF;
        visited[i] = false;
    }

    dist[src].first = 0;

    for (size_t count = 0; count < node_quantity - 1; count++)
    {
        size_t u = min_distance(dist, visited);

        visited[u] = true;

        for (size_t v = 0; v < node_quantity; v++)
        {
            //if (!visited[v] && adj[u].)
        }
    }
}

void Graph::dijkstra_classic_p2p(const int start, const int goal)
{

}

void Graph::dial_ss(const int src)
{
    std::vector<std::pair<int, std::list<size_t>::iterator> > dist(node_quantity);

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = INF;
    }

    std::list<size_t> B[max_weight * node_quantity + 1];

    B[0].push_back(src);
    dist[src].first = 0;

    size_t idx = 0;

    while (true)
    {
         while (B[idx].size() == 0 && idx < max_weight * node_quantity)
            idx++;
 
        if (idx == max_weight * node_quantity)
            break;
 
        int u = B[idx].front();
        B[idx].pop_front();

        for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
 
            int du = dist[u].first;
            int dv = dist[v].first;

            if (dv > du + weight)
            {
                if (dv != INF)
                    B[dv].erase(dist[v].second);
 
                dist[v].first = du + weight;
                dv = dist[v].first;

                B[dv].push_front(v);

                dist[v].second = B[dv].begin();
            }
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < node_quantity; ++i)
        printf("%d     %d\n", i, dist[i].first);
}

void Graph::dial_p2p(const int start, const int goal)
{
    int start = start - 1;
    int goal = goal - 1;
    std::vector<std::pair<int, std::list<size_t>::iterator> > dist(node_quantity);

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = INF;
    }

    std::list<size_t> B[max_weight * node_quantity + 1];

    dist[start].first = 0;
    B[0].push_back(start);

}
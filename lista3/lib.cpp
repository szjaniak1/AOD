#include "lib.hpp"

#include <utility>
#include <queue>
#include <functional>
#include <algorithm>
#include <stdio.h>

#define INF 0x3f3f3f3f

typedef std::pair<size_t, size_t> pair;

Graph::Graph(const size_t quantity, const size_t weight)
{
    this->node_quantity = quantity;
    this->max_weight = weight;
    this->adj = new std::list<pair>[node_quantity];
}

auto Graph::add_edge(const size_t vert1, const size_t vert2, const size_t weight) -> void
{
    if (weight > this->max_weight) this->max_weight = weight;
    adj[vert1].push_back(std::make_pair(vert2, weight));
    adj[vert2].push_back(std::make_pair(vert1, weight));   
}

auto Graph::dijkstra_classic_ss(const size_t src) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >
{
    std::vector<std::pair<size_t, std::list<size_t>::iterator> > dist(node_quantity);
    std::priority_queue<pair, std::vector<pair>, std::greater<pair> > Q;

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = INF;
    }
    
    Q.push(std::make_pair(0, src));
    dist[src].first = 0;

    while (!Q.empty())
    {
        auto u = Q.top().second;
        Q.pop();

        std::list<pair>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            auto v = (*i).first;
            auto weight = (*i).second;

            size_t du = dist[u].first;
            size_t dv = dist[v].first;

            if (dv > du + weight)
            {
                dist[v].first = du + weight;
                dv = dist[v].first;
                Q.push(std::make_pair(dv, v));
            }
        }
    }


    printf("Vertex Distance from Source\n");
    for (size_t i = 0; i < node_quantity; ++i)
        printf("%zu \t\t %zu\n", i, dist[i].first);

    return dist;
}

auto Graph::dijkstra_classic_p2p(const int start, const int goal) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >
{

}

auto Graph::dial_ss(const size_t src) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >
{
    std::vector<std::pair<size_t, std::list<size_t>::iterator> > dist(node_quantity);

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
 
        auto u = B[idx].front();
        B[idx].pop_front();

        for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            auto v = (*i).first;
            auto weight = (*i).second;
 
            auto du = dist[u].first;
            auto dv = dist[v].first;

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
    for (size_t i = 0; i < node_quantity; ++i)
        printf("%zu     %zu\n", i, dist[i].first);

    return dist;
}

auto Graph::dial_p2p(const int start, const int goal) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >
{
    // int start = start - 1;
    // int goal = goal - 1;
    // std::vector<std::pair<int, std::list<size_t>::iterator> > dist(node_quantity);

    // for (size_t i = 0; i < node_quantity; i++)
    // {
    //     dist[i].first = INF;
    // }

    // std::list<size_t> B[max_weight * node_quantity + 1];

    // dist[start].first = 0;
    // B[0].push_back(start);

    // std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
    // heap.push({0, start});

    // while (!heap.empty())
    // {
    //     auto [dist, node] = heap.top();
    //     heap.pop();
    //     if (node == goal)
    //     {
    //         return dist;
    //     }
    //     if (auto d = dist[node]; d.has_value() && dist > d.value())
    //     {
    //         continue;
    //     }
    //     B[dist].erase(std::remove(B[dist].begin(), B[dist].end(), node), buckets[dist].end());
    //     distances[node] = dist;
    //     for (auto [neighbor, weight] : adj[node])
    //     {
    //         int new_dist = dist + weight;
    //         if (auto d = distances[neighbor]; d.has_value() && new_dist >= d.value())
    //         {
    //             continue;
    //         }
    //         buckets[new_dist].push_back(neighbor);
    //         heap.push({new_dist, neighbor});
    //     }
    // }
    // return std::nullopt;

}

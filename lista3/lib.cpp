#include "lib.hpp"

#include <utility>
#include <queue>
#include <algorithm>
#include <stdio.h>

#define INF 0x3f3f3f3f

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

auto Graph::dijkstra_classic_ss(const size_t src) -> distances
{
    distances dist(node_quantity);
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

    return dist;
}

auto Graph::dijkstra_classic_p2p(const size_t start, const size_t goal) -> size_t
{
    auto dist = dijkstra_classic_ss(start);

    return dist[goal].first;
}

auto Graph::dial_ss(const size_t src) -> distances
{
    distances dist(node_quantity);

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

    return dist;
}

auto Graph::dial_p2p(const size_t start, const size_t goal) -> size_t
{
    auto dist = dial_ss(start);

    return dist[goal].first;
}

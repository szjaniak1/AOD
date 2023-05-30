#include "lib.hpp"

#include <utility>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <fstream>
#include <string.h>

#define INF 0x3f3f3f3f

struct bucketsradix
{
    std::list<int32_t> v_list;
    size_t range_a;
    size_t range_b;
};

Graph::Graph(const size_t quantity, const size_t weight)
{
    this->node_quantity = quantity;
    this->max_weight = weight;
    this->adj = new std::list<pair>[node_quantity];
}

auto Graph::add_edge(const int32_t vert1, const int32_t vert2, const size_t weight) -> void
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

            auto du = dist[u].first;
            auto dv = dist[v].first;

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

auto Graph::dijkstra_classic_p2p(const size_t start, const size_t goal) -> int32_t
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

    std::list<int32_t> B[max_weight * node_quantity + 1];

    B[0].push_back((int32_t)src);
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

auto Graph::dial_p2p(const size_t start, const size_t goal) -> int32_t
{
    auto dist = dial_ss(start);

    return dist[goal].first;
}

auto Graph::radix_heap_ss(const size_t src) -> std::vector<int>
{
    std::vector<int> dist(node_quantity);

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
    }

    dist[src] = 0;
    int no_buck = log2(std::numeric_limits<int>::max());

    std::vector<bucketsradix> buckets(no_buck);

    for (int i = 0; i < no_buck; i++)
    {
        buckets[i].range_a = floor(pow(2, i - 1));
        buckets[i].range_b = pow(2, i) - 1;
    }

    buckets[0].v_list.push_front(src);
    long unsigned long idx;

    while (true)
    {
        idx = 0;
        while (buckets[idx].v_list.size() == 0 && idx < buckets.size())
        {
            idx++;
        }

        if (idx == buckets.size()) break;

        int u = buckets[idx].v_list.front();

        if (buckets[idx].range_b - buckets[idx].range_a + 1 == 1)
        {
            buckets[idx].v_list.pop_front();
        }
        else
        {
            int minv;
            int mindist = std::numeric_limits<int>::max();

            for (auto v = buckets[idx].v_list.begin(); v != buckets[idx].v_list.end(); ++v)
            {
                if (dist[*v] < mindist)
                {
                    mindist = dist[*v];
                    minv = *v;
                }
            }

            u = minv;
            for (auto i = buckets[idx].v_list.begin(); i != buckets[idx].v_list.end(); ++i)
            {
                if (*i < u)
                {
                    buckets[idx].v_list.erase(i);
                    break;
                }
            }

            for(int i = 0; i < idx; i++)
            {
                buckets[i].range_a = mindist +  floor(pow(2, i - 1));
                buckets[i].range_b =  mindist + pow(2, i) - 1;
            }
            buckets[idx -1].range_b = buckets[idx].range_b;
            //determine the correct buckets
            for(auto v = buckets[idx].v_list.begin(); v != buckets[idx].v_list.end(); ++v)
            {
                for(int i = idx - 1; i >= 0; i--)
                {
                    if(dist[*v] >= buckets[i].range_a && dist[*v] <= buckets[i].range_b)
                    {
                        buckets[i].v_list.push_front(*v);
                        break;
                    }
                }
            }
            // mark bucket as empty
            buckets[idx].range_a = 1;
            buckets[idx].range_b = 0;
            buckets[idx].v_list.clear();
        }

        for(auto i = adj[u].begin(); i != adj[u].end(); i++)
        {
            int v = (*i).first;
            int weight = (*i).second;
            int dv = dist[v];
            int du = dist[u];

            if(dv > du + weight)
            {
                if (dv != std::numeric_limits<int>::max())
                {
                    int tmp = 0;
                    // check where was v before
                    while (!(buckets[tmp].range_a <= dv && buckets[tmp].range_b >= dv))
                        tmp++;
                    // remove from prev bucket
                    for(auto j = buckets[tmp].v_list.begin(); j != buckets[tmp].v_list.end(); j++)
                    {
                        if(*j == v)
                        {
                            buckets[tmp].v_list.erase(j);
                            break;
                        }
                    }
                }

                int b = 0;
                // check where to put v
                while (!(buckets[b].range_a <= du + weight && buckets[b].range_b >= du + weight))
                    b++;

                dist[v] = du + weight;    // new dist
                buckets[b].v_list.push_front(v);    // new bucket
            }
        }
    }

    return dist;
}

auto Graph::radix_heap_p2p(const size_t start, const size_t goal) -> int32_t
{
    const auto dist = radix_heap_ss(start);
    return dist[goal];
}

auto Graph::create_graph_from_path(char *path) -> void
{
    std::fstream file(path);
    std::string text;

    while (getline(file, text))
    {
        char *p;
        char *line = new char [text.length() + 1];

        strcpy(line, text.c_str());
        p = strtok(line, " ");

        if (strcmp(p, "a") == 0)
        {
            p = strtok(NULL, " ");
            int src = atoi(p);
            p = strtok(NULL, " ");
            int dest = atoi(p);
            p = strtok(NULL, " ");
            int weight = atoi(p);

            if(weight > max_weight)
            {
                max_weight = weight;
            }
            add_edge(src - 1, dest - 1, weight);
        }
        else if (strcmp(p, "p") == 0)
        {
            p = strtok(NULL, " ");
            p = strtok(NULL, " ");
            node_quantity = atoi(p);
        }
        delete[] line;
    }
    file.close();
}

auto Graph::get_sources(char *path, int mode) -> std::list<int32_t>
{
    std::fstream file(path);
    std::list<int32_t> src;
    std::string text;

    while (getline(file, text))
    {
        char* p;
        char* line = new char [text.length() + 1];
        strcpy(line, text.c_str());
        p = strtok(line, " ");

        if(mode == 1)
        {
            if(strcmp(p, "s") == 0)
            {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        else if (mode == 2)
        {
            if(strcmp(p, "q") == 0)
            {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        delete[] line;
    }
    file.close();
    return src;
}

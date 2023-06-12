#include "lib.hpp"

#include <utility>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <array>

#define INF 0x3f3f3f3f

template <typename key_t, typename val_t>
struct RadixHeap
{
    static constexpr int bit = sizeof(key_t) * 8;
    std::array<std::vector<std::pair<key_t, val_t> >, bit > vs;

    size_t sz;
    key_t last;

    RadixHeap() : sz(0), last(0) {}

    bool empty() const { return sz == 0; };
    size_t size() const { return sz; }

    inline int getbit(int a) const
    {
        return a ? bit - __builtin_clz(a) : 0;
    }

    inline int getbit(int64_t a) const
    {
        return a ? bit - __builtin_clzll(a) : 0;
    }

    void push(const key_t &key, const val_t &val)
    {
        sz++;
        vs[getbit(key ^ last)].emplace_back(key, val);
    }

    std::pair<key_t, val_t> pop()
    {
        if (vs[0].empty())
        {
            int idx = 1;
            while (vs[idx].empty()) 
            {
                idx++;
            }

            last = std::min_element(vs[idx].begin(), vs[idx].end())->first;

            for (auto &p : vs[idx])
            {
                vs[getbit(p.first ^ last)].emplace_back(p);
            }

            vs[idx].clear();
        }

        --sz;
        auto res = vs[0].back();
        vs[0].pop_back();

        return res;
    }
};

Graph::Graph(const size_t quantity) : node_quantity(quantity), adj(quantity){}

auto Graph::get_size(void) -> size_t
{   
    node_quantity = adj.size();
    return node_quantity;
}

auto Graph::add_edge(const int32_t vert1, const int32_t vert2, const size_t weight) -> void
{
    if (weight > this->max_weight) this->max_weight = weight;
    adj[vert1].push_back(std::make_pair(vert2, weight));
    adj[vert2].push_back(std::make_pair(vert1, weight));
}

auto Graph::dijkstra_classic_ss(const size_t src) -> std::vector<int32_t>
{
    std::priority_queue<pair, std::vector<pair>, std::greater<> > Q;
    std::vector<int32_t> dist(get_size(), std::numeric_limits<int32_t>::max());

    Q.emplace(0, src);
    dist[src] = 0;

    while (!Q.empty())
    {
        auto u = Q.top().second;
        Q.pop();

        for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            auto v = (*i).first;
            auto weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                Q.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

auto Graph::dijkstra_classic_p2p(const size_t start, const size_t goal) -> int32_t
{
    auto dist = dijkstra_classic_ss(start);

    return dist[goal];
}

auto Graph::dial_ss(int32_t src) -> std::vector<int32_t>
{
    std::vector<std::pair<int32_t, std::list<int32_t>::iterator>> dist(get_size());

    for (size_t i = 0; i < node_quantity; i++)
    {
        dist[i].first = std::numeric_limits<int32_t>::max();
    }

    size_t buckets_size;
    buckets_size = max_weight * 3;

    std::vector<std::list<int32_t>> B(buckets_size);
    
    B[0].push_back(src);
    dist[src].first = 0;
    
    long unsigned long idx = 0;

    while (true)
    {
        while (B[idx].empty() && idx < B.size())
            idx++;

        if (idx >= B.size())
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
                if (dv != std::numeric_limits<int32_t>::max())
                    B[dv].erase(dist[v].second);

                dist[v].first = du + weight;
                dv = dist[v].first;

                if (dv > B.size())
                {
                    B.resize(dv + buckets_size);
                }

                B[dv].push_front(v);

                dist[v].second = B[dv].begin();
            }
        }
    }

    std::vector<int32_t> d(node_quantity);
    for (size_t i = 0; i < node_quantity; ++i)
    {
        d[i] = dist[i].first;
    }

    return d;
}

auto Graph::dial_p2p(const size_t start, const size_t goal) -> int32_t
{
    auto dist = dial_ss(start);

    return dist[goal];
}

auto Graph::dijkstra_radix_ss(int src) -> std::vector<int32_t>
{
    const auto inf = std::numeric_limits<int32_t>::max();
    std::vector<int32_t> dist(get_size(), inf);

    RadixHeap<int32_t, int32_t> heap;
    dist[src] = 0;

    heap.push(dist[src], src);
    while (!heap.empty())
    {
        int cost;
        int idx;

        std::tie(cost, idx) = heap.pop();
        if (dist[idx] < cost) continue;

        for (auto &e : adj[idx])
        {
            auto next_cost = cost + e.second;

            if (dist[e.first] <= next_cost) continue;

            dist[e.first] = next_cost;
            heap.push(dist[e.first], e.first);
        }
    }

    return dist;
}

auto Graph::dijkstra_radix_p2p(int32_t src, int32_t dest) -> int32_t
{
    const auto dist = dijkstra_radix_ss(src);
    return dist[dest];
}

auto create_graph_from_path(char *path) -> Graph*
{
    std::fstream file(path);
    std::string text;

    Graph *g = new Graph(1);

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

            g->add_edge(src - 1, dest - 1, weight);
        }
        else if (strcmp(p, "p") == 0)
        {
            p = strtok(NULL, " ");
            p = strtok(NULL, " ");
            g = new Graph(atoi(p));
        }
        delete[] line;
    }
    file.close();
    return g;
}

auto get_sources(char *path, int mode) -> std::list<int32_t>
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

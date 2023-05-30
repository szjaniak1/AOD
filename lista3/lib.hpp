#pragma once

#include <list>
#include <cstddef>
#include <vector>

typedef std::vector<std::pair<size_t, std::list<size_t>::iterator> > distances;
typedef std::pair<size_t, size_t> pair;

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::list<pair>* adj;

    public:
        Graph(const size_t node_quantity, const size_t max_weight);

        auto add_edge(const size_t vert1, const size_t vert2, const size_t weight) -> void;
        auto dijkstra_classic_ss(const size_t src) -> distances;
        auto dijkstra_classic_p2p(const size_t start, const size_t goal) -> size_t;
        auto dial_ss(const size_t src) -> distances;
        auto dial_p2p(const size_t start, const size_t goal) -> size_t;
        auto radix_heap_ss(const size_t src) -> std::vector<int>;
        auto radix_heap_p2p(const size_t start, const size_t goal) -> size_t;
};

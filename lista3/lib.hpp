#pragma once

#include <list>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string.h>

typedef std::vector<std::pair<int32_t, std::list<int32_t>::iterator> > distances;
typedef std::pair<int32_t, int32_t> pair;

class Graph;
auto get_sources(char *path, int mode) -> std::list<int32_t>;
auto create_graph_from_path(char *path) -> Graph*;

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::list<pair>* adj;

    public:
        Graph(const size_t node_quantity);

        auto add_edge(const int32_t vert1, const int32_t vert2, const size_t weight) -> void;
        auto dijkstra_classic_ss(const size_t src) -> distances;
        auto dijkstra_classic_p2p(const size_t start, const size_t goal) -> int32_t;
        auto dial_ss(int src) -> std::vector<int>;
        auto dial_p2p(const size_t start, const size_t goal) -> int32_t;
        auto radix_heap_ss(const size_t src) -> std::vector<int>;
        auto radix_heap_p2p(const size_t start, const size_t goal) -> int32_t;
};

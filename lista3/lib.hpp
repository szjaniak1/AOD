#pragma once

#include <list>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string.h>

typedef std::pair<int32_t, int32_t> pair;

class Graph;
auto get_sources(char *path, int mode) -> std::list<int32_t>;
auto create_graph_from_path(char *path) -> Graph*;

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::vector<std::vector<pair>> adj; 

    public:
        Graph(const size_t node_quantity);

        auto add_edge(const int32_t vert1, const int32_t vert2, const size_t weight) -> void;
        auto dijkstra_classic_ss(const size_t src) -> std::vector<int32_t>;
        auto dijkstra_classic_p2p(const size_t start, const size_t goal) -> int32_t;
        auto dial_ss(int32_t src) -> std::vector<int32_t>;
        auto dial_p2p(size_t start, const size_t goal) -> int32_t;
        auto dijkstra_radix_ss(int32_t src) -> std::vector<int32_t>;
        auto dijkstra_radix_p2p(int32_t src, int32_t dest) -> int32_t;
        auto get_size(void) -> size_t;
};

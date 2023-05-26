#include <list>
#include <cstddef>
#include <vector>

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::list<std::pair<size_t, size_t> >* adj;

    public:
        Graph(const size_t node_quantity, const size_t max_weight);

        auto add_edge(const size_t vert1, const size_t vert2, const size_t weight) -> void;
        auto dijkstra_classic_ss(const size_t src) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >;
        auto dijkstra_classic_p2p(const int start, const int goal) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >;
        auto dial_ss(const size_t src) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >;
        auto dial_p2p(const int start, const int goal) -> std::vector<std::pair<size_t, std::list<size_t>::iterator> >;
};

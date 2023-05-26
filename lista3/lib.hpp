#include <list>
#include <cstddef>

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::list<std::pair<int, int>>* adj;

    public:
        Graph(const size_t node_quantity);

        void add_edge(const int u, const int v, const int w);
        void shortest_path(const int s, const int w);
};

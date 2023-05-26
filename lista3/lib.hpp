#include <list>
#include <cstddef>

class Graph
{
    size_t node_quantity;
    size_t max_weight;
    std::list<std::pair<size_t, size_t> >* adj;

        size_t min_distance(const std::vector<std::pair<int, std::list<size_t>::iterator> > dist, const bool visited[]);  

    public:
        Graph(const size_t node_quantity, const size_t max_weight);

        void add_edge(const size_t vert1, const size_t vert2, const size_t weight);
        void dijkstra_classic_ss(const size_t src);
        void dijkstra_classic_p2p(const int start, const int goal);
        void dial_ss(const int src);
        void dial_p2p(const int start, const int goal);
};

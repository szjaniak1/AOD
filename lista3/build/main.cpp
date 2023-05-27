#include <cstdio>

#include "lib.hpp"
#include "radixheap.hpp"

void take_input();
void print_dist(const distances dist, const size_t node_quantity);

void print_dist(const distances dist, const size_t node_quantity)
{
    printf("Vertex Distance from Source\n");
    for (size_t i = 0; i < node_quantity; ++i)
        printf("%zu \t %zu\n", i, dist[i].first);
}

int main(void)
{
    size_t V = 9;
    Graph g(V, 0);
 
    // making above shown graph
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14);
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(7, 8, 7);
 
    // maximum weighted edge - 14
    // g.dial_ss(0);
    // printf("\n");

    auto dist = g.dijkstra_classic_ss(2);
    print_dist(dist, V);

    printf("\n");

    auto d = g.dijkstra_classic_p2p(2, 4);
    printf("%zu", d);

    auto d2 = g.radix_heap_ss(2);
    print_dist(d2, V);

    return 0;
}

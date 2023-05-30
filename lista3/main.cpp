#include <cstdio>
#include <cstring>
#include <iostream>

#include "lib.hpp"

void take_input();
void print_dist(const distances dist, const size_t node_quantity);
void print_dist_radix(const std::vector<int32_t> dist, const size_t node_quantity);

void print_dist(const distances dist, const size_t node_quantity)
{
    printf("Vertex Distance from Source\n");
    for (size_t i = 0; i < node_quantity; ++i)
        printf("%zu \t %zu\n", i, dist[i].first);
}

void print_dist_radix(const std::vector<int> dist, const size_t node_quantity)
{
    for (auto d : dist)
    {
        printf("%d\n", d);
    }
}

int main(int argc, char* argv[])
{
    int mode; // 1 - time measure, 2 - shortest path
    char* data_path;
    char* sources_path;
    char* results_path;

    // load_params
    if(argc < 5)
    {
        std::cout << "No parameters given" << std::endl;
        return -1;
    }
    for(size_t i = 1; i < 5; i+=2)
    {
        if(strcmp(argv[i], "-d") == 0)
        {
            data_path = argv[i+1];
        }
        else if(strcmp(argv[i], "-ss") == 0)
        {
            sources_path = argv[i+1];
            mode = 1;
        }
        else if(strcmp(argv[i], "-p2p") == 0)
        {
            sources_path = argv[i+1];
            mode = 2;
        }
    }
    Graph* g = new Graph(0, 0);
    g->create_graph_from_path(data_path);

    std::list<int> src = g->get_sources(sources_path, mode);

    if(mode == 1)
    {
        while(!src.empty())
        {
            int s = src.back();
            std::vector<int> dist = g->radix_heap_ss(s);
            src.pop_back();
        }
    }
    else if (mode == 2)
    {
        while (!src.empty())
        {
            int dest = src.back();
            src.pop_back();
            int s = src.back();
            auto dist = g->radix_heap_p2p(s, dest);
            src.pop_back();
            std::cout << dist << std::endl;
        }
    }

    return 0;
}

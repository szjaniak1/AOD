#include <cstring>
#include <iostream>

#include "lib.hpp"

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
    
    Graph* g = create_graph_from_path(data_path);

    std::list<int32_t> src = get_sources(sources_path, mode);

    if(mode == 1)
    {
        while(!src.empty())
        {
            int s = src.back();
            auto dist = g->dijkstra_classic_ss(s);
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
            auto dist = g->dijkstra_classic_p2p(s, dest);
            src.pop_back();
            std::cout << dist << std::endl;
        }
    }

    return 0;
}


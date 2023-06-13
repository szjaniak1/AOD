#include <cstring>
#include <iostream>
#include <chrono>
#include <fstream>

#include "lib.hpp"

int main(int argc, char* argv[])
{
    int mode = 0; // 1 - time measure, 2 - shortest path
    char* data_path;
    char* sources_path;
    char* results_path;

    // load_params
   if(argc < 5)
    {
        std::cout << "No parameters given" << std::endl;
        return -1;
    }
    for(size_t i = 1; i < 6; i+=2)
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
        else if (strcmp(argv[i], "-oss") == 0)
        {
            results_path = argv[i + 1];
        }
        else if (strcmp(argv[i], "-op2p") == 0)
        {
            results_path = argv[i + 1];
        }
    }
    
    Graph *g = create_graph_from_path(data_path);

    std::list<int32_t> src = get_sources(sources_path, mode);

    std::ofstream my_file(results_path, std::ios::app);
    if(mode == 1)
    {
        long long time = 0;
        while(!src.empty())
        {
            int s = src.back();
            auto start = std::chrono::high_resolution_clock::now();
            auto dist = g->dial_ss(s);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duaration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            time += duaration.count();
            src.pop_back();
        }
        my_file << "dial: time: " << time << " msec" << std::endl;
    }
    else if (mode == 2)
    {
        while (!src.empty())
        {
            int dest = src.back();
            src.pop_back();
            int s = src.back();
            auto dist = g->dial_p2p(s, dest);
            src.pop_back();
            my_file << "dial: source: " << s << " dest: " << dest << "distance: " << dist << std::endl;
        }
    }

    return 0;
}


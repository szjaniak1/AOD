#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

const int max_node = 1000000;
const int max_edge = 5000000;
std::vector<int> graph[max_edge];              //store graph's adjacency list
std::vector<int> transpose_graph[max_edge];    //store transpose graph's adjacency list
bool vis[max_node];                            //store node visit stat for dfs
static int length = 0;
std::vector<int> node_order;  
int numOfNodes;			

void dfs(int n)
{
    	if(vis[n]) return; 
    
    	int len = graph[n].size();
    	vis[n]= true;
    
    	for(int i = 0; i < len; i++)
    	{
        	dfs(graph[n][i]);
    	}
    
    	node_order.push_back(n);
}


//this function traverses the transpose graphq
// at each call traverses a SCC and prints each node of that SCC to std output
void dfs_print(int n)
{
    	if (vis[n] == true) return;  //if node is already visited
   	
       	if(numOfNodes <= 200) std:: cout << n << " ";
    	length++;
    	int len = transpose_graph[n].size();
    	vis[n] = true;
    
    	for (int i = 0; i < len; i++)
    	{
        	dfs_print(transpose_graph[n][i]);
    	}
}

//n nodes
// print each SCC nodes in separate line
// and return the number of SCC in that graph
int scc(int n)
{
    	int scc_count= 0; 
    	for (int i = 1; i <= n; i++)
    	{
        	if(vis[i] == false)
		{
            		dfs(i);
        	}
    	}
    
    	for(int i = 1; i <= n; i++)
    	{
        	vis[i]= false;
    	}
    
    	for (int i = node_order.size() - 1; i >= 1; i--)
    	{
        	if (vis[node_order[i]] == false)
		{
			dfs_print(node_order[i]);
			std::cout << "length :" << length << " ";
            		scc_count++;
			length = 0;
			if (numOfNodes <= 200) std::cout << std::endl;
        	}  
    	}
    
    	node_order.clear();
    	return scc_count;
}

int main(void)
{    
    	int m; //m edges
    	int src;
    	int dst; 
	char c;
	std::cin >> c;	
    	std::cin >> numOfNodes >> m;
    
    	for(int i= 0; i <= numOfNodes; i++)
    	{
        	vis[i]= false;
        	graph[i].clear();
        	transpose_graph[i].clear();
    	}
    
    	for (int i = 0; i < m; i++)
	{
		std::cin >> src >> dst;
        
        	graph[src].push_back(dst);
        	transpose_graph[dst].push_back(src);
    	}
    
    	int components = scc(numOfNodes);
	std::cout << "Components: " << components << std::endl;
    
    return 0;
}

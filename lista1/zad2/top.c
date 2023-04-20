#include <stdio.h>
#include <stdlib.h>

void display();
int** input();
void dfs();
int pop(int*);
void push(int, int*);
int v, numOfNodes, numOfVert, t = -1;

int** input()
{
	int src, dst;
	scanf("%d", &numOfNodes);
	numOfNodes++;
	scanf("%d", &numOfVert);	

	int **a = (int**)malloc(numOfNodes * sizeof(int*));
	for (int i = 0; i < numOfNodes; i++)
	{
		a[i] = (int*)malloc(numOfNodes * sizeof(int));	
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			a[i][j] = 0;
		}
	}

	for (int i = 0; i < numOfVert; i++)
	{
		scanf("%d", &src);
		scanf("%d", &dst);
		a[src][dst] = 1;
		if(i == 0) v = src;	
	}

	return a;
}

void topologicalSortUtil(int v, int **a, int *visited, int *stk)
{
	visited[v] = 1;
	for (int *i = a[v][0]; i != &a[v][numOfNodes - 1]; ++i)
	{
		if (!visited[*i]) topologicalSortUtil(*i, a, visited, stk);
	}

	push(v, stk);
}

void topologicalSort(int **a, int *visited, int *stk)
{
	for (int i = 0; i < numOfVert; i++)
	{
		if (visited[i] == 0)
		{
			topologicalSortUtil(i, a, visited, stk);
		}
	}

	while (t >= 0)
	{
		printf("%d ", pop(stk));
	}
}

void display(int **a)
{
	int i, j;
	printf("\nadjacency matrix[][]: \n");
	for (i = 0; i < numOfNodes; i++)
	{
		for (j = 0; j < numOfNodes; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}

void push(int x, int* stk)
{
	stk[++t] = x;
}

int pop(int *stk)
{
	return stk[t--];
}

int main(int argc, char *argv[]) 
{	
	char d;
	scanf("%c", &d);

	int **a = input();	
	int *visited = (int*)malloc(numOfNodes * sizeof(int));
	int *stk = (int*)malloc(numOfNodes * sizeof(int));
	
	for (int i = 0; i < numOfNodes; i++)
	{
		stk[i] = 0;
		visited[i] = 0;
	}

	topologicalSort(a, visited, stk);
	
	for (int i = 0; i < numOfNodes; i++)
	{
		free(a[i]);
	}

	free(a);
	free(visited);
	free(stk);
  	return 0;
}

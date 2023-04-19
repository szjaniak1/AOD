#include <stdio.h>

#define MAX 100

void adj();
void input();
void bfs(int);
int delQue();
void addQue(int);
int v, numOfNodes, numOfVert, f = 0, r = 0,  visited[MAX] = {0}, a[MAX][MAX] = {0}, que[100] = {0};

void input()
{
	int src, dst;
	scanf("%d", &numOfNodes);
	scanf("%d", &numOfVert);

	for (int i = 1; i <= numOfVert; i++)
	{
		scanf("%d", &src);
		scanf("%d", &dst);
		a[src][dst] = 1;
		if(i == 1) v = src;	
	}
}

void bfs(int v)
{
	printf("%d->", v);
	int j, u=v;
	visited[u] = 1;

	while(1)
	{
		for (j = 1; j <= numOfNodes; j++)
		{
			if(a[u][j] != 0 && visited[j] == 0)
			{
				visited[j] = 1;
				addQue(j);
			}
		}

		u = delQue();
		printf("%d->", u);

		if (f == r) break;
	}

	printf("NULL\n");
}

void bfstree(int v)
{
	printf("%d\n", v);
	int j, u=v;
	visited[u] = 1;
	int depth[MAX] = {0};

	while(1)
	{
		for (j = 1; j <= numOfNodes; j++)
		{
			if(a[u][j] != 0 && visited[j] == 0)
			{
				visited[j] = 1;
				depth[j] = depth[u] + 1;
				addQue(j);
			}
		}
		u = delQue();
		for (int i = 0; i < depth[u]; i++)
		{
			printf("-");
		}
		printf("%d\n", u);

		if (f == r) break;
	}

	printf("NULL\n");
}

void adj()
{
	int i, j;
	printf("nadjacency matrix[][]: \n");
	for (i = 1; i <= numOfNodes; i++)
	{	
		for (j = 1; j <= numOfNodes; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}

void addQue(int x)
{
	que[r++] = x;
}

int delQue()
{
	return que[f++];
}


int main(int argc, char *argv[]) 
{
	char d;
	scanf("%c", &d);

	input();	

	if (argc < 2) bfs(v);
	else bfstree(v);

  	return 0;
}

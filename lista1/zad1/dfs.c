#include <stdio.h>

#define MAX 100

void display();
void input();
void dfs();
int pop();
void push(int);
int v, numOfNodes, numOfVert, t = -1, visited[MAX] = {0}, a[MAX][MAX] = {0}, stk[MAX] = {0};

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

void dfs(int v)
{
	printf("%d->", v);
	int i, j, u=v;
	visited[u] = 1;

	while(1)
	{
		for (j = 1; j<= numOfNodes; j++)
		{
			if (a[u][j] != 0 && visited[j] == 0)
			{
				visited[j] = 1;
				push(j);
			}
		}
		u = pop();
		printf("%d->", u);

		if (t == -1) break;
	}
	printf("NULL\n");
}

void dfstree(int v)
{
	printf("%d\n", v);
	int i, j, u=v;
	visited[u] = 1;
	int depth[MAX] = {0};

	while(1)
	{
		for (j = 1; j<= numOfNodes; j++)
		{
			if (a[u][j] != 0 && visited[j] == 0)
			{
				visited[j] = 1;
				depth[j] = depth[u] + 1;
				push(j);
			}
		}
		u = pop();
		for (int i = 0; i < depth[u]; i++)
		{
			printf("-");
		}
		printf("%d\n", u);

		if (t == -1) break;
	}
	printf("NULL\n");
}

void display()
{
	int i, j;
	printf("\nadjacency matrix[][]: \n");
	for (i = 1; i <= numOfNodes; i++)
	{
		for (j = 1; j <= numOfNodes; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}

void push(int x)
{
	stk[++t] = x;
}

int pop()
{
	return stk[t--];
}

int main(int argc, char *argv[]) 
{
	char d;
	scanf("%c", &d);

	input();	

	if (argc < 2) dfs(v);
	else dfstree(v);

  	return 0;
}

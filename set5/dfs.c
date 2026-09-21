#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100

typedef enum
{
    WHITE,
    GRAY,
    BLACK
} Color;

typedef struct Node
{
    int dest;
    struct Node *next;
} Node;

typedef struct
{
    int V;
    Node *head[MAX_V];
    Node *tail[MAX_V]; // tail pointer keeps insertion order
} Graph;

// DFS state
static Color color[MAX_V];
static int disc[MAX_V], fin[MAX_V];
static int timer_;

void initGraph(Graph *g, int V)
{
    g->V = V;
    for (int i = 0; i < V; i++)
        g->head[i] = g->tail[i] = NULL;
}

void addEdge(Graph *g, int u, int v)
{
    Node *n = malloc(sizeof(Node));
    n->dest = v;
    n->next = NULL;
    if (g->tail[u])
        g->tail[u]->next = n;
    else
        g->head[u] = n;
    g->tail[u] = n;
}

void freeGraph(Graph *g)
{
    for (int i = 0; i < g->V; i++)
    {
        Node *cur = g->head[i];
        while (cur)
        {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

void dfsVisit(Graph *g, int u)
{
    color[u] = GRAY;
    disc[u] = ++timer_;

    for (Node *e = g->head[u]; e; e = e->next)
    {
        int v = e->dest;

        if (color[v] == WHITE)
        {
            printf("Tree edge     : %d -> %d\n", u, v);
            dfsVisit(g, v);
        }
        else if (color[v] == GRAY)
        {
            // v is an ancestor still on the recursion stack (includes self-loops)
            printf("Back edge     : %d -> %d\n", u, v);
        }
        else
        { // BLACK: v is already finished
            if (disc[u] < disc[v])
                printf("Forward edge  : %d -> %d\n", u, v); // v is a descendant of u
            else
                printf("Cross edge    : %d -> %d\n", u, v); // v is in another subtree/tree
        }
    }

    color[u] = BLACK;
    fin[u] = ++timer_;
}

void dfs(Graph *g)
{
    for (int i = 0; i < g->V; i++)
    {
        color[i] = WHITE;
        disc[i] = fin[i] = 0;
    }
    timer_ = 0;

    // Loop over all vertices so disconnected parts (DFS forest) are covered
    for (int i = 0; i < g->V; i++)
    {
        if (color[i] == WHITE)
            dfsVisit(g, i);
    }

    printf("\nVertex  Discovery  Finish\n");
    for (int i = 0; i < g->V; i++)
        printf("%4d    %6d    %5d\n", i, disc[i], fin[i]);
}

int main(void)
{
    Graph g;
    initGraph(&g, 6);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 0, 3);
    addEdge(&g, 1, 3);
    addEdge(&g, 2, 1);
    addEdge(&g, 3, 0);
    addEdge(&g, 4, 5);
    addEdge(&g, 4, 3);
    addEdge(&g, 5, 4);

    dfs(&g);
    freeGraph(&g);
    return 0;
}
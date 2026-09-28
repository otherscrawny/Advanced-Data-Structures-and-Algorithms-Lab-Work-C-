#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int dest;
    struct Node *next;
};

struct Graph
{
    int V;
    struct Node **adj;
};

struct Edge
{
    int u;
    int v;
};

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (struct Node **)malloc(V * sizeof(struct Node *));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

void SCCUtil(struct Graph *graph, int u, int disc[], int low[], int st[], int *top, bool stackMember[], int *timer)
{
    disc[u] = low[u] = ++(*timer);
    st[++(*top)] = u;
    stackMember[u] = true;

    struct Node *temp = graph->adj[u];
    while (temp != NULL)
    {
        int v = temp->dest;
        if (disc[v] == -1)
        {
            SCCUtil(graph, v, disc, low, st, top, stackMember, timer);
            if (low[v] < low[u])
                low[u] = low[v];
        }
        else if (stackMember[v])
        {
            if (disc[v] < low[u])
                low[u] = disc[v];
        }
        temp = temp->next;
    }

    if (low[u] == disc[u])
    {
        printf("  - SCC: ");
        while (true)
        {
            int v = st[(*top)--];
            stackMember[v] = false;
            printf("%d ", v);
            if (v == u)
                break;
        }
        printf("\n");
    }
}

void findSCCs(struct Graph *graph)
{
    int V = graph->V;
    int *disc = (int *)malloc(V * sizeof(int));
    int *low = (int *)malloc(V * sizeof(int));
    bool *stackMember = (bool *)malloc(V * sizeof(bool));
    int *st = (int *)malloc(V * sizeof(int));
    int top = -1;
    int timer = 0;

    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    printf("\n--- Strongly Connected Components (SCCs) ---\n");
    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            SCCUtil(graph, i, disc, low, st, &top, stackMember, &timer);
        }
    }

    free(disc);
    free(low);
    free(stackMember);
    free(st);
}

void bridgeBCCUtil(struct Graph *graph, int u, int p, int disc[], int low[], bool ap[],
                   struct Edge edgeStack[], int *edgeTop, int *timer)
{
    disc[u] = low[u] = ++(*timer);
    int children = 0;

    struct Node *temp = graph->adj[u];
    while (temp != NULL)
    {
        int v = temp->dest;
        if (v == p)
        {
            temp = temp->next;
            continue;
        }

        if (disc[v] != -1)
        {
            if (disc[v] < low[u])
                low[u] = disc[v];
            if (disc[v] < disc[u])
            {
                edgeStack[++(*edgeTop)] = (struct Edge){u, v};
            }
        }
        else
        {
            children++;
            edgeStack[++(*edgeTop)] = (struct Edge){u, v};
            bridgeBCCUtil(graph, v, u, disc, low, ap, edgeStack, edgeTop, timer);

            if (low[v] < low[u])
                low[u] = low[v];

            // Bridge condition
            if (low[v] > disc[u])
            {
                printf("  - Bridge: %d - %d\n", u, v);
            }

            // Articulation point condition
            if (p != -1 && low[v] >= disc[u])
            {
                ap[u] = true;
                printf("  - BCC containing edge (%d, %d): ", u, v);
                while (true)
                {
                    struct Edge edge = edgeStack[(*edgeTop)--];
                    printf("(%d,%d) ", edge.u, edge.v);
                    if (edge.u == u && edge.v == v)
                        break;
                }
                printf("\n");
            }
        }
        temp = temp->next;
    }

    if (p == -1 && children > 1)
    {
        ap[u] = true;
    }
}

void findBCCsAndBridges(struct Graph *graph)
{
    int V = graph->V;
    int *disc = (int *)malloc(V * sizeof(int));
    int *low = (int *)malloc(V * sizeof(int));
    bool *ap = (bool *)malloc(V * sizeof(bool));
    struct Edge *edgeStack = (struct Edge *)malloc(100 * sizeof(struct Edge));
    int edgeTop = -1;
    int timer = 0;

    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        ap[i] = false;
    }

    printf("\n--- Bridges and Biconnected Components (BCCs) ---\n");
    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            bridgeBCCUtil(graph, i, -1, disc, low, ap, edgeStack, &edgeTop, &timer);

            if (edgeTop != -1)
            {
                printf("  - Root BCC: ");
                while (edgeTop != -1)
                {
                    struct Edge edge = edgeStack[edgeTop--];
                    printf("(%d,%d) ", edge.u, edge.v);
                }
                printf("\n");
            }
        }
    }

    printf("\n--- Articulation Points ---\n  - ");
    bool anyAP = false;
    for (int i = 0; i < V; i++)
    {
        if (ap[i])
        {
            printf("%d ", i);
            anyAP = true;
        }
    }
    if (!anyAP)
        printf("None");
    printf("\n");

    free(disc);
    free(low);
    free(ap);
    free(edgeStack);
}

int main()
{
    int V = 5;
    struct Graph *graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);

    findSCCs(graph);

    findBCCsAndBridges(graph);

    return 0;
}
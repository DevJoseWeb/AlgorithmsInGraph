/*graph.h*/
#ifndef GRAPH_H
#define GRAPH_H

struct adjlist_node{
    int vertex;
    struct adjlist_node *next;
    struct adjlist_node *previous;
};

struct adjlist{
    int num_members;
    struct adjlist_node *head;
};

struct graph{
    int n;
    struct adjlist *adjListArr; /*its size will be the number of vertices in graph*/
};


struct adjlist_node* createNode(int v){
    struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
    if(!newNode)
        printf("Unable to allocate memory for new node");

    newNode->vertex = v;
    newNode->next = NULL;

    return newNode;
}

struct graph* createGraph(int n){
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph));
    if(!graph)
        printf("Unable to allocate memory for graph");
    graph->n = n;

    /* Create an array of adjacency lists*/
    graph->adjListArr = (struct adjlist *)malloc(n * sizeof(struct adjlist));
    if(!graph->adjListArr)
        printf("Unable to allocate memory for adjacency list array");

    for(int i = 0; i < n; i++)
    {
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }

    return graph;
}

void destroyGraph(struct graph *graph){
    if(graph)
    {
        if(graph->adjListArr)
        {
            /*Free up the nodes*/
            for (int v = 0; v < graph->n; v++)
            {
                struct adjlist_node *adjListPtr = graph->adjListArr[v].head;
                while (adjListPtr)
                {
                    struct adjlist_node *tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjListArr);
        }
        /*Free the graph*/
        free(graph);
    }
}

void addEdge(struct graph *graph, int vertex1, int vertex2){
    /* Add an edge from vertex1 to vertex2 in the adjacency list*/
    struct adjlist_node *newNode = createNode(vertex2);
    newNode->next = graph->adjListArr[vertex1].head;
    graph->adjListArr[vertex1].head = newNode;
    graph->adjListArr[vertex1].num_members++;

    /* Add an edge from vertex2 to vertex1 also*/
    newNode = createNode(vertex1);
    newNode->next = graph->adjListArr[vertex2].head;
    graph->adjListArr[vertex2].head = newNode;
    graph->adjListArr[vertex2].num_members++;
}

void displayAdjacencyList(struct adjlist adjlist){
    struct adjlist_node *adjListPtr = adjlist.head;
    
    while (adjListPtr)
    {
        printf("%d->", adjListPtr->vertex);
        adjListPtr = adjListPtr->next;
    }
    printf("NULL\n");
}

void displayGraph(struct graph *graph){
    for (int i = 0; i < graph->n; i++){
        printf("\n%d: ", i);
        displayAdjacencyList(graph->adjListArr[i]);
    }
}

#endif
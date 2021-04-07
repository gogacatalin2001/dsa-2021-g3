#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next;

} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

typedef struct vertex_type
{
    int label;
    ListT *edges;
    struct vertex_type *nextVertex;// each vertex has a list associated for defining its edges
}VertexT;

typedef struct
{
    VertexT *first, *last;
} GraphT;

void error(const char *msg)
{
    printf(msg);
    exit(1);
}

ListT *createEmptyList()
{
    ListT *listPtr = (ListT*)calloc(1,sizeof(ListT));/// allocate memory for the list
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

VertexT *createVertex(int label)
{
    VertexT *vertex = (VertexT*)calloc(1,sizeof(VertexT));
    if(vertex == NULL)
        error("Not enough memory for creating the vertex!");
    vertex->label = label;
    vertex->edges = createEmptyList();
    vertex->nextVertex = NULL;
    return vertex;
}

NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT*)calloc(1,sizeof(NodeT));/// allocate memory for the node
    if(p == NULL)
        error("Not enough to create the node!");
    else
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

int insertAtFront(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        p->next = listPtr->first;/// list is nonempty
        if(listPtr->count == 0)
        {
            listPtr->last = p;/// list is empty
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

/// insert at the end
int append(ListT *listPtr, NodeT *p)
{
    if(listPtr)
    {
        if(listPtr->count == 0)
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;/// success
    }
    return 0;/// failure
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if(listPtr->first != NULL)
    {
        /// for non-empty list
        p = listPtr->first;
        listPtr->first = p->next;
        //free(p);/// free memory
        listPtr->count--;
        /// for empty list
        if(listPtr->first == NULL)
            listPtr->last = NULL;
        return p;/// return the deleted node
    }
    return NULL;
}

NodeT *deleteLast(ListT *listPtr)
{
    NodeT *p;
    p = listPtr->first;
    if(p)/// list is not empty
    {
        while(p->next != listPtr->last)
            p = p->next;
        if(p == listPtr->first)
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            listPtr->last = p;
            listPtr->last->next = NULL;
            p = p->next;
            listPtr->count--;
            return p;/// return the deleted node
        }
    }
    /// list is empty
    return NULL;
}

void purge(ListT *listPtr)
{
    NodeT *p;
    while(listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = p->next;
        free(p);
    }
    listPtr->last = NULL;
    listPtr->count = 0;
}

void printList(ListT *listPtr)
{
    NodeT *p = listPtr->first;
    while(p)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

/// for STACK

int push(ListT *stackPtr, NodeT *p)
{
   return insertAtFront(stackPtr,p);
}

NodeT *pop(ListT *stackPtr)
{
  return deleteFirst(stackPtr);
}

NodeT *top(ListT *stackPtr)
{
    return stackPtr->first;
}

/// for QUEUE

int enqueue(ListT *queuePtr, NodeT *p)
{
    return append(queuePtr,p);
}

NodeT *dequeue(ListT *queuePtr)
{
    return deleteFirst(queuePtr);
}

NodeT *front(ListT *queuePtr)
{
    return queuePtr->first;
}

NodeT *rear(ListT *queuePtr)
{
    return queuePtr->last;
}

void createGraph(FILE *in, GraphT *adjList)
{
    if(adjList == NULL)
    {
        adjList = (GraphT*)calloc(1, sizeof(GraphT));
        if(adjList == NULL)
            error("Not enough memory to create the graph!");
        adjList->first = adjList->last = NULL;
    }

    int n = 0; // number of relations
    fscanf(in, "%d", &n);

    // create the graph
    for(int i = 0; i < n; i++)
    {
        int vertex1, vertex2;
        fscanf(in, "\n%d", &vertex1);
        fscanf(in, "\n%d", &vertex2);
        VertexT *v = adjList->last;
        // if graph is empty
        if(v == NULL)
        {
            // add the first vertex to the graph
            v = createVertex(vertex1);
            adjList->first = adjList->last = v;
            append(v->edges, createSLLNode(vertex2));
            // add the second vertex to the graph
            v->nextVertex = createVertex(vertex2);
            v = v->nextVertex;
            adjList->last = v;
            append(v->edges, createSLLNode(vertex1));
        }
        else
        {
            // add the first vertex to the graph
            v->nextVertex = createVertex(vertex1);
            v = v->nextVertex;
            append(v->edges, createSLLNode(vertex2));
            // add the second vertex to the graph
            v->nextVertex = createVertex(vertex2);
            v = v->nextVertex;
            adjList->last = v;
            append(v->edges, createSLLNode(vertex1));
        }
    }
}

int main(int argc, char **argv)
{

    FILE *in, *out;
    in = fopen(argv[1], "r");
    if(in == NULL)
        error("Couldn't open input file!");
    out = fopen(argv[2], "w");
    if(out == NULL)
        error("Couldn't open output file!");

    GraphT *adjacencyList = NULL;
    createGraph(in, adjacencyList);


    int n; // number of relations
    fscanf(in, "%d", &n);
    fprintf(out, "%d\n", n);
    /*
    VertexT *v = adjacencyList->first;
    while(v != NULL)
    {
        fprintf(out, "%d: ",v->label);
        printList(v->edges);
        v = v->nextVertex;
    }



    // create the graph
    for(int i = 0; i < n; i++)
    {
        int vertex1, vertex2;
        fscanf(in, "\n%d", &vertex1);
        fprintf(out, "%d ", vertex1);
        fscanf(in, "\n%d", &vertex2);
        fprintf(out, "%d\n", vertex2);
    }
    */
    fclose(in);
    fclose(out);

    return 0;
}

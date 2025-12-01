#include <stdio.h>
#include <stdlib.h>
#define MAX 9
#define VISITED 1
#define UNVISITED 100

typedef struct node {
    int elem;
    struct node *link;
} *ptr, Node;

typedef ptr Graph[MAX];
typedef int vertex;

typedef struct {
    int front;
    int rear;
    vertex G[MAX+1];
} Queue;

void dfs(Graph G, vertex v, int mark[])
{
    ptr node = G[v];
    mark[v] = VISITED;
    printf("%d ", v);
    while(node != NULL)
    {
        int elem = node->elem; 
        if(mark[elem] == UNVISITED){
            dfs(G, elem, mark);
        }
         node = node->link;
    }
}

void enqueue(Queue *q, vertex v)
{
    if(q->front == q->rear)
    return;
    
    if(q->front == -1)
    q->front = 0;
    
    q->G[q->rear] = v;
    q->rear = (q->rear + 1) % MAX;
}

vertex dequeue(Queue *q)
{
    if(q->front == -1)
    return -1;
    
    vertex node = q->G[q->front];
    q->front = (q->front + 1) % MAX;
    
    if(q->front == q->rear)
    {
        q->front = -1;
        q->rear = 0;
    }
    
    return node;
}

void bfs(Graph G, vertex v, int mark[])
{
    Queue q;
    q.front = -1;
    q.rear = 0;
    enqueue(&q, v);
    while(q.front != -1)
    {
        vertex v = dequeue(&q);
        
        mark[v] = VISITED;
        printf("%d ", v);
        
        ptr node = G[v];
        
        while(node != NULL)
        {
            if(mark[node->elem] == UNVISITED)
            enqueue(&q, node->elem);
            node = node->link;
        }
    }
}

void insert(Graph G, vertex v, vertex w)
{
    ptr newNode = calloc(1, sizeof(Node));
    newNode->elem = w;
    ptr head = G[v];
    if(G[v] == NULL)
    G[v] = newNode;
    else
    {
        while(head->link != NULL)
        {
            head = head->link;
        }
        head->link = newNode;
    }
}

int main() 
{
    Graph G;
    int mark[MAX]; 
    for(int i = 0; i < MAX; i++)
    {
        G[i] = NULL;
        mark[i] = UNVISITED;
    }
    
    insert(G, 0, 1);
    insert(G, 0, 3);
    insert(G, 0, 4);
    insert(G, 1, 5);
    insert(G, 3, 8);
    insert(G, 4, 6);
    // dfs(G, 0, mark);
    bfs(G, 0, mark);
}
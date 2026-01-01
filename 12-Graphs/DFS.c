#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define unvisited 100
#define visited 1

typedef struct node{
    int elem;
    struct node* link;
} *ptr, Node;

typedef ptr Graph[MAX];
typedef int vertex;

void dfs(Graph G, vertex v, int * marker){
    if(marker[v] == visited){
        return;
    }
    
    marker[v] = visited;
    printf("%d -> ", v);
    
    ptr pointer = G[v];
    while(pointer != NULL){
        vertex w = pointer->elem;
        if(marker[w] == unvisited){
            dfs(G, w, marker);
        }
        pointer = pointer->link;
        
    }
    
    
    
}

void insertLast(Graph G, vertex v, vertex w){
    ptr newNode = (ptr)calloc(1,sizeof(Node));
    newNode->elem = w;

    if(G[v] == NULL) G[v] = newNode;
    else{
        ptr temp = G[w];
        while(temp->link != NULL){
            temp = temp->link;
        }
        temp->link = newNode;
    }
}


int main(){
    Graph G;
    int marker[MAX];
    vertex start = 2;
    for (int i = 0; i < MAX; i++) {
        G[i] = NULL;
        marker[i] = unvisited;
    }
    
    insertLast(G, 2, 3);
    insertLast(G, 3, 4);
    insertLast(G, 4, 1);
    insertLast(G, 1, 5);
    dfs(G, start, marker);
    printf("NULL");
}




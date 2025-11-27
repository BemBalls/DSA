#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define unvisited 100
#define visited -1


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
    
    Node pointer = G[v]
    while(pointer != NULL){
        vertex w = pointer->elem;
        if(marker[w] == unvisited){
            dfs(G, w, marker);
        }
        pointer = pointer->link
    }
    
}

void insertLast(Graph G, vertex v, vertex w){
    ptr newNode = (ptr)calloc(1,sizeof(node));
    newNode->elem = v;

    if(G[w] == NULL) G[w] = newNode;
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
    int marker;
    for (int i = 0; i < MAX; i++) {
        G[i] = NULL;
        marker[i] = unvisited;
    }

    insertLast(G, 3, 2);
    insertLast(G, 2, 4);
    insertLast(G, 4, 1);
    insertLast(G, 1, 5);
    vertex start = 2;
    dfs(G, v, &marker);

}




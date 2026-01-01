#include <stdio.h>
#define MAX 100
#define VISITED 1
#define UNVISITED 100




typedef struct node{
    int data;
    struct node* link;
}*ptr, Node;


typedef ptr Graph[MAX];
typedef int vertex;


void dfs(Graph G, vertex w, int * marker){
    if(marked[v] == VISITED){
        return NULL;
    }
    marked[v] = VISITED;
    ptr * temp = G;
    while(temp != NULL){
        vertex  w = temp->data;
        if(marked[v] == UNVISITED){
            
        }
    }
}
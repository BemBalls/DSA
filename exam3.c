/*f

for DFS
max 9
unvisited 999
visited 1
typedef int vertex;


dfs(graph * T, vertex u, marker)
if marker[v] == visited
return

marker[v] = visited
ptr pointer = T
while (pointer != NULL)
vertex w  = pointer->elem
if(marker[w] = unvisited)  
dfs(T, w, &marker)
pointer = pointer -> link



void insertLast(Graph * T, vertex v, vertex w){
ptr newNode = (ptr*)calloc(1,sizeof(node))

if(T[v] == NULL) T[V] = newNode
else
ptr temp = T[w]
while(temp->link!=NULL)
temp = temp->link

temp->link = newNode

BST
	


insert(Tree * T, int value

Tree * trav = T;

while(*trav != NULL)
if ((*trav)->data == value) duplication

trav = (*trav)->data > value ? &(*trav)->left : &(*trav)->right

 

if (*trav == NULL)
*trav = calloc(1,sizeof(node))




insert
set TREE * trav as T
while trav is not = to NULL
check for duplication //((*trav)->data == value)
check if data is greater than value
yes, go to left
else go to right

insert now the trav using calloc
/*
  *trav = calloc(1,sizeof(node)




deleting


*/












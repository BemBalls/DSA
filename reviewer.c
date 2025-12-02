/*

/*
made by spry IM SO COOKED
EXAM 3 Coverage 
Priority Queue
Binary Tree
Binary Search Tree
Graphs
Itlog ni Djakstra 


Priority Queue
- A queueing system that uses Max Heap, where starting from root each child will always be lower than the parent
Formulas to note
Parent = (child index - 1)/2
Left = 2(parent index) + 1
Right = 2(parent index) + 2
Delete root heapsort = size/2 - 1

PQ's Typedef 
typedef struct {
    int priority; // Priority level (Higher number = Higher priority)
    //maybe some other data
} Process;

// Priority Queue Structure (Max Heap Implementation)
// The heap array will store the processes.
typedef struct {
    Process heap[MAX_PROCESSES]; // Array to store the heap elements
    int size;                    // Current number of processes in the queue
    int capacity;                // Maximum capacity of the queue
} PriorityQueue;


Basic commands
1. enqueue(PriorityQueue * pq, int priority)
- Insert data at last available node (size), then increment
- while loop to upheapify(pushing the number up the tree until root)
    - upheapify uses a while loop that compares child and parent, call swap func if child is greater
- functions ends

2. dequeue(PriorityQueue * pq)
* depending on whats asked, might be a non void func that asks for returned value(extracted root)
- Swap data of root and last, then decrement size;
- Start a for loop where I starts at the last non leaf, each iteration call heapify to fix the heap
    - take note that the heapify argument would be heapify(pq, i)
    *we need to pass i as index for heapify to start there

3. Swap(Process * a, Process * b)
*Make sure the passed value to this functions are ADDRESSES of the struct containing data
- initialize temp to store the value of a(Process temp = *a)
- swap, assign value of b(*b) to value of a(*a) where (*a = *b)
- *b = temp

4. Heapify(PriorityQueue * pq, int i)
*concept of heapify is checks if a swap is possible, if it is then swap then recursively call the number
- initialize variables to store
largest = i //current parent index
left = 2(i) + 1 //current's left child
right = 2(i) + 2 //current's right child

- Setup two if statements, where both:
checks if its under size, meaning valid
if childs index value is higher than largest's index value, proceed to next condition

- check if largest is not equal to i(if its not eq, it means a child is greater)
if condition was fulfilled:
call swap function on largest and i, then heapify where we pass largest as 2nd argument


Binary Tree & Binary Search Tree
BT:
- In shape of a tree, where each data is connected via parent-child relationship
- Looks similar to a PQ, but not in an array format as childs depend on their parent node
- Most common implementation is linked list
- Data is NOT sorted, therefore all datas are around the place

Three Types of Order 
Preorder - root, left, (middle), right
Postorder - left, (middle), right, root
Inorder - left, (middle), root, right
*note that middle is optional, because in cases of BT a middle child usually appears
*in the case of BST, there is no middle child

Terminologies
Root - topmost index, which starts at 0th index
Siblings - nodes under the same parent 
Path - sequences of the nodes as they go down the tree 
Ancestor - all the paths and nodes before the chosen node
Descendant - all the nodes from that subtree from a specific node
Subtree - a branch/node that serves as a root for its children nodes 
Height - number of connections found from root to latest child 
Depth - number of connections found from root to a specific node
Parent - node that serves as an ancestor for a child
Children - node that serves as a descendant of a node
Leaf - node without any children node
Cousins - 2 nodes of the same depth

Visualization: 
        5
      / | \
     0  6  2
       / \   \
      3   1   8
    / | \
   9  4  7
Preorder: 5 0 6 3 9 4 7 1 2 8 
Postorder: 0 9 4 7 3 1 6 8 2 5
Inorder: 0 5 9 3 4 7 6 1 8 2


BST
- Ordered through a system where compared to parent node, all left will be smaller and all right will be higher than the pnode
- Uses a double pointer system to traverse, where traversal will hold the address of the node were looking for/insert on



BST's typedef 
typedef struct node{
    struct node * lc;
    struct node * rc; 
    int data;
}*BST, node; 
//we need node for the sizeof() initializations, also for structs next(lc and rc) 

Basic Commands 
- Important note: traversal works via
    trav = (*trav)->data > val ? &(*trav)->lc : &(*trav)->rc
    //travs new address by checking if its current data is higher than the val we are inserting, 
    if not then we assign it the ADDRESS of lc else the ADDRESS of rc
    *assigning address is important to maintain integrity of double pointer


1. Insert(BST * tree, int val)
- initialize trav as double pointer, containing tree (BST * trav = tree)
- start a while with our traversal inside that only stops if *trav is null, or if matching value was found(duplicate checker)
- After loop stops, add an if statement checking if *trav is NULL (to ensure we are inserting at a free node)
- call calloc on the *trav, with 1 and sizeof(node), this initializes all values to 0 (pointers will treat 0 as null automatically)
- insert data on trav

2. Delete(BST * tree, int val)
- initialize trav as double pointer, containing tree (BST * trav = tree)
- start a while with our traversal inside that only stops if *trav is null, or if matching value was found(meaning target value was found)
- After loop stops, add an if statement checking if *trav's data is equal to target val (to ensure we are on the node we WANT to delete)
- if fulfilled, we start a chain of conditionals checking specifically for:
1. no children (Both null) //1st if statement
    - simply free *trav

2. left child only(left is NOT null, right is null) //2nd else if 
    - Initialize a single pointer temp to store the left child
    - free your *trav
    - assign your temp to *trav
    - now your trav contains the left child
    //note FOLLOW the * because its important to match what we are assigning 
    //if u dont put *, u are saying "we are assigning a single pointer to double pointer"

3. right child only(left is null, right is NOT null) //3rd else if
    - same code as outcome 2(left child only), but temp is set to right child

4. 2 childrens(both are NOT null) //4th else
    - initialize temp as right child of trav, which well use to look for the leftmost on the right subtree
    - start a while loop that ends if the lc of temp is null, and the loop traverses by assigning temps left to temp (temp = temp->lc)
    - after loop ends, copy the data of temp to trav
    - call delete function with the parameters as address of trav's right child, and value of temp: delete(&(*trav)->rc, temp->data)
    //this last step starts a 1 step recursion to delete the node we copied from, which is either no child or 1 child 



Graphs 
- a finite set of points connected, called vertices 

Edge
- joins each node together
A-------------B
^       ^
node    edge


Different Types of graphs
1. Directed Graph (A------------>B)
    - Graphs where edge has directions

2. Undirected Graph (A-------B)
    - Does not have a direction

3.  Complete Graph
    - ever pair of node is joined by an edge (A to B,C : B to A,C : C to A,B)
    * to calculate for amount of edges in a complete graph, the formula is:
        (n-1) * (n-2) where is n is the total amount of nodes

4. Connected Graph 
    - If there exists a path for every arbitrary source or event
    //in summary if theres a path that goes through ALL nodes from start to end

Arc (Tail-------->Head)
- Directed edge / edges with arrows pointing
- joins unordered pair of distinct nodes, pointing to another node

Adjacency 
- Node that is adjacent to each other 
Example: T2 --------> T1
    - T2 is ADJACENT to T1
    - Head is ADJACENT to Tail

Path
- Sequences of vertices

Length of path
- number of arcs in a path
Example: A ---------> B ---------> C
    - There are two arcs from A to C

Simple path 
- If all vertices are distinct
//in a sense each node can only have one outgoing and receiving
Example: A ----> B ----> C ----> D ----> A //this is valid, fulfills condition
         A ----> B ----> C ----> A ----> D //this is NOT valid, breaks condition

Loops are defined through cycles, where:
Simple Cycle 
- Simple path that begins and ends at the same vertex (Example 1 of simple path)

Cyclic Graph 
- Contains a cycle(loop)

Acyclic Cycle
- Contains NO cycle(no loop)

Incident 
- A node is incident to an arc IF n is one of the two nodes in an ordered pair
//simple terms, a node is an incident if its one of the two nodes in an arc 
Example: P1 ------> P2
               ^
            Arc X 
    - P1 is an incident to Arc X
    - P2 is an incident to Arc X

Degree 
- Number of arcs incident to a node
Example P3 ----- > P2 <----- P1 
    - P2 has 2 degrees 

Types of degrees
1. Indegree 
- the number of arcs that have the node as a head 
    - In the example above, P2 has 2 indegrees 

2. Outdegree 
- the number of arcs that have the node as a tail 
    - In the example above, P1 has 1 outdegree

Relations in a graph 
1. Weighted Graph 
- The weight of each arc is the remainder of Heads % Tail
//in short, calculate the mod of head and tail for the value of that arc

         3                      4
         |                    / |
         |                   /  |
         |                  /   |
     /   |                |/_   |
15__ ----------------------7    |
|\   \   |                      |
  \      |                      |
   \     |                     \|/
    \    |                      2
     \   |
      \ \|/
        10

List of Values: 
Arc 10 -> 15: 5
Arc 3 -> 10: 1
Arc 7 -> 15: 1
Arc 4 -> 7: 3
Arc 4 -> 2: 0


2. Labeled Graph 
- di graph in which arcs and/or vertices have an associated label of any value
//This means each arc can have random values, unlike weighted graph that calculates for value of an arc

Representations in C (IM SO COOKED)
1. Adjacency Matrix(2D array)
- Uses a 2d array system that marks arrays index as true if a connection exist between x and y (tail and head)
Visualization
[0] A ----------------->__ B [1]
    |                    /|                     
    |                   / |
    |     -----------  /  |
    |    /                |
    |   /                 |
    |  /                  |
   \|//                  \|/
[3] D ----------------->  C [2]

2D array visualization
               Head  
        |-0---1---2---3-||
      0 |-0-|-1-|-0-|-1-||
Tails 1 |-0-|-0-|-1-|-0-||
      2 |-0-|-0-|-0-|-0-||
      3 |-0-|-1-|-2-|-0-||

Existing Arcs: 
0 -> 1
0 -> 3
1 -> 2
3 -> 2
3 -> 1 


 Weighted Adjacency
- same implementation, but uses value instead of bool operators
- traversal works by checking the shortest possible path

Visualization
[0] A --------5-------->__ B [1]
    |                    /|                     
    |                   / |
    |     ---5-------  /  |
    8    /                7
    |   /                 |
    |  /                  |
   \|//                  \|/
[3] D --------9 ------->  C [2]

2D array visualization
               Head  
        |-0---1---2---3-||
      0 |INF|-5-|INF|-8-||
Tails 1 |INF|INF|-7-|INF||
      2 |INF|INF|INF|INF||
      3 |INF|-5-|-9-|INF||

Existing Arcs: 
0 -> 1, Value 5
0 -> 3, Value 8
1 -> 2, Value 7
3 -> 2, Value 5
3 -> 1, Value 5 //same value  going back

Code algorithm 
- Infinite for inactive spots, to avoid traversing to those coords
    can be either done by:
    1. #define INF 999
    2. Math.h where double inf = INFINITY


2. An array of link list
- Think of this as open hash, but recursive printing on DFS/BFS
//The nodes are basically connections of that index
index 0 -> 1 -> 3
index 1 -> 2
index 2 -> NULL
index 3 -> 2 -> 1

Code Algorithm 
Insertion(Graph G, int v, int indexVal)
//G for graph, v for parent index to insert on, indexVal as value to insert on node
- Initialize a new node as calloc, with 1 as size then insert indexVal as data
- Check if the v index is empty, if it is then insert as head
- else start a trav in index v (G[v]), trav until next is null then insert at last

Deletion
//idk yet im still thinking but no next(no connections) is prolly free that node, but if theres children inherit on grandparent

Depth First Search - DFS(Graph G, int v, int * dict)
//prints through a recursive function that checks if a node is in dict, if not then add there
- print the data of the passed index 
- through the dict(array that checks through boolean), mark that v index(dict[v]) as true(1)
- start a for loop where trav is initialized as passed index (G[v]), trav is NOT null, and increments via traverseing to next (trav = trav->next)
- in the loop, check if the data of trav is FALSE(Unvisited) in the dict(dict[v] == 0)
- IF not visited call dfs recursively, passing trav's data(next index) as your v, ELSE loop continues



3. Dictionary Based
//idk yet but its just cursor based closed hash, shouldnt be hard

Graphs 
- array of linked list


Graphs typedef
typdef struct node{
    int elem;
    struct node * link;
}

typedef ptr Graph[MAX]


DFS Graphs
Depth First Traversal
- array of link list traversal
    - initialize temp node to hold our current vertice 
    - print out data, mark that vertice as visited
    - start a for loop where trav starts at current vertice, stop the loop if trav is null, while incremending through trav = trav->next
    - add a condition checking if travs elem(technically index) is not visited, 
        *if yes then call dfs again, with value of trav passed on vertices(passing the next index through recursion)

BFS Graph
Breadth First Graph
- starts with any nopde for trav, makes use of array to check if visited
- visits all nodes adjacent to current node //recursive? NOT RECURSIVE













int child = size; 
int parent = 0; 
size++ 


//insertion
heap[child] = data;
while(child >= 0){
    parent = (child - 1)/2;
    if(heap[child] > heap[parent]){
        swap(&heap[child], &heap[parent]);
    }
    child = parent; 
} 


//deletion
int returntop = heap[0];
size--; 
swap(&heap[0], &heap[size]); 

for(int i = size/2 - 1;i >= 0;i--){
    heapify(pq, i);
}


//swap
int temp = *a;
*b = *a; 
*b = temp; 

//heapify 
int largest = i;
int left = 2(i) + 1;
int right = 2(i) + 2; 

if(left < size && arr[left] > arr[largest]){
    largest = left; 
}

if(right < size && arr[right] > arr[largest]){
    largest = right;
}

if(largest != i){
    swap(&arr[largest], &arr[i]);
    heapify(pq, largest);
}

typedef struct node{
    struct node * next; 
    int data; 
}node, *ptr; 

typedef ptr Graph[MAX]; 


void dfs(Graph G, int v, int * dict){
    printf("%d" G[v]->data); 
    dict[v] = VISITED; 

    for(node * trav = G[v]; trav != NULL ;trav = trav->next){
        if(trav->data == UNVISITED){
            dfs(G, trav->data, dict);
        }
    }
}


void insert(Graph G, int v, int val){
    node * newNode = (node*)calloc(1, sizeof(node)); 
    newNode->data = val; 

    if(G[v] == NULL){

    }


    ptr trav = G[v]; 
    while(trav->next != NULL){
        trav = trav->next; 
    }

    trav->next = newNode; 
}



dijkstra
also known as the greedy algorithm
only takes itinto account the shortest path from the current to the last
doesnt take in account the whole graph


array to check the cost of the path ( takes it into account the weighted from arc to arc)

also check the unvisited nodes
after checking the paths, set the node as visited
if the cost is higher than the trajected path then change the cost to the trajected, else dont change the cost

UNVISITED NODES = {A, B, C , D , E}
COST
A 0
B 4,  3
C 2
D 4
E 5



flloyds-warshall algorithm
shortest possible path with  negative weights included

spanning tree
subraph with all the shortest path

prims algorithm
finds the shortyest path with the spanning tree
look for the shortest path or the lowest cost and mark it
has an array of visited nodes and use it as the STASRT
O(N log(N) 
)
kruskal
similar to prims
marks the whole graph from the lowest to the highest cost


*/
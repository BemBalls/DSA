/*
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


*/
#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to determine whether an undirected graph is a tree

// A recursive function that returns true if no cycles found
bool isTreeDFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    graphNode_t parent,
    graphNode_t current
) {

    // First see if current node has already been visited, indicating a cycle found
    /* ... */
    if(visited[current]){
        return false;
    }

    // Current node was not already visited, so now mark it as visited
    /* ... */
    visited[current] = true;

    // Now iterate through each of the neighboring graph nodes
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if(visited[neighbor->graphNode]){
            return false;
        }
        if (neighbor->graphNode!=parent) {
            // If the neighbor nodes is not the parent node (the node from which we arrived at current), call DFS
            /* ... */
            parent = current;
            current = neighbor->graphNode;
            isTreeDFS(graphNodeCount, adjacencyList, visited, parent, current);
        }
        neighbor = neighbor->next;
    }

    // All DFS searches from current node found no cycles, so graph is a tree from this node
    return true;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    /*for(size_t i=0; i<graphNodeCount; i++){
        printf("%zu", i);
        AdjacencyListNode* curr = adjacencyList[i].next;
        while(curr!=NULL){
            printf("->%zu", curr->graphNode);
            curr = curr->next;
        }
        printf("\n");
    }*/
    /* ... */

    // Array of boolean variables indicating whether graph node has been visited
    bool* visited = calloc ( graphNodeCount, sizeof(bool) );
    /* ... */

    /* ... */
    graphNode_t parent = -1;
    graphNode_t current = 0;
    bool isTree = isTreeDFS(graphNodeCount, adjacencyList, visited, parent, current);

    freeAdjList(graphNodeCount, adjacencyList);
    free(visited);
    
    printf(isTree ? "yes" : "no");

    return EXIT_SUCCESS;
}

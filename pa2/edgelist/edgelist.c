#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    /* ... */
    AdjacencyListNode* adjacencyList = NULL;
   // char* filename = argv[1];

    size_t nodes = adjMatrixToList(argv[1], &adjacencyList);
    
    //printf("%zu\n", nodes);

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    /* ... */
    for (size_t source=0; source<nodes; source++) {

        AdjacencyListNode* dest = adjacencyList[source].next;

        // list iterator
        while (dest) {
            AdjacencyListNode* temp = dest;
            dest = dest->next; // iterator moves to next
            printf("%zu %zu \n", source, temp->graphNode);
            free(temp);
        }
    }
   
    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    free(adjacencyList);

    return EXIT_SUCCESS;
}

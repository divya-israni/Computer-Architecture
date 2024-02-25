#include "../graphutils.h" // header for functions to load and free adjacencyList
#include "../queue/queue.h" // header for queue

// A program to solve a maze that may contain cycles using BFS

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */
    graphNode_t current;
    graphNode_t target;

    FILE* fp = fopen(argv[2], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    fscanf(fp, "%zu", &current);
    fscanf(fp, "%zu", &target);

    fclose(fp);


    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    /* ... */

    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }

    /* ... */
    parents[current] = current; 
    enqueue(&queue, &current);
    

    while ( current != target && queue.front!=NULL) {
        current = *(graphNode_t*)queue.front->data;
        dequeue(&queue);

        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */
        AdjacencyListNode* neighborNode = adjacencyList[current].next;
        while(neighborNode!=NULL){
            if(parents[neighborNode->graphNode]==-1){
                parents[neighborNode->graphNode] = current;
                enqueue(&queue, &(neighborNode->graphNode));
            }
            neighborNode = neighborNode->next;
        }

        // Visit the next node at the front of the queue of nodes to visit
        /* ... */
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */
    for(size_t i=0; i<graphNodeCount; i++){
        if(parents[i]!=i && parents[i]!=-1){
            printf("%zu %zu\n", parents[i], i);
        }
    }

    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        /* ... */
        QueueNode* toFree = queue.front;
        queue.front = queue.front->next;
        free(toFree);
    }
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}

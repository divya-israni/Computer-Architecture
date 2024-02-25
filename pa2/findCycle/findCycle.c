#include "../graphutils.h"
#include "../queue/queue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
struct element {
    int number;
    struct element* next;
};

void push (
    struct element** paramRoot,
    graphNode_t number
) {
    struct element* oldHead = *paramRoot;
    *paramRoot = malloc ( sizeof ( struct element ) );
    (*paramRoot)->number = number;
    (*paramRoot)->next = oldHead;
    //printf("push %u", newElement->number);
    return;
}

graphNode_t pop (
    struct element** paramRoot
) {
    //when do the .next no memory but infinite loop
    if((*paramRoot!=NULL)){
        struct element* oldRoot = *paramRoot;
        graphNode_t num = oldRoot->number;
        *paramRoot = oldRoot->next;
        free(oldRoot);
        return num;
    //}
    /*if ( (*paramRoot)->next != NULL ) {
        struct element* newHead = (*paramRoot)->next;
        graphNode_t num = newHead->number;
        free(*paramRoot);
        *paramRoot = newHead;
        //printf("%zu ", num);
        return num;*/
    } else {
        perror("Empty stack");
        return(0);
    }
}



bool dfs(AdjacencyListNode* adjacencyList, graphNode_t current, bool* visited, bool* inStack, struct element** root){

    visited[current] = true;
    push(root, current);
    inStack[current] = true;
    bool check = false;

    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while(neighbor){
        if(!visited[neighbor->graphNode]){
            
            check = dfs(adjacencyList, neighbor->graphNode, visited, inStack, root);
            if(check){
                return true;
            }
        }
        else if(inStack[neighbor->graphNode]){
            push(root, neighbor->graphNode);
            return true;
        }
        neighbor = neighbor->next;
    }
    graphNode_t leave = pop(root);
    inStack[leave] = false;
    return false;  
}

int main ( int argc, char* argv[] ) {

    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
   
    bool* visited = calloc(graphNodeCount, sizeof(bool));
    bool* inStack = calloc(graphNodeCount, sizeof(bool));
   
    for(int i=0; i<graphNodeCount; i++){
        visited[i] = false;
        inStack[i] = false;
    }

    struct element* root = NULL;
    bool isCyclic = false;

    for(graphNode_t source=0; source<graphNodeCount; source++){
        if(isCyclic){
            break;
        }
        if(!visited[source]){
            isCyclic = dfs(adjacencyList, source, visited, inStack, &root);
        }
    }

    if (!isCyclic) { printf("DAG\n"); }
 
    free(visited);
    free(inStack);
    graphNode_t leave;
  
    if(isCyclic){
        /*while(root!=NULL){
            printf("%d ", root->number);
            pop(&root);
        }*/
        leave = pop(&root);
        printf("%zu ", leave);
    
        graphNode_t temp = -1;
        struct element* root2 = NULL;
        while(root!=NULL && leave!=temp){
            temp = pop(&root);
            if(leave!=temp){
                push(&root2, temp);
            }
        }
        while(root2!=NULL){
            temp = pop(&root2);
            printf("%zu ", temp);
        }
        free(root2);
    }
    
    while(root!=NULL){
        pop(&root);
    }
    free(root);
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}

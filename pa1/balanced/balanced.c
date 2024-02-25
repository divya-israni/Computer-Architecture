#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold the open and close braces and the pointer to the next element.
struct element {
    // char open; // not needed
    char close;
    struct element* next;
};

// Append the new element to the start of the stack
// This is one potential way to write this function signature
/*struct element* push (
    struct element* stack,
    // char open, // not needed
    char close
) {
    struct element *bracket = malloc(sizeof(struct element));
    bracket->close = close;
    bracket->next = stack;

    stack = bracket;

    return stack;

}*/
void push (
    struct element** stack,
    char close
) {
    struct element* newElement = malloc ( sizeof ( struct element ) );
    newElement->close = close;
    newElement->next = *stack;
    *stack = newElement;
    return;
}


// Remove element from the top of the stack
char pop ( struct element** stack ) {

    if (*stack != NULL) {
        struct element* temp = *stack;
        char close = temp->close;
        *stack = temp->next;
        free ( temp );
        return close;
    } else {
        //perror("Empty stack");
        return '\0';
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;

    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {

        switch(buff) {
            case '<' :
                push(&root, buff);
                break;
            case '(' :
                push(&root, buff);
                break;
            case '[' :
                push(&root, buff);
                break;
            case '{' :
                push(&root, buff);
                break;
            case '>' :
                if(pop(&root)!='<'){
                    printf("no");
                    fclose(fp);
                    return 0;
                }
                break;
            case ')' :
               if(pop(&root)!='('){
                    printf("no");
                    fclose(fp);
                    return 0;
                }
                break;
            case ']' :
                if(pop(&root)!='['){
                    printf("no");
                    fclose(fp);
                    return 0;
                }
                break;
            case '}' :
                if(pop(&root)!='{'){
                    printf("no");
                    fclose(fp);
                    return 0;
                }
                break;
            default :
                printf("Invalid character\n" );
        }
    }

    if(root==NULL){
        balanced = true;
    }
    else{
        balanced = false;
    }

    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}

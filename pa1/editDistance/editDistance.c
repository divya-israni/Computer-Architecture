#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min ( size_t x, size_t y ) {
    return x<y ? x : y;
}

size_t levenshtein_recursive ( char* source, char* target ) {

    // printf( "source=%s\n", source );
    // printf( "target=%s\n", target );

    if (strlen(source)==0) return strlen(target);
    else if (strlen(target)==0) return strlen(source);
    else if (source[0]==target[0]) return levenshtein_recursive (source+1, target+1);
    else {
        size_t ins = levenshtein_recursive (source+1, target  );
        size_t del = levenshtein_recursive (source,   target+1);
        size_t sub = levenshtein_recursive (source+1, target+1);
        return 1 + min( min(ins,del), sub );
    }

}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf (inputFile, "%s\n%s", source, target);
    
    int length1;
    int length2;
    length1 = strlen(source);
    length2 = strlen(target);

    if(length1==0){
        return length2;
    }
    if(length2==0){
        return length1;
    }

    /*int** arr = malloc(length1 * sizeof(int*));
    for(int i=0; i<length1; i++){
        arr[i] = malloc(length2 * sizeof(int));
    }*/
    /*int** arr;
    arr = malloc(length1 * sizeof(int *));
    for(int i=0; i<length1; i++){
        arr[i] = malloc(length2 * sizeof(int));
        *(arr+i) = arr[i] (btw)
    }

    for(int i=0; i<length1; i++){
        free(arr[i]);
        OR free(*(arr+i)); (try?)
    }
    free(arr);
    */

    int arr[100][100];
    
    for(int r=0; r<length1; r++){
        arr[r][0] = r;;
    }
    for(int c=0; c<length2; c++){
        arr[0][c] = c;
    }

    for(int i=1; i<=length1; i++){
        for(int j=1; j<=length2; j++){

            int check;
            if(source[i-1] == target[j-1]){
                check=0;
            }
            else{
                check=1;
            }

            int first = arr[i-1][j]+1;
            int second = arr[i][j-1]+1;
            int third = arr[i-1][j-1] + check;
            int result = min(first, second);
            arr[i][j] = min(result, third);
        }
    }

    printf("%d\n", arr[length1][length2]);

   /* for(int i=0; i<length1; i++){
        free(arr[i]);
    }
    free(arr);*/
    return EXIT_SUCCESS;

}

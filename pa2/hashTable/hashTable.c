#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define RESTOCK "RESTOCK"
#define SHOW_STOCK "SHOW_STOCK"
#define SALE "SALE"

// Author: @nate-blum

typedef struct HashNode {
    int count;
    char* album_name;
    struct HashNode* next;
} HashNode;

static HashNode** table = NULL;
static int table_fullness = 0, table_size = 4;

int hash(char* str) {
    unsigned long long hash = 0;
	int len = (int) strlen(str);
    for (int i = 0; i < len; i++){
        hash += str[i] * pow(31, len - (i + 1));
	}
    return hash % table_size;
}

void pretty_print_table() {
	// Implement pretty printing of the hash tabled
	// based on the format of the answers
	printf("-------- FINAL COUNTS --------\n");
	for(int i=0; i<table_size; i++){
		HashNode* current = table[i];
		while(current!=NULL){
			printf("%s: %d\n", current->album_name, current->count);
			current = current->next;
		}
	}
	printf("------------------------------\n");
}

void resize() {
	printf("Resizing the table from %d to %d\n", table_size, table_size*2);
	// Implement resize logic here
	int old_size = table_size;
	table_size = table_size * 2;
	table_fullness = 0;
	HashNode** new_table = (HashNode**)malloc(table_size * sizeof(HashNode*));
	for(int i=0; i<table_size; i++){
		new_table[i] = NULL;
	}
	for(int i=0; i<old_size; i++){
		HashNode* current = table[i];
		while(current!=NULL){
			HashNode* temp = current->next;
			int index = hash(current->album_name);
			table_fullness++;
			current->next = new_table[index];
			new_table[index] = current;
			current = temp;
		}
	}
	free(table);
	table = new_table;
}

void update(char* album, int k) {
	
	int index = hash(album);
	HashNode* current = table[index];
	bool found = false;

	if(current == NULL && k<0){
		printf("No stock of %s\n", album);
	}
	else if(current == NULL && k>=0){
		table_fullness++;
		current = (HashNode*)malloc(sizeof(HashNode));
		current->count = k;
		current->album_name = strdup(album);
		current->next = table[index];
		table[index] = current;
	}
	else if(current!=NULL && k<0){
		while(current!=NULL){
			if(strcmp(current->album_name, album)==0){
				found = true;
				if(current->count >= (k * -1)){
					int newCount = current->count + k;
					current->count = newCount;
					break;
				}
				else{
					printf("Not enough stock of %s\n", album);
				}
			}
			current = current->next;
		}
		if(!found){
			printf("No stock of %s\n", album);
		}
	}
	else if(current!=NULL && k>0){
		while(current!=NULL){
			if(strcmp(current->album_name, album)==0){
				found = true;
				int currCount = current->count;
				currCount+=k;
				current->count = currCount;
				break;
			}
			current = current->next;
		}
		if(!found){
			HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
			newNode->count = k;
			newNode->album_name = strdup(album);
			newNode->next = table[index];
			table[index] = newNode;
			table_fullness++;
		}
	}
	
	double load_factor = (double)table_fullness/table_size;
	//int half_size = table_size/2;
	if(load_factor>=0.5){
		resize();
	}
	// Implement update logic here
	// Remember to resize if necessary

}

int retrieve(char* album_name) {
	// Implement retrieve logic here
	// Remember to account for non-existent searches (must return -1)
	int index = hash(album_name);
	HashNode* current = table[index];
	while(current!=NULL){
		if(strcmp(current->album_name, album_name)==0){
			return current->count;
		}
		current = current->next;
	}
	free(current);
	return -1;
}

void free_table() {
	// Make sure to properly free your hash table
	for(int i=0; i<table_size; i++){
		HashNode* current = table[i];
		while(current!=NULL){
			HashNode* temp = current;
			current = current->next;
			free(temp->album_name);
			free(temp);
		}
		free(current);
	}
	free(table);
}

int main(int argc, char* argv[]) {

	FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

	if (!fscanf(fp, "%d\n", &table_size)) {
        perror("Reading the initial size of the table failed.\n");
        exit(EXIT_FAILURE);
    }

    char command[20], album[150];
	int count;
	table = (HashNode**)malloc(table_size * sizeof(HashNode*));
	for(int i=0; i<table_size; i++){
		table[i] = NULL;
	}
    while (fscanf(fp, "%s %d %[^\n]s", command, &count, album) == 3) {
		if (strcmp(command, SALE) == 0) {
			// *** //
			update(album, count*-1);
			
		} else if (strcmp(command, RESTOCK) == 0) {
			// *** //
			update(album, count);
			
		} else if (strcmp(command, SHOW_STOCK) == 0) {
			//***//
			int stock = retrieve(album);
			if(stock>=0){
				printf("Current stock of %s: %d\n", album, stock);
			}
			else{
				printf("No stock of %s\n", album);
			}
		}
    }

	pretty_print_table();
	free_table();
    return 0;
}
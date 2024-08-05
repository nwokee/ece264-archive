// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	//Allocate and initialize an empty Path linked list
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

// Read the comments in list.h 
// to understand what you need to implement
// for each function
bool helpFree(PathNode ** p){
	if(*p == NULL){return false;}
	PathNode * f = *p;
	*p = f->next;
	freeNode(f);
	return true;
}

void freePaths(PathLL * p) {
	// Remove all paths in linked list, deallocate Path LL structure	
	while(helpFree(&(p->head))){}
	free(p);
}

PathNode * buildNode(char * path) {
	//Allocate a new PathNode with path as its data, return the address
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
	//builds a node containing the path

	// Allocate Size For Node
	PathNode * node = malloc(sizeof(PathNode));
	int allocateLength = strlen(path) + 1; // Length to allocate Value
	node -> path = malloc((allocateLength) * sizeof(char));
	
	
	strcpy((node -> path), path);
	node -> next = NULL;  
	return node;
}

void freeNode(PathNode * p) {
	
	free(p -> path);
	p -> next = NULL;
	free(p);
}

int numTurns(char * path){
	int countTurn = 0;
	int k = 0;
	char variable = path[0];

	while(path[k] != '\0'){ 
		if(variable != path[k]){++countTurn;} 
	variable = path[k];
	++k;
	}
	return countTurn;
}

int compareLength(char * path_1, char * path_2){
	
	
	int pathDiff = strlen(path_1) - strlen(path_2);
	int turnDiff = numTurns(path_1) - numTurns(path_2);

	return (pathDiff != 0) ? pathDiff :
	((turnDiff != 0) ? turnDiff : strcmp(path_1, path_2));
	
	
}


PathNode ** findNextNode(PathNode** k, char *path){
	while((*k != NULL) && ((compareLength((*k) -> path, path)) < 0)){
		k = &((*k) -> next);
	}
	return k;
}

void addAnotherNode(PathNode** k, char *path){
	PathNode *add = buildNode(path);
	add -> next = *k;
	*k = add;
}

PathNode * findDeleteNode(PathNode * p, char *path){
	while((p != NULL) && (!(strcmp((p) -> path, path) == 0))){
		p = (p->next);
	}
	return p;
}

bool addNode(PathLL * paths, char * path) {
/*Add a path to the list of paths
  PathLL should be sorted by the following priority
  1. In ascending order of length (shortest path first), then
  2. By number of turns (see README), then
  3. Alphabetical order
 
  return true if the node is added successfully 
*/
	PathNode** p = findNextNode(&(paths -> head), path);
	if((*p != NULL) && (!strcmp((*p) -> path, path))){
		return false;
	}

	addAnotherNode(p, path);
	return true;

	
}

bool removeNode(PathLL * paths, char * path) {
	
	/*Remove a node from the list with the specified path
  return true if the node exists and is removed, false otherwise
*/
	PathNode * k = findDeleteNode((paths -> head),path);
	return helpFree(&k);

}

bool containsNode(PathLL * paths, char * path) {
	/* Return true if path exists in the list */

	return (findDeleteNode((paths -> head),path)) != NULL;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * current = paths->head;
	int i = 0;
	while (current != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, current->path);
		i++;
		current = current->next;
	}
}




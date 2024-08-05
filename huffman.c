#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

long TreeNodeCount(TreeNode *node){
    if(node == NULL){
        return(0);
    }
    return(node -> count);
}

TreeNode *buildTreeNode(int label, TreeNode *left, TreeNode *right){
    TreeNode *ptr = malloc(sizeof(TreeNode));
    
    if(ptr == NULL){
        return NULL;
    }

    (ptr -> label) = label;
    (ptr -> count) = TreeNodeCount(left) + TreeNodeCount(right);
    (ptr -> left) = (left);
    (ptr -> right) = (right);
    
    return(ptr);
}

ListNode *addListNode(ListNode **list, TreeNode *new_object, int (*cmpFunction)(TreeNode *, TreeNode *)){
    if(new_object == NULL){
        return NULL;
    }
    
    ListNode *node = malloc(sizeof(ListNode));
    if(node == NULL){
        return NULL;
    }

    ListNode dummy;
    dummy.next = *list;
    ListNode *previous = &dummy;
    ListNode *current = *list;

    while(current != NULL){
        if(cmpFunction(current -> ptr, new_object) >= 0){
            break;
        }
        else{
            previous = current;
            current = current -> next;
        }
    }

    node -> ptr = new_object;
    node -> next = current;
    previous -> next = node;
    *list = dummy.next;
    
    return(node);
}

int treeNodeCompare(TreeNode *tp1, TreeNode *tp2){
    long difference;
    difference = (tp1 -> count) - (tp2 -> count);

    if(difference == 0){
        return((tp1 -> label) - (tp2 -> label));
    }

    if(difference < 0){return(-1);}
    return(1);
}


void printList(const ListNode *list, FILE * fp){
    while(list != NULL){
        fprintf(fp, "%c:", (list -> ptr -> label));
        fprintf(fp, "%ld\n", (list -> ptr -> count));
        list = list -> next;
    }
}

TreeNode *buildHuffmanTree(ListNode *list){
   int label = ASCII_SIZE;
   ListNode *firstNode = removeListNode(&list);
   
   while(firstNode != NULL){
    ListNode *secondNode = removeListNode(&list);
      if (secondNode == NULL){
            TreeNode *huffman = (TreeNode *)firstNode -> ptr;
            free(firstNode);
            return huffman;
      }

        TreeNode *newTreeNode;
        newTreeNode = buildTreeNode(label, (TreeNode *)firstNode -> ptr, (TreeNode *)secondNode -> ptr);
        free(firstNode);
        free(secondNode);

        if(newTreeNode == NULL){
            fprintf(stderr,"Error: newTreeNode is NULL.\n");
            freeList(list);
            return NULL;
        }
        ListNode *var = addListNode(&list, newTreeNode, treeNodeCompare);
        
        if(var == NULL){
            fprintf(stderr,"Error: var is NULL.\n");
            freeHuffmanTree(newTreeNode);
            freeList(list);
            return NULL;
        }
        firstNode = removeListNode(&list);
        label++;
   }
   return NULL;
}

void freeHuffmanTree(TreeNode *ptr){
    if(ptr == NULL){
        return;
    }

    freeHuffmanTree(ptr -> left);
    freeHuffmanTree(ptr -> right);
    free(ptr);
}

int isLeafNode(const TreeNode *node){
    if(node == NULL){
        return(0);
    }
    if((node -> left == NULL) && (node -> right == NULL)){
        return(1);
    }
    return(0);
}

void freeList(ListNode *list){
    while(list!= NULL){
        ListNode *temp = list -> next;
        freeHuffmanTree(list -> ptr);
        free(list);
        list = temp;
    }
}

ListNode *removeListNode(ListNode **list){
    ListNode *node = *list;
    if(node != NULL){
        *list = node -> next;
        node -> next = NULL;
    }
    return(node);
}

void huffmanPrintHelper(const TreeNode *ptr, int index, char *array, FILE *file){
    if(ptr == NULL) {return;}
    
    if(isLeafNode(ptr) == 1){
        fprintf(file, "%c:", ptr -> label);
        for(int i = 0; i < index; i++){
            fprintf(file, "%c", array[i]);
        }
        fprintf(file, "\n");
        return;
    }

    array[index] = '0';
    huffmanPrintHelper(ptr -> left, index + 1, array, file);
    array[index] = '1';
    huffmanPrintHelper(ptr -> right, index + 1, array, file);
}

void huffmanPrint(const TreeNode *ptr, FILE * fp){
    if(ptr == NULL){return;}

    char huffman[ASCII_SIZE];
    huffmanPrintHelper(ptr, 0, huffman, fp);
}

void printHuffmanTree(char *file, TreeNode *huffmanTree){
    FILE *ptr = fopen(file,"w");
    if(ptr == NULL){
        fprintf(stderr, "No File for printHuffmanTree\n");
    }
    huffmanPrint(huffmanTree, ptr);
    fclose(ptr);
}

void sortASCIICount(char *file, ListNode *ptr){
    FILE *fp = fopen(file, "w");

    if(fp == NULL){
        fprintf(stderr, "File could not be opened.\n");
    }

    printList(ptr, fp);
    fclose(fp);
}

ListNode * makeHuffmanBook(long *asciiCount){
   ListNode *List = NULL;
   for(int i = 0; i < ASCII_SIZE; i++){
      if (asciiCount[i] > 0){
         TreeNode *ptr = buildTreeNode(i, NULL, NULL);
            if(ptr == NULL){
               freeList(List);
               printf("ptr is NULL\n");
               return NULL;
            }
            ptr -> count = asciiCount[i];
         ListNode *NewList = addListNode(&List, ptr, treeNodeCompare);
         if(NewList == NULL){
            printf("NewList is NULL\n");
            freeHuffmanTree(ptr);
            freeList(List);
            return NULL;
         }
      }
   }
   return List;
   
}

void printHeaderHelper(FILE *file, TreeNode *ptr, int *current_count, int *current_byte){
    if(ptr == NULL){return;}

    const int BYTE_SIZE = 8;

    if(isLeafNode(ptr) == 1){
        int position = BYTE_SIZE - 1 - *current_count;
        int one_bit = 1 << position;
        *current_byte = *current_byte | one_bit;
        *current_count += 1;

        if(*current_count == BYTE_SIZE){
            fputc(*current_byte, file);
            *current_byte = 0;
            *current_count = 0;
        }

        if(*current_count == 0){fputc(ptr -> label, file);}
        else{
            *current_byte = *current_byte | (ptr -> label >> *current_count);
            fputc(*current_byte, file);
            int MS_Count = BYTE_SIZE - *current_count;
            *current_byte = (ptr->label & (0xFF >> MS_Count)) << MS_Count;
        }
        return;
    }
    *current_count += 1;
    if(*current_count == BYTE_SIZE){
            fputc(*current_byte, file);
            *current_byte = 0;
            *current_count = 0;
        }
        printHeaderHelper(file, ptr -> left, current_count, current_byte);
        printHeaderHelper(file, ptr -> right, current_count, current_byte);
}

void printHeader(char *file, TreeNode *huffmanTree){
    FILE *fptr = fopen(file, "w");

    if(fptr == NULL){
        fprintf(stderr, "Error: Header File is NULL");
        //return;
    }

    int current_count = 0;
    int current_byte = 0;

    printHeaderHelper(fptr, huffmanTree, &current_count, &current_byte);
    if(current_count == 0){
        fputc(0,fptr);
    }

    else{
        fputc(current_byte, fptr);
    }
    fclose(fptr);
}
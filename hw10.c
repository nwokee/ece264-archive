// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "hw10.h"

// DO NOT MODIFY this function --->>>
void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL) // the linked list must end with NULL
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}
// <<<--- until here

// You MUST modify the following functions

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
// the linked list must end with NULL
ListNode * createList(int valn)
{
  struct node * head = NULL;
  struct node * temp = NULL;
  struct node * p = NULL;
  for(int x = 0; x < valn; x++)
  {
    temp = (struct node*)malloc(sizeof(struct node));
    temp->value = x;
    temp->next = NULL;
    if(head == NULL)
    {
      head = temp;
    }
    else
    {
      p = head;
      while(p->next != NULL)
      {
        p = p-> next;
      }
      p->next = temp;
    }
  }
  return head;
}
#endif

#ifdef TEST_ELIMINATE
// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk)
{
  struct node * p;
  p = head;
  int counter;

  while(head->next != NULL)
  {
    counter = valk;
    while(counter > 0)
    {
      if(p != NULL)
      {
        counter--;
      }
      struct node * q = p -> next;
      if(counter == 0)
      {
        #ifdef DEBUG
        // this #ifdef ... #endif should be inside the condition *BEFORE* a
        // node' value is printed and it is deleted
        ListNode * todelete = p;
        printListNode (todelete); 
        #endif
        printf("%d\n", p -> value);
        head = deleteNode(head, p);
      }
      if(q != NULL)
      {
        p = q;
      }
      else
      {
        p = head;
      }
      
    }
    
  }
  printf("%d\n", head -> value);
  free(head);
  
  
}
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete)
{
  if(head == NULL)
  {
    return NULL;
  }
  if(head == todelete)
  {
    struct node * newhead = head->next;
    free(head);
    return newhead;
  }
  if(todelete == NULL)
  {
    return head;
  }
  
   // struct node * current = head->next; 
    struct node * temp = head;
    while((temp != NULL) && ((temp->next) != todelete))
    {
      
      temp = temp -> next;
    }
    if(temp != NULL)
    {
      temp -> next = todelete -> next;
      free(todelete);
    }
  return head;
}
#endif



// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
Tree * newTree(void)
{
  Tree * t = malloc(sizeof(Tree));
  t -> root = NULL;
  return t;
}

void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}


// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***
#ifdef TEST_BUILDTREE
TreeNode * createNode(int val)
{
  TreeNode * head = (TreeNode*)malloc(sizeof(TreeNode));
  head->value = val;
  head->left = NULL;
  head->right = NULL;
  return head;
}

int search(int * inA, int st, int en, int val)
{
  for(int x = st; x <= en; x++)
  {
    if(inA[x] == val)
    {
      return x;
    }
  }
  return -1;
}

TreeNode * buildSide(int * inA, int * postA, int strt, int end, int* pIndex)
{
  if(strt > end)
  {
    return NULL;
  }
  int newval = postA[*pIndex];
  TreeNode * head = createNode(newval);
  (*pIndex)--;

  if(strt == end)
  {
    return head;    
  }

  int iIndex = search(inA, strt, end, newval);

  if(iIndex == -1)
  {
    fprintf(stderr, "SOMETHING WRONG\n");
  }

  head->right = buildSide(inA, postA, iIndex+1, end, pIndex); 
  head->left = buildSide(inA, postA, strt, iIndex-1, pIndex);

  return head;
  
}

Tree * buildTree(int * inArray, int * postArray, int size)
{
  int pIndex = size-1;
  Tree * x = (Tree*)malloc(sizeof(Tree));
  x->root = buildSide(inArray, postArray, 0, size-1, &pIndex);
  return x;
}
#endif

#ifdef TEST_PRINTPATH
int printPathHelp(TreeNode * node, int val)
{
  if(node == NULL)
  {
    return 0;
  }
  if(node->value == val)
  {
    printf("%d ", node->value);
    return 1;
  }
  if(printPathHelp(node->left, val) == 1)
  {
    printf("%d ", node->value);
    return 1;
  }
  if(printPathHelp(node->right, val) == 1)
  {
    printf("%d ", node->value);
    return 1;
  }
  return 0;
}

void printPath(Tree * tr, int val)
{
  if(tr == NULL)
  {
    return;
  }
  printPathHelp(tr->root, val);
  printf("\n");
}
#endif

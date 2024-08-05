// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
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

static void preOrderTraversal(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    {
      return;
    }
  fprintf(fptr, "%d\n", tn -> value);
  preOrderTraversal(tn -> left, fptr);
  preOrderTraversal(tn -> right, fptr);
}

void preOrderToFile(Tree * tr, char * filename)
{
  if (tr == NULL)
    {
      return;
    }
  FILE * fptr = fopen(filename, "w");
  preOrderTraversal(tr -> root, fptr);
  fclose (fptr);
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***

#ifdef TEST_BUILDTREE
// Consider the algorithm posted on
// https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
// Feel free to add helper functions
// inArray: an integer array containing the in-order traversal output
// postArray: an integer array containing the post-order traversal output
// size: number of integers in inArray or postArray
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

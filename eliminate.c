/* You MUST modify this file */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#ifdef TEST_ELIMINATE
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
	
  // Note that from here on, you can access elements of the arr with
  // expressions like a[i]
	
  // initialize all elements
  int eliminated = 0, counter = 1;
  while (eliminated < n)
  {
    for(int idx = 0; idx < n; idx++)
    {
      if(arr[idx] != -1)
      {
        if(counter >= k)
        {
          counter = 1;
          arr[idx] = -1;
          printf("%d\n", idx);
          eliminated++;
        }
        else
        {
          arr[idx] = 1;
          counter++;
        }
      }
    }
  }

  
  // counting to k,
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked




  // print the last one




  // release the memory of the array
  free (arr);
}
#endif

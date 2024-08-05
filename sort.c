/* MODIFY this file */

#include "sort.h"

void ssort(int * arr, int size) {
	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */
	#ifdef ASCENDING
	int asc = 1;
	#else
	int asc = -1;
	#endif
	
	for (int x = 0; x < size; x++)
	{
		int index = x;
		for (int y = x; y < size; y++)
		{
			if((asc * arr[y]) < (asc * arr[index]))
			{
				index = y;

			}
		}
		int temp = arr[x];
		arr[x] = arr[index];
		arr[index] = temp;
	}
}


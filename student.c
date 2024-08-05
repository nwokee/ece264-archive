// ***
// *** You MUST modify this file
// ***

#include "hw5.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void StudentPrint(Student * stu, int num)
{
  printf("There are %d students\n", num);
  for (int ind = 0; ind < num; ind ++)
  {
    printf("ID = %d, Name = %s\n", stu[ind].ID, stu[ind].name);
  }
}

// count the number of '\n' to determine the number of records
int countNewLine(FILE * fptr) 
{
  int numline = 0;
  while (! feof(fptr))
  {
    int onechar = fgetc(fptr);
    if (onechar == '\n')
    {
	    numline ++;
    }
  }
  return numline;
}

/* This is the first function you need to implement */
#ifdef TEST_READ
bool StudentRead(char * filename, Student * * stu, int * numelem)
{
  /* 1.1: open the file to read */
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    fprintf(stderr, "fopen fail\n");
    return false;
  }
  // the name of the file to open is stored in filename
  // if fopen fails, return false
  // do not use fclose since fopen already fails
  
  /* end of 1.1: open the file to read */
	
	
  int numline = countNewLine(fptr);
  
  // return to the beginning of the file
  // you can use fseek or
  // fclose followed by fopen
  // You need to check whether fseek or fopen fails
  // Do not use rewind because it does not report whether it fails
  int rtv; // return value
  rtv = fseek(fptr, 0, SEEK_SET);
  if (rtv == -1) // fseek fails
    {
      fclose (fptr);
      return false;
    }
  
	
  /* 1.2 allocate memory for the data */
  Student * stuptr = (Student *) malloc(numline * sizeof(Student));;
  // stuptr is an array of type Student
  // refer to hw5.h to understand the type Student
  // the number of elements in this array is numline
  // use the malloc function
  // check whether memory allocation fails
  
  /* end of 1.2: allocate memory for the data */

	for(int x = 0; x < numline; x++)
  {
    int stdid;
    char stdname[NAME_LENGTH];
    if (fscanf(fptr, "%d", &stdid) != 1 || fscanf(fptr, "%s\n", stdname) != 1)
    {
      free(stuptr);
      fclose(fptr);
      return false;
    }
    stuptr[x].ID = stdid;
    strcpy(stuptr[x].name, stdname);
  }
	
  fclose(fptr);
	
  /* 1.3: read data from the file */
  // read the data from the file
  // store the data to the array stuptr
  // fclose the file after read of data is done

  /* end of 1.3: allocate memory for the data */

	
	
  * numelem = numline;
  * stu = stuptr;
  return true;
}
#endif



/* This is the second function you need to implement */
#ifdef TEST_WRITE
bool StudentWrite(char * filename, Student * stu, int numelem)
{
  // open the file to write
  // the name of file to open is stored in string filename
  // if fopen fails, return false
  FILE * wptr = fopen(filename, "w");
  if (wptr == NULL)
  {
    fprintf(stderr, "fopen fail\n");
    return false;
  }
  // do not use fclose since fopen already fails
  // stu is an array of type Student
  // refer to hw5.h to understand the type Student
  // the number of elements in array stu is numelem
  for(int x = 1; x < numelem ; x++)
  {
    if(fprintf(wptr, "%d %s\n", stu[x].ID, stu[x].name) < 1)
    {
      fclose(wptr);
      return false;
    }
  }
  // write the data from array stu to the opened file
  // fclose the file in the end
  fclose(wptr);
  return true;

}
#endif



/* This is the third function you need to implement */
#ifdef TEST_QSORT
void sortStudents(Student * stu, int numelem, int (*compar)(const void *, const void *)) 
{
  /* Fill in to call qsort function to sort array stu */
  qsort(stu, numelem, sizeof(Student), compar);
  // stu: an array of Students. numelem: number of elements in the array. compar: comparison function
  // refer to hw5.h to understand the type Student

}
#endif



/* This is the fourth function you need to implement */
#ifdef TEST_SORTID
int compareID(const void * p1, const void * p2)
{
  /* Fill in to compare p1 and p2 by id */
  const Student * st1 = (const Student*) p1;
  const Student * st2 = (const Student*) p2;
  int one = st1->ID, two = st2->ID;
  
  if(one < two)
  {
    return -1;
  }
  else if (one == two)
  {
    return 0;
  }
  return 1;
  // return a negative value if the ID of the first student is smaller
  // return a positive value if the ID of the first student is larger
  // return zero if the IDs of the two students are the same
    
}
#endif



/* This is the fifth function you need to implement */
#ifdef TEST_SORTNAME
int compareName(const void * p1, const void * p2)
{
  const Student * st1 = (const Student*) p1;
  const Student * st2 = (const Student*) p2;
  return strcmp(st1->name, st2->name);
  /* Fill in to compare p1 and p2 by name */
  // use strcmp function to compare two strings
  // return a negative value if the name of the first student is alphabetically earlier
  // return a positive value if the name of the first student is alphabetically later
  // return zero if the names of the two students are the same
   
}
#endif



/* This is the sixth function you need to implement */
#ifdef TEST_SORTED
bool areStudentsSorted(Student * stu, int numelem, int (*compar)(const void *, const void *)) {
  /* Fill in to check if the stu array is sorted according to compar */
  for(int x = 0; x < numelem-1; x++)
  {
    const void * s1 = &stu[x];
    const void * s2 = &stu[x+1];
    if(compar(s1, s2) == 1)
    {
      return false;
    }

  }
  return true;
  // return true if the stu array is sorted according to compar
  // return false otherwise
  // refer to hw5.h to understand the type Student
    
}
#endif
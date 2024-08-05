// ***
// *** DO NOT modify this file
// ***

#ifndef HW5_H
#define HW5_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NAME_LENGTH 80
#define LINE_LENGTH 80

typedef struct
{
  int ID;
  char name[NAME_LENGTH];
} Student;

void StudentPrint(Student * stu, int num);
int countNewLine(FILE * fptr);
bool StudentRead(char * filename, Student * * stu, int * numelem);
bool StudentWrite(char * filename, Student * stu, int numelem);
void sortStudents(Student * stu, int numelem, int (*compar)(const void *, const void *));
int compareID(const void * p1, const void * p2);
int compareName(const void * p1, const void * p2);
bool areStudentsSorted(Student * stu, int numelem, int (*compar)(const void *, const void *));

#endif

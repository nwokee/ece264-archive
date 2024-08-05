# Homework 5: QSort

## Goals 

In HW4 you've learned how to read and write file in C program.
You will continue to use the file operation function in this assignment.

This assignment asks you to write a program that uses *qsort*
to sort an array of integers in the ascending order.
Note that in this homework you do not need to write the *qsort* algorithm,
but to call the C library function `qsort` for sorting.


You will learn to
* Read unsorted data from files
* Write sorted data to another file
* Call `qsort` function to sort the student records according to IDs or names
* Allocate memory (an array) dynamically
* Release memory
* Check memory error using `valgrind`

## Background

### 1. Dynamic memory allocation

In this assignment, you will use `malloc` function to allocate dynamic function.

`void * malloc(size_t size)` allocates the requested memory, and returns a pointer to it,
or returns NULL if the allocation fails.

You should always deallocate the memory with the `void free(void *ptr)` function when you are done using the memory.

For example, 

```
int * arr = (int *) malloc(10 * sizeof(int)); // allocates the memory for 10 integers
void free(arr); // releases the allocated memory
```

You will use the `valgrind` tool to debug memory, and detect memory leak.
Check [here](http://cs.ecs.baylor.edu/~donahoo/tools/valgrind/messages.html) for the various types of errors that you may have.

For example, to use a valgrind to check a program `hw5` for memory errors with input file `filename`, run the following command:

`> valgrind --tool=memcheck --leak-check=yes ./hw5 filename`


### 2. QSort

QSort is a built-in function in C for sorting arrays based on quick sort algorithm.
In this assignment, you **do not** need to implement the qsort function.
Instead, you will need to read the [`qsort` function](https://linux.die.net/man/3/qsort)
and understand how to use this `qsort` function. The QSort algorithm is based on recusion.
You will learn the algorithm later when we discuss recussion in class.

To use qsort, you need to provide four arguments:

* the address of the first element
* the number of elements
* the size of each element
* the function for comparing elements


### 3. strcmp function

`strcmp` function's signature is: `int strcmp(const char *s1, const char *s2)`. It takes two char arrays (i.e., strings) and compares them alphabetically. It returns a negative number if the first string is alphabetically earlier, 0 if the two strings are the same, and a positive number if the second string is alphabetically earlier.

> Note that `strcmp` handles capitalization weird: it assumes that all capital letters are alphabetically earlier than all lowercase letters (so "aardvark" is before "zebra" (as expected); "Zebra" is before "aardvark" (because all capital letters come before any lower-case letters); and "Aardvark" is before "Zebra" (because when both letters are capitalized, it goes back to "regular" alphabetical order). In this assignment, you can assume that all names are consistently capitalized, so the weird handling of capitalization doesn't matter.


## What do you need to do?

You need to modify only one files (`student.c`) and complete the following functions:
 * `bool StudentRead(char * filename, Student * * stu, int * numelem)`
 * `bool StudentWrite(char * filename, Student * stu, int numelem)`
 * `void sortStudents(Student * stu, int numelem, int (*compar)(const void *, const void *))`
 * `int compareID(const void * p1, const void * p2)`
 * `int compareName(const void * p1, const void * p2)`
 * `bool areStudentsSorted(Student * stu, int numelem, int (*compar)(const void *, const void *))`

Read the comments for each of the functions to understand what you need to do.
For the two comparison functions (`compareID` and `compareName`), each of them has three steps:

* cast the type from `void *` to the proper type (it is a pointer). For example in `compareID`, you can use `const Student * st1 = (const Student *) p1;` to cast from pointer p1 (of type `const void *`) to type `const Student *` and assign its value to st1 (of type `const Student *`)
* retrieve the values from the pointer
* compare the values and return negative, zero, or positive numbers

To compare two IDs, you'll use the numeric difference.
To compare two names (strings), you'll use `strcmp` function.


### Testing for memory leak

Note that in the Makefile that is provided to you, there is one target line for `testmemory`.
Run the Makefile with the target `testmemory` will check for memory errors using the `valgrind` tool.
The log of memory leak check will be stored in log files named `log1`, `log2`, `log3`, `log4` (for example,
in the Makefile, we define the command for valgrind with option `--log-file=log1` for the first testcase)

In summary, for memory leak, run the following commands:
```
> make testmemory
> cat log1 # this only checks the memory log file for testcase 1
``` 
where the first command runs the `valgrind` tool and the second command displays the memory check log for testcase 1.


## Grading

You will receive zero if your program has error or warning from `gcc`.

You will lose 1 point for every 1 byte of memory leak. In other words, if your program leaks 100 or more bytes, you will **receive zero**.

You will receive zero if your program terminates abnormally (e.g., segmentation fault).

You will lose 1 point for every error detected by valgrind even though the program continues.

The grading will be based on the test cases run by the teaching staffs. 
Your score is proportional to the number of testcases that your program passes. 
Passing means the program returns EXIT_SUCCESS and provides correct outputs that match the expected outputs.

You **must** follow the instructions precisely. Failing to follow
these instructions will likely make you receive zero in this assignment.

# Homework 10: Who Gets the Cake (Part 2)

## Goals 

In HW2, we address the "who gets the cake" problem using array,
in this assignment, we will use a different data structure (linked list)
to work on the same problem.

You will learn to:

* Create a linked list 
* Insert and delete nodes in a linked list 

## Background

### 1. Changes from HW2

In HW2, an array is used to keep track who is still in the
game. In this assignment, a linked list is used. The output of your
program should match the output of HW2. In addition, the linked
list is printed every time one number is removed.

The files in `testcases` directory have `-DDEBUG` in Makefile to turn
on the code printing the lists starting from the nodes to be
eliminated.  If Makefile does not have `-DDEBUG`, the outputs should
be the same as the files in HW2.

### 2. Initialize Pointers

You should *always* initialize pointers to `NULL`. Many students lose
points unnecessarily because they do not initialize pointers to
`NULL`. Uninitialized pointers can make your programs' behavior
unpredictable. Many students lose points due to uninitialized
pointers.

### 3. Printing ListNode

You should call `printListNode` each time BEFORE you delete any node 
and print the node value. In the expected files, `printListNode` is not
called for the last value in the list. Follow the 
expected files format. You can turn on the `-DDEBUG` flag in your Makefile
for printing.

You must NOT use a circular linked list for this assignment. The
`printListNode` does not work if the input is a circular linked
list. Please do NOT modify the `printListNode` function, otherwise
your program will fail in grading.

## What do you need to do?

You will need to implement three functions in `hw10.c`. Read the comments
carefully in `hw10.c` to understand what to implement for the three functions.
```
ListNode * createList(int valn);
void eliminate(ListNode * head, int valk);
ListNode * deleteNode(ListNode * head, ListNode * todelete);
```

### 1. Testing your code

Same as HW2, to run your code, you will need two arguments: `n` (total number of nodes) and `k` (counting target).
And then, you'll need to put the output into a file using the `>` command.
For example, if your executable file is named `hw10`, you can use the following command to run your
program with `n=6, k=3` and put the output in `output1` file.

```
./hw10 6 3 > output1
```
We provide the expected output for three testcases in the `testcases` directory:

* n = 6, k = 3
* n = 4, k = 6
* n = 25, k = 7

And you can use the `diff` command to compare your output file with the expected file.

### Hints:
* Refer to the Makefile in HW2 and think about how to modify it to test HW10
* Be sure to include the testflag `-DDEBUG` in your gcc command
* Do NOT forget to check memory leak using `valgrind`.

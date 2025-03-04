
#ifndef STACK_H_
#define STACK_H_

#include <Arduino.h>

#define MAX_STACK_LEN 17 // maximum legnth of a stack

#define EXIT_OK       0
#define EXIT_ERR     -1

/////////////////////////////////////STRUCTS////////////////////////////////////

// Item structure
typedef struct item	{
  char my_message[17];
  char ;
} personal_message;

typedef struct stack {
  personal_message [MAX_STACK_LEN];
  int top;
} Stack, *pStack;

///////////////////////////////FUNCTION PROTOTYPES//////////////////////////////

// fills an array (of size num_stacks) with Stacks 
void CreateStackArray(Stack stack_array[], int num_stacks);

// creates a new StampedItem from timestam and data input parameters, and pushes
// it on the top of a stack. Returns EXIT_OK if it succeeds, and EXIT_ERR if not.
int Push(pStack stack, int timestamp, char data);

// pops top item from a stack, returns EXIT_OK if it succeeds, and EXIT_ERR if 
// it does not. The popped item's timestamp and char data are stored in passed
// by reference input parameters
int Pop(pStack stack, int& timestamp, char& data);

// pops all items from a stack
void PopAll(pStack stack);

// if stack is empty return true, otherwise, return false 
bool IsStackEmpty (pStack stack);

// if stack is full return true, otherwise, return false 
bool IsStackFull (pStack stack);


#endif

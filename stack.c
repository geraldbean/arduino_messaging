#include <stdio.h>
#include "Stack.h"

void CreateStackArray(Stack stack_array[]){
    Stack stack; 
    stack.top = -1; 
}

int Push(pStack stack, int timestamp, char data) {
  
  /*-------------------------insert your code here--------------------------*/
  //Look to see if the stack is full
  if(IsStackFull(stack)){
    Serial.print("Push failed because the stack is already full");
    return EXIT_ERR;
  }

  //If the stack is not full then push an item onto the top of the stack.
  //change the top to the new top each time something is added.
  stack->top++;

  stack->stack_of_items[stack->top+1].data=data;
  stack->stack_of_items[stack->top+1].timestamp=timestamp;
  

  // this return value will need to be changed once your code is written
  return EXIT_OK;
}

int Pop(pStack stack, int &timestamp, char &data) {

  /*-------------------------insert your code here--------------------------*/
  //Look to see if stack is empty.
    if(IsStackEmpty(stack)){
      Serial.print("Pop failed because the stack is empty.\n");
      return false;
    }

  //If the stack is not empty then store the item at the top of the stack in "data" through pass by pointer
   //you increment the top once for both the timestamp and the data because you only have one stack.
  stack->top--;

  data = stack->stack_of_items[stack->top].data;

  timestamp = stack->stack_of_items[stack->top].timestamp;
 

  // this return value will need to be changed once your code is written
  return EXIT_OK;
}

bool IsStackFull (pStack stack) {
  /*-------------------------insert your code here--------------------------*/
  //check to see if the top of the stack is the max length of the stack.
  if(IsStackFull(stack->top) == MAX_STACK_LEN-1){
    Serial.print("The stack is full");
    return EXIT_ERR;
  }else{
    Serial.print("The stack is not full");
    return EXIT_OK;
  }

  // this return value will need to be changed once your code is written
  //return false;
}

bool IsStackEmpty (pStack stack) {
   /*-------------------------insert your code here--------------------------*/
   //check to see if the top of the stack is -1 to see that it is empty.
   if(IsStackEmpty(stack->top)==-1){
    Serial.print("Stack is empty");
    return EXIT_ERR;
   }else{
    return EXIT_OK;
   }

}

void PopAll(pStack stack) {
  /*-------------------------insert your code here--------------------------*/
  //pop off the stack until you have nothing left to pop.
  //check if the stack is empty.
  if(IsStackEmpty(stack)){
    Serial.print("There is nothing to pop because the stack is empty");
    return EXIT_ERR;
  }
  stack->top == -1;
  return EXIT_OK;
}


long GetTime(DS3231 rtc_clock) {
  /*-------------------------insert your code here--------------------------*/
  bool h12;
  bool hPM;
  byte hr = (rtc_clock.getHour(h12,hPM));
  byte min = rtc_clock.getMinute();
  byte sec = rtc_clock.getSecond();
  long time = (hr*3600)+(min*60)+sec;


  // this return value will need to be changed once your code is written
  return time;
}

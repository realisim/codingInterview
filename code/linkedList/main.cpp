
#include "linkedList.h"
#include <iostream>

using namespace codingInterview;

void print(const doublyLinkedList& l)
{
  printf("number of element: %d\n"
         "%s\n", l.size(), l.toString().c_str() );
}

int main(int argc, char** argv)
{
  doublyLinkedList theList;
  
  //--- push back
  printf("\n");
  printf("push_backing a bunch of elements...\n");
  for(int i = 0; i < 15; ++i)
  {
    theList.push_back(i);
  }
  print(theList);
  
  //--- pop back
  printf("\n");
  int a = theList.pop_back();
  int b = theList.pop_back();
  int c = theList.pop_back();
  printf("pop_back last 3 elements: %d, %d, %d\n", a, b, c);
  print(theList);
  
  //--- push front
  printf("\n");
  printf("pushing 3 elements to the front\n");
  theList.push_front(a);
  theList.push_front(b);
  theList.push_front(c);
  print(theList);
  
  //--- pop front
  printf("\n");
  a = theList.pop_front();
  b = theList.pop_front();
  c = theList.pop_front();
  printf("pop_front last 3 elements: %d, %d, %d\n", a, b, c);
  print(theList);
  
  //--- copy constructor
  printf("\n");
  doublyLinkedList theList2(theList);
  printf("Copy constructor\n");
  print(theList2);
  
  //--- assignement
  printf("\n");
  printf("push_back 1,2,3 to new list.\n");
  theList2.push_back(1); theList2.push_back(2); theList2.push_back(3);
  print(theList2);
  printf("assigment operator, back to old list\n");
  theList2 = theList;
  print(theList2);
  
  
  //--- clear
  printf("\n");
  printf("clearing the list.\n");
  theList.clear();
  print(theList);

  return 0;
}
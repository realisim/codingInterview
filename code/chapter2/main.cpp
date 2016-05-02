
#include "linkedList.h"
#include <cstdio>

using namespace std;

//-----------------------------------------------------------------
int main(int argc, char** argv)
{
  printf("--- exercise 2.1\n");
  codingInterview::linkedList ll;
  ll.insert(1);
  ll.insert(1);
  ll.insert(2);
  ll.insert(2);
  ll.insert(3);
  ll.insert(3);
  ll.insert(4);
  ll.insert(4);
  printf("%s\n", ll.toStdString().c_str());
  ll.remove(1);
  printf("%s\n", ll.toStdString().c_str());
  
  return 0;
}
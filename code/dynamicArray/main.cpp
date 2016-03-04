

#include "reusable/dynamicArray.h"
#include <sstream>

using namespace codingInterview;
using namespace std;

template<typename T>
void print(const dynamicArray<T>& iDa)
{
  ostringstream oss;
  oss << "dynamic array\n" << "size: " << iDa.size() << endl <<
  "capacity: " << iDa.capacity() << endl;
  for(int i = 0; i < iDa.size(); ++i)
  {
    oss << "[" << iDa[i] << "] ";
  }
  printf("%s\n\n", oss.str().c_str());
}

struct point3
{
  point3() : x(0), y(0), z(0) {}
  
  double x;
  double y;
  double z;
};

int main(int argc, char** argv)
{
  dynamicArray<int> da;
  
  //push back some element
  for(int i = 0; i < 15; ++i)
  { da.push_back(i); }
  print(da);
  
  //random access non const
  int a = da[5];
  int b = da[6];
  int c = da[7];
  printf("random access to element 5, 6, 7 -> %d, %d, %d\n", a, b, c);
  
  //modify element 4,5,6
  da[5] = 22;
  da[6] = 23;
  da[7] = 24;
  printf("modified element 5, 6, 7 to 22, 23, 24\n");
  print(da);
  
  //clear
  da.clear();
  printf("after clear\n");
  print(da);
  
  //resize bigger
  da.resize(10, 5);
  printf("resize 10, 5\n");
  print(da);
  
  //resize smaller
  printf("resize smaller 5, 22\n");
  da.resize( 5, 22 );
  print(da);
  
  //memory leak test
//  for(int i = 0; i < 1000; ++i)
//  {
//    dynamicArray<int> da2;
//    da2.resize(1024*1024);
//  }
  
  //erase
  printf("clearing and inserting 15 elements.\n");
  da.clear();
  for(int i = 0; i < 15; ++i)
  { da.push_back(i); }
  print(da);
  
  printf("erasing elelment 2, 4, 6 (value 2,5,8)\n");
  da.erase(2);
  da.erase(4);
  da.erase(6);
  print(da);
  
  printf("erasing the last element\n");
  da.erase( da.size() - 1 );
  print(da);
  
  printf("push_back element 22\n");
  da.push_back( 22 );
  print(da);
  
  printf("erasing elelment 2, to 6 (value 3,4,6,7,9)\n");
  da.erase(2,6);
  print(da);
  
  printf("push_back element 23\n");
  da.push_back( 23 );
  print(da);
  
  printf("erasing elelment 3 to end \n");
  da.erase(3, da.size() -1);
  print(da);
  
  printf("push_back element 23\n");
  da.push_back( 24 );
  print(da);

  //erase in a loop.
  printf("clearing and inserting 15 elements.\n");
  da.clear();
  for(int i = 0; i < 15; ++i)
  { da.push_back(i); }
  print(da);
  
  printf("erasing in a loop from 5 to 10\n");
  int index = 5;
  for(int i = index; i <= 10; ++i)
  { index = da.erase(index); }
  print(da);
  
  //copy constructor
  printf("copy contructor\n");
  dynamicArray<int> da2(da);
  print(da2);
  
  //operator=
  printf("operator=\n");
  da.push_back(22);
  da.push_back(23);
  da.push_back(24);
  da2 = da;
  print(da2);
  
  return 0;
}
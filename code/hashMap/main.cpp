

#include "reusable/hashMap.h"

using namespace codingInterview;
using namespace std;

void print(const hashMap<int, string>& iHm)
{
  auto it = iHm.begin();
  for( ; it != iHm.end(); ++it )
  {
    printf("key: %d, value: %s, bucketIndex %d, arrayIndex %d\n", it.key(), it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() );
  }
}

void print(hashMap<int, string>::iterator& it, const hashMap<int, string>& iHm)
{
  if( it != iHm.end() )
  { printf("key found: value %s bucketIndex %d, arrayIndex %d\n", it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() ); }
  else
  { printf("key not found"); }
}

void testIntString()
{
  hashMap<int, string> hm(100);
  hm.insert(1, "patate1");
  hm.insert(2, "patate2");
  hm.insert(3, "patate3");
  hm.insert(4, "patate4");
  hm.insert(4, "patate5");
  hm.insert(4, "patate6");
  
  print(hm);
  
  printf("recherche de key == 3...\n");
  auto it = hm.find(3);
  print(it, hm);
  
  printf("\nrecherche de key == 2...\n");
  it = hm.find(2);
  print(it, hm);
  
  printf("\nrecherche de key == 4...\n");
  it = hm.find(4);
  print(it, hm);
  
  printf("\nrecherche de key == 22...\n");
  it = hm.find(22);
  print(it, hm);

}

int main(int argc, char** argv)
{
  testIntString();
  return 0;
}
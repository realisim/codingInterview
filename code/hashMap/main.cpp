

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
}

int main(int argc, char** argv)
{
  testIntString();
  return 0;
}
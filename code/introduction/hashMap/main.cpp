

#include <map>
#include "reusable/hashMap.h"
#include "reusable/statistics.h"
#include "reusable/timer.h"
#include "reusable/utilities.h"
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace codingInterview;
using namespace std;

struct point2d
{
  point2d() : mX(0.0), mY(0.0) {;}
  point2d(double x, double y) : mX(x), mY(y) {;}
  
  bool operator==(const point2d& iP) const { return mX == iP.mX && mY == iP.mY; }
  double mX;
  double mY;
};

//------------------------------------------------------------------
void generateTestData( vector< pair<int, string> >* iData)
{
  
  //generator for characters
  std::default_random_engine generator;
  std::uniform_int_distribution<int> charDistribution(34,95);
  
  
  int n = 1e5;
  int key = 0;
  string value = "n/a";
  for(int i = 0; i < n; ++i)
  {
    key = i;
    value = "";
    for(int j = 0; j < 5; ++j)
    {
      value += (char)charDistribution(generator);
    }
    iData->push_back( make_pair(key, value) );
  }
}

//------------------------------------------------------------------
void generateTestData( vector< pair<string, string> >* iData)
{
  
  //generator for characters
  std::default_random_engine generator;
  std::uniform_int_distribution<int> charDistribution(34,95);
  std::uniform_int_distribution<int> numberOfCharacter(10, 20);
  
  int n = 5e6;
  string key = "n/a";
  string value = "n/a";
  for(int i = 0; i < n; ++i)
  {
    int numChar = numberOfCharacter(generator);
    key = "";
    value = "";
    for(int j = 0; j < numChar; ++j)
    {
      key += (char)charDistribution(generator);
      value += (char)charDistribution(generator);
    }
    iData->push_back( make_pair(key, value) );
  }
}

//------------------------------------------------------------------
void print(const hashMap<int, string>& iHm)
{
  printf("\nHashMap with %d elements:\n", iHm.size());
  auto it = iHm.begin();
  for( ; it != iHm.end(); ++it )
  {
    printf("key: %d, value: %s, bucketIndex %d, arrayIndex %d\n", it.key(), it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() );
  }
  printf("\n");
}

//------------------------------------------------------------------
void print(hashMap<int, string>::iterator& it, const hashMap<int, string>& iHm)
{
  if( it != iHm.end() )
  { printf("key found: value %s bucketIndex %d, arrayIndex %d\n", it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() ); }
  else
  { printf("key not found\n"); }
}

//------------------------------------------------------------------
void print(hashMap<string, string>::iterator& it, const hashMap<string, string>& iHm)
{
  if( it != iHm.end() )
  { printf("key %s found: value %s bucketIndex %d, arrayIndex %d\n", it.key().c_str(), it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() ); }
  else
  { printf("key not found\n"); }
}

//------------------------------------------------------------------
void print(hashMap<point2d, string>::iterator& it, const hashMap<point2d, string>& iHm)
{
  if( it != iHm.end() )
  { printf("key (%.4f,%.4f) found: value %s bucketIndex %d, arrayIndex %d\n", it.key().mX, it.key().mY, it.value().c_str(), it.getBucketIndex(), it.getArrayIndex() ); }
  else
  { printf("key not found\n"); }
}

//------------------------------------------------------------------
void testIntString()
{
  const int numBuckets = 10000;
  hashMap<int, string> hm(numBuckets);
  
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

  
  //--- performance tests
  hm.clear();
  
  vector< pair<int, string> > data;
  generateTestData(&data);
  
  timer t;
  //--- HashMap insert time
  {
    statistics insertTimeStats;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      hm.insert(data[i].first, data[i].second);
      insertTimeStats.add( t.getElapsed() );
    }
    printf("HashMap insert time stats:\n%s\n", toString(insertTimeStats).c_str() );
  }
  
  //--- Hash Mapfind time
  {
    statistics findTimeStats;
    statistics bucketInfoStats;
    
    hashMap<int, string>::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = hm.find(data[i].first);
      
      //wrond data returned!
      if(data[i].second != it.value())
      {
        printf( "searching for key %d, value %s\n"
               "\tfound key %d, value %s, hash %d\n",
               data[i].first, data[i].second.c_str(),
               it.key(), it.value().c_str(), it.hash() );
        it = hm.find(data[i].first);
        assert(false);
      }
      
      findTimeStats.add( t.getElapsed() );
      bucketInfoStats.add( it.getBucketIndex() );
    }
    printf("HashMap find time stats:\n%s\n", toString(findTimeStats).c_str() );
    printf("HashMap bucket info stats:\n%s\n", toString(bucketInfoStats).c_str() );
  }
  hm.clear();

//--- vector is commented because it is way too long
//  //--- vector insert time
//  std::vector< pair<int, string> > v;
//  {
//    statistics insertTimeStats;
//    for(int i = 0; i < data.size(); ++i)
//    {
//      t.start();
//      v.push_back( data[i] );
//      insertTimeStats.add(t.getElapsed());
//    }
//    printf("vector insert time stats:\n%s\n", toString(insertTimeStats).c_str() );
//  }
//  
//  //--- vector find time
//  {
//    statistics st;
//    std::vector< pair<int, string> >::iterator it;
//    for(int i = 0; i < data.size(); ++i)
//    {
//      t.start();
//      it = find(v.begin(), v.end(), data[i]);
//      if(data[i].second != it->second)
//      {
//        printf( "searching for key %d, value %s\n"
//               "\tfound key %d, value %s\n",
//               data[i].first, data[i].second.c_str(),
//               it->first, it->second.c_str() );
//        assert(false);
//      }
//      st.add(t.getElapsed());
//    }
//    printf("vector find time stats:\n%s\n", toString(st).c_str() );
//  }
  
  //--- map insert time
  map<int, string> m;
  {
    statistics st;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      m[data[i].first] = data[i].second;
      st.add(t.getElapsed());
    }
    printf("map insert time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- map find time
  {
    statistics st;
    map< int, string >::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = m.find(data[i].first);
      
      if(data[i].second != it->second)
      {
        printf( "searching for key %d, value %s\n"
               "\tfound key %d, value %s\n",
               data[i].first, data[i].second.c_str(),
               it->first, it->second.c_str() );
        assert(false);
      }
      
      st.add(t.getElapsed());
    }
    printf("map find time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- unordered map insert time
  unordered_map<int, string> um(numBuckets);
  {
    statistics st;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      um[data[i].first] = data[i].second;
      st.add(t.getElapsed());
    }
    printf("unordered map insert time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- unordered map find time
  {
    statistics st;
    unordered_map< int, string >::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = um.find(data[i].first);
      
      if(data[i].second != it->second)
      {
        printf( "searching for key %d, value %s\n"
               "\tfound key %d, value %s\n",
               data[i].first, data[i].second.c_str(),
               it->first, it->second.c_str() );
        assert(false);
      }
      
      st.add(t.getElapsed());
    }
    printf("unordered map find time stats:\n%s\n", toString(st).c_str() );
  }
}

//------------------------------------------------------------------
void testStringString()
{
  printf("\n----testStringString\n");
  const int numBuckets = 10000;
  
  
  vector< pair<string, string> > data;
  generateTestData(&data);
  
  timer t;
  hashMap<string, string> hm(numBuckets);
  //--- HashMap insert time
  {
    statistics insertTimeStats;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      hm.insert(data[i].first, data[i].second);
      insertTimeStats.add( t.getElapsed() );
    }
    printf("HashMap insert time stats:\n%s\n", toString(insertTimeStats).c_str() );
  }
  
  //--- Hash Mapfind time
  {
    statistics findTimeStats;
    statistics bucketInfoStats;
    
    hashMap<string, string>::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = hm.find(data[i].first);
      
      //wrond data returned!
      if(data[i].second != it.value())
      {
        printf( "searching for key %s, value %s\n"
               "\tfound key %s, value %s, hash %d\n",
               data[i].first.c_str(), data[i].second.c_str(),
               it.key().c_str(), it.value().c_str(), it.hash() );
        it = hm.find(data[i].first);
        assert(false);
      }
      
      findTimeStats.add( t.getElapsed() );
      bucketInfoStats.add( it.getBucketIndex() );
    }
    printf("HashMap find time stats:\n%s\n", toString(findTimeStats).c_str() );
  }
  hm.clear();
  
  //--- map insert time
  map<string, string> m;
  {
    statistics st;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      m[data[i].first] = data[i].second;
      st.add(t.getElapsed());
    }
    printf("map insert time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- map find time
  {
    statistics st;
    map< string, string >::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = m.find(data[i].first);
      
      if(data[i].second != it->second)
      {
        printf( "searching for key %s, value %s\n"
               "\tfound key %s, value %s\n",
               data[i].first.c_str(), data[i].second.c_str(),
               it->first.c_str(), it->second.c_str() );
        assert(false);
      }
      
      st.add(t.getElapsed());
    }
    printf("map find time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- unordered map insert time
  unordered_map<string, string> um(numBuckets);
  {
    statistics st;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      um[data[i].first] = data[i].second;
      st.add(t.getElapsed());
    }
    printf("unordered map insert time stats:\n%s\n", toString(st).c_str() );
  }
  
  //--- unordered map find time
  {
    statistics st;
    unordered_map< string, string >::iterator it;
    for(int i = 0; i < data.size(); ++i)
    {
      t.start();
      it = um.find(data[i].first);
      
      if(data[i].second != it->second)
      {
        printf( "searching for key %s, value %s\n"
               "\tfound key %s, value %s\n",
               data[i].first.c_str(), data[i].second.c_str(),
               it->first.c_str(), it->second.c_str() );
        assert(false);
      }
      
      st.add(t.getElapsed());
    }
    printf("unordered map find time stats:\n%s\n", toString(st).c_str() );
  }
  
}

//------------------------------------------------------------------
void testPointString()
{
  printf("\n----testPointString\n");
  const int numBuckets = 10000;
  hashMap<point2d, string> hm(numBuckets);
  
  point2d p1(0,0);
  point2d p2(5,12);
  point2d p3(-1024.22, 2048.12);
  point2d p4(44, 2200.23);
  point2d p5(-12398.876, 34.8594);
  point2d p6(9478.534, 1234.9876);
  hm.insert(p1, "(0,0)");
  hm.insert(p2, "(5,12)");
  hm.insert(p3, "(-1024.22, 2048.12)");
  hm.insert(p4, "(44, 2200.23)");
  hm.insert(p5, "(-12398.876, 34.8594)");
  hm.insert(p6, "(9478.534, 1234.9876)");
  
  auto it1 = hm.find(p1);
  auto it2 = hm.find(p2);
  auto it3 = hm.find(p3);
  auto it4 = hm.find(p4);
  auto it5 = hm.find(p5);
  auto it6 = hm.find(p6);
  print(it1, hm);
  print(it2, hm);
  print(it3, hm);
  print(it4, hm);
  print(it5, hm);
  print(it6, hm);
}

int main(int argc, char** argv)
{
  testIntString();
  
  testStringString();
  
  testPointString();
  
  return 0;
}
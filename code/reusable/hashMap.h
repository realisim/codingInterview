#ifndef CODINGINTERVIEW_HASH_MAP_HH
#define CODINGINTERVIEW_HASH_MAP_HH

#include <cassert>
#include "dynamicArray.h"
#include <string>

namespace codingInterview
{
 
//-----------------------------------------------------
//--- hashMap
//-----------------------------------------------------
template<typename KEY>
class hash
{
public:
  hash();
  virtual ~hash() {;}
  unsigned int operator()(const KEY&);
};
  
//-----------------------------------------------------
//--- hashMap
//-----------------------------------------------------
template<typename KEY, typename VALUE>
class hashMap
{
public:
  explicit hashMap(unsigned int);
//  hashMap(const hashMap&);
//hashMap& operator=(const hashMap&);
  ~hashMap();
  
  class iterator
  {
  public:
    iterator();
    iterator(const iterator&);
    iterator& operator=(const iterator&);
    ~iterator();
    
    unsigned int getArrayIndex() const;
    unsigned int getBucketIndex() const;
    bool isValid() const;
    bool operator==(const iterator&) const;
    bool operator!=(const iterator&) const;
    bool operator>(const iterator&) const;
    bool operator<(const iterator&) const;
    iterator& operator++(); //pre-increment
    iterator& operator--(); //pre-decrement
    //iterator operator+(int);
    //iterator operator-(int);
    
    const KEY& key() const;
    VALUE& value();
    unsigned int hash() const;
    
  protected:
    friend typename hashMap<KEY, VALUE>::iterator hashMap<KEY, VALUE>::createIterator(unsigned int, unsigned int) const;
    
    hashMap<KEY, VALUE>* mpHashMap;
    unsigned int mBucketIndex;
    unsigned int mArrayIndex;
  };
  
  iterator begin() const;
//unsigned int count(const KEY&) const;
  void clear();
  iterator end() const;
  int getNumberOfBuckets() const {return mNumberOfBuckets;}
//pair<iterator, iterator> equalRange(const Key&) const;
  iterator find(const KEY&) const;
  void insert(const KEY&, const VALUE&);
  unsigned int size() const;
  
protected:
  friend class iterator;
  struct node
  {
    node();
    node(unsigned int h, const KEY& iK, const VALUE& iV);
    ~node() {}
    
    KEY mKey;
    VALUE mValue;
    unsigned int mHash;
  };
  
  hashMap() {;} //no default constructor
  iterator createIterator(unsigned int, unsigned int) const;
  dynamicArray<node>& operator[](int); //pour iterator;
  
  //--- data
  int mNumberOfBuckets;
  unsigned int mSize;
  dynamicArray<node> *mpBuckets;
  iterator mBeginIt;
  iterator mEndIt;
};
  
  //-----------------------------------------------------
  //--- implementation hash - hasher
  //-----------------------------------------------------
  template<typename KEY>
  hash<KEY>::hash() {}
  
  //-----------------------------------------------------
  //general catch all hasher.
  template<typename KEY>
  unsigned int hash<KEY>::operator()(const KEY &iKey)
  {
    // settings taken from
    // http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
    const unsigned int FNV_PRIME = 16777619;
    const unsigned int FNV_OFFSET_BASIS = 2166136261;
    
    unsigned int hash = FNV_OFFSET_BASIS;
    
    const size_t numBytes = sizeof(iKey);
    const char *bytes = reinterpret_cast<const char*>(&iKey);
    
    for(size_t i = 0; i < numBytes; i++)
    {
      hash ^= bytes[i];
      hash *= FNV_PRIME;
    }
    
    return hash;
  }
  
  //-----------------------------------------------------
  //string specialization (to handle \0 properly)
  template<>
  unsigned int hash<std::string>::operator()(const std::string &iKey)
  {
    // settings taken from
    // http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
    const unsigned int FNV_PRIME = 16777619;
    const unsigned int FNV_OFFSET_BASIS = 2166136261;
    
    unsigned int hash = FNV_OFFSET_BASIS;
    
    const char *bytes = reinterpret_cast<const char*>(&iKey);
    std::string s(bytes);
    
    for(size_t i = 0; i < s.size(); i++)
    {
      hash ^= bytes[i];
      hash *= FNV_PRIME;
    }
    
    return hash;
  }
  
  //------------------------------------------------------------------------------
  //--- Implementation hashMap
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap(unsigned int iNumBuckets) :
    mNumberOfBuckets(iNumBuckets),
    mSize(0),
    mpBuckets(nullptr)
  {
    mpBuckets = new dynamicArray<node>[mNumberOfBuckets];
    mBeginIt = createIterator(-1, -1);
    mEndIt = mBeginIt;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::~hashMap()
  { delete[] mpBuckets; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  typename hashMap<KEY, VALUE>::iterator
  hashMap<KEY, VALUE>::begin() const
  { return mBeginIt; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  void
  hashMap<KEY, VALUE>::clear()
  {
    if( mpBuckets != nullptr )
    { delete[] mpBuckets; }
    mpBuckets = new dynamicArray<node>[mNumberOfBuckets];
    mBeginIt = createIterator(-1, -1);
    mEndIt = mBeginIt;
    mSize = 0;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  typename hashMap<KEY, VALUE>::iterator
  hashMap<KEY, VALUE>::createIterator(unsigned int iBucketIndex, unsigned int iArrayIndex) const
  {
    iterator it;
    it.mpHashMap = const_cast< hashMap<KEY, VALUE>* >(this);
    it.mBucketIndex = iBucketIndex;
    it.mArrayIndex = iArrayIndex;
    return it;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  typename hashMap<KEY, VALUE>::iterator
  hashMap<KEY, VALUE>::end() const
  { return mEndIt; }
    
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  typename hashMap<KEY, VALUE>::iterator
  hashMap<KEY, VALUE>::find(const KEY& iKey) const
  {
    iterator it = end();
    
    codingInterview::hash<KEY> hasher;
    const unsigned int hash = hasher(iKey);
    const unsigned int bucketIndex = hash % getNumberOfBuckets();
    
    const dynamicArray<node>& bucket = mpBuckets[bucketIndex];
    const int bucketSize = bucket.size();
    
    bool found = false;
    for(int i = 0; i < bucketSize && !found; ++i)
    {
      if( bucket[i].mKey == iKey )
      {
        it = createIterator(bucketIndex, i);
        found = true;
      }
    }
    
    return it;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  void
  hashMap<KEY, VALUE>::insert(const KEY& iKey, const VALUE& iValue)
  {
    codingInterview::hash<KEY> hasher;
    const unsigned int hash = hasher(iKey);
    const unsigned int bucketIndex = hash % getNumberOfBuckets();
    
    node n(hash, iKey, iValue);
    mpBuckets[bucketIndex].push_back(n);
    
    //update begin and end iterator.
    iterator currentIt = createIterator(bucketIndex, mpBuckets[bucketIndex].size() - 1);
    if( !begin().isValid() || currentIt < begin() )
    { mBeginIt = currentIt; }
    
    //end is one bucket past end
    if( !end().isValid() || currentIt > end() )
    { mEndIt = createIterator(currentIt.getBucketIndex() + 1, 0); }
    
    //update size
    ++mSize;
  }

  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  dynamicArray<typename hashMap<KEY, VALUE>::node>&
  hashMap<KEY, VALUE>::operator[](int iIndex)
  { return mpBuckets[iIndex]; }

  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  unsigned int
  hashMap<KEY, VALUE>::size() const
  { return mSize; }
  
  //------------------------------------------------------------------------------
  //--- Implementation hashMap::iterator
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::iterator::iterator() :
    mpHashMap(0),
    mBucketIndex(-1),
    mArrayIndex(-1)
  {}
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::iterator::iterator(const iterator& iRhs) :
    mpHashMap(iRhs.mpHashMap),
    mBucketIndex(iRhs.mBucketIndex),
    mArrayIndex(iRhs.mArrayIndex)
  {}
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::iterator&
  hashMap<KEY, VALUE>::hashMap::iterator::operator=(const iterator& iRhs)
  {
    mpHashMap = iRhs.mpHashMap;
    mBucketIndex = iRhs.mBucketIndex;
    mArrayIndex = iRhs.mArrayIndex;
    return *this;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::iterator::~iterator()
  { mpHashMap = 0; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  unsigned int
  hashMap<KEY, VALUE>::hashMap::iterator::getArrayIndex() const
  { return mArrayIndex; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  unsigned int
  hashMap<KEY, VALUE>::hashMap::iterator::getBucketIndex() const
  { return mBucketIndex; }

  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  unsigned int
  hashMap<KEY, VALUE>::hashMap::iterator::hash() const
  { return (*mpHashMap)[mBucketIndex][mArrayIndex].mHash; }

  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  bool
  hashMap<KEY, VALUE>::hashMap::iterator::isValid() const
  { return mBucketIndex != -1 && mArrayIndex != -1; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  const KEY&
  hashMap<KEY, VALUE>::hashMap::iterator::key() const
  { return (*mpHashMap)[mBucketIndex][mArrayIndex].mKey; }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  VALUE&
  hashMap<KEY, VALUE>::hashMap::iterator::value()
  { return (*mpHashMap)[mBucketIndex][mArrayIndex].mValue; }

  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  bool
  hashMap<KEY, VALUE>::hashMap::iterator::operator==(const hashMap::iterator &iRhs) const
  {
    return mBucketIndex == iRhs.mBucketIndex &&
      mArrayIndex == iRhs.mArrayIndex &&
      mpHashMap == iRhs.mpHashMap;
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  bool
  hashMap<KEY, VALUE>::hashMap::iterator::operator!=(const hashMap::iterator &iRhs) const
  { return !operator==(iRhs); }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  bool
  hashMap<KEY, VALUE>::hashMap::iterator::operator>(const hashMap::iterator &iRhs) const
  {
    return mBucketIndex > iRhs.mBucketIndex ||
      (mBucketIndex == iRhs.mBucketIndex && mArrayIndex > iRhs.mArrayIndex);
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  bool
  hashMap<KEY, VALUE>::hashMap::iterator::operator<(const hashMap::iterator &iRhs) const
  {
    return mBucketIndex < iRhs.mBucketIndex ||
      (mBucketIndex == iRhs.mBucketIndex && mArrayIndex < iRhs.mArrayIndex);
  }
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::iterator&
  hashMap<KEY, VALUE>::hashMap::iterator::operator++()
  {
    //go to next element in array, if not possible or empty, go to next bucket.
    bool foundNext = false;
    
    while(!foundNext && *this != mpHashMap->end())
    {
      //since mArrayIndex is unsigned int size() is promoted to unsigned int and
      //we must validate the size is greater than 0 prior substracting 1. If we
      //dont, it will wrap around and always be greater than mArrayIndex.
      if( (*mpHashMap)[mBucketIndex].size() > 0 &&
         (*mpHashMap)[mBucketIndex].size() - 1 > mArrayIndex )
      { ++mArrayIndex; }
      else
      {
          mArrayIndex = 0;
          ++mBucketIndex;
      }
      foundNext = (*mpHashMap)[mBucketIndex].size() > 0;
    }
    
    return *this;
  }
  
  //------------------------------------------------------------------------------
  //--- Implementation hashMap::node
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::node::node() :
  mKey(),
  mValue(),
  mHash(-1)
  {}
  
  //------------------------------------------------------------------------------
  template<typename KEY, typename VALUE>
  hashMap<KEY, VALUE>::hashMap::node::node(unsigned int iH,
                                           const KEY& iK,
                                           const VALUE& iV) :
  mKey(iK),
  mValue(iV),
  mHash(iH)
  {}
  
} //namespace codingInterview

#endif
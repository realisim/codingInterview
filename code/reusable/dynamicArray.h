#ifndef CODINGINTERVIEW_DYNAMIC_ARRAY_HH
#define CODINGINTERVIEW_DYNAMIC_ARRAY_HH

#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>

namespace codingInterview
{
  
template<typename T>
class dynamicArray
{
public:
  dynamicArray();
  dynamicArray(int, const T& = T());
  dynamicArray(const dynamicArray&);
  dynamicArray& operator=(const dynamicArray&);
  ~dynamicArray();
  
  //enum growthMethod( gmExactSize, gmDoubleUp );
  
  int capacity() const;
  void clear();
  int erase(int);
  int erase(int, int);
//int find(const T&) const;
//int insert(int, const T&);
  T& operator[](int);
  const T& operator[](int) const;
  T pop_back() const;
  void push_back(const T&);
  void resize(int, const T& = T());
  int size() const;
  
protected:
  int computeArrayCapacity(int) const;
  void expand(int);
  void reduce();
  bool shouldReduce() const;
  
  //TODO.. should use unsigned int here!!!
  T *mpData;
  int mLastInsertionIndex;
  int mCapacity;
};
 
  //----------------------------------------------------------------------------
  //--- implementation
  //----------------------------------------------------------------------------
  template<typename T>
  dynamicArray<T>::dynamicArray() : mpData(nullptr), mLastInsertionIndex(-1),
    mCapacity(0)
  {}
  
  //----------------------------------------------------------------------------
  template<typename T>
  dynamicArray<T>::dynamicArray(int iNumElement, const T &iVal /*=T()*/) :
  mpData(nullptr),
  mLastInsertionIndex(-1),
  mCapacity(0)
  { resize(iNumElement, iVal); }

  //----------------------------------------------------------------------------
  template<typename T>
  dynamicArray<T>::dynamicArray(const dynamicArray& iDyn) :
  mpData(nullptr),
  mLastInsertionIndex(-1),
  mCapacity(0)
  {
    mpData = new T[iDyn.capacity()];
    mLastInsertionIndex = iDyn.mLastInsertionIndex;
    mCapacity = iDyn.capacity();
    memcpy(mpData, iDyn.mpData, sizeof(T)*iDyn.size());
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  dynamicArray<T>& dynamicArray<T>::operator=(const dynamicArray& iDyn)
  {
    clear();
    mpData = new T[iDyn.capacity()];
    mLastInsertionIndex = iDyn.mLastInsertionIndex;
    mCapacity = iDyn.capacity();
    memcpy(mpData, iDyn.mpData, sizeof(T)*iDyn.size());
    return *this;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  dynamicArray<T>::~dynamicArray()
  { clear(); }
  
  //----------------------------------------------------------------------------
  template<typename T>
  int dynamicArray<T>::capacity() const
  { return mCapacity; }
  
  //----------------------------------------------------------------------------
  template<typename T>
  void dynamicArray<T>::clear()
  {
    if(mpData != nullptr)
    {
      delete[] mpData;
      mpData = nullptr;
    }
    mLastInsertionIndex = -1;
    mCapacity = 0;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  int dynamicArray<T>::computeArrayCapacity(int iV) const
  { return pow(2, ceil( log2((double)iV) )); }
  
  //----------------------------------------------------------------------------
  //erase the element at index iIndex and return the index of the element
  //that took it's place.
  template<typename T>
  int dynamicArray<T>::erase(int iIndex)
  {
    int r = 0;
    if(iIndex >= 0 && iIndex < size() - 1)
    {
      memcpy(mpData + iIndex, mpData + iIndex+1, sizeof(T) * (size() - iIndex - 1));
      --mLastInsertionIndex;
      r = iIndex;
    }
    
    //removing the last item
    if(iIndex == size() - 1)
    {
      --mLastInsertionIndex;
      r = mLastInsertionIndex;
    }
    
    if(shouldReduce()){ reduce(); }
    return r;
  }
  
  //----------------------------------------------------------------------------
  //erase the elements from index fromIndex to index toIndex and return the index of the element
  //that took it's place.
  template<typename T>
  int dynamicArray<T>::erase(int iFrom, int iTo)
  {
    int r = 0;
    if(iFrom >= 0 && iFrom <= iTo &&
       iTo < size())
    {
      if( iTo < size() - 1 )
      {
        memcpy(mpData + iFrom, mpData + iTo+1, sizeof(T) * (size() - iTo - 1));
        mLastInsertionIndex -= iTo - iFrom + 1;
        r = iFrom;
      }
      else //erasing until the end.
      { mLastInsertionIndex = iFrom - 1; }
      
      if(shouldReduce()){ reduce(); }
    }
    return r;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  void dynamicArray<T>::expand(int iNewSize)
  {
    T *newArray = new T[iNewSize];
    memcpy(newArray, mpData, sizeof(T) * size() );
//printf("expand from %d to %d, old mpdata 0x%08x, new mpdata 0x%08x, sizeof(T) %d, total copy size %d\n",
//       size(),
//       iNewSize,
//       mpData, newArray, sizeof(T), sizeof(T) * size());
    delete[] mpData;
    mpData = newArray;
    
    mCapacity = iNewSize;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  T& dynamicArray<T>::operator[](int iIndex)
  {
    const T& r = (const_cast<const dynamicArray<T> &>(*this))[iIndex];
    return const_cast<T&>(r);
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  const T& dynamicArray<T>::operator[](int iIndex) const
  {
    assert(iIndex < size());
    return mpData[iIndex];
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  T dynamicArray<T>::pop_back() const
  {
    T r;
    if(size() > 0)
    {
      r = mpData[size()-1];
      erase(size() - 1);
    }
    return r;
  }
    
  //----------------------------------------------------------------------------
  template<typename T>
  void dynamicArray<T>::push_back(const T& iV)
  {
    //allocate if null
    if(mpData == nullptr)
    {
      mpData = new T[1];
      mLastInsertionIndex = -1;
      mCapacity = 1;
    }
    
    //expand when reaching max number of element
    assert(size() <= mCapacity && "dynamic array should never be longer than maximumNumberOfelement");
    if( size() == mCapacity )
    {
      expand( computeArrayCapacity(mCapacity + 1) );
    }
    
    mpData[++mLastInsertionIndex] = iV;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  void dynamicArray<T>::reduce()
  {
    mCapacity = computeArrayCapacity(size());
    T *newArray = new T[mCapacity];
    
    memcpy(newArray, mpData, sizeof(T) * size());
    if(mpData != nullptr)
    { delete mpData; }
    mpData = newArray;
  }
  
  //----------------------------------------------------------------------------
  //inserts or erase element at the end so the new size is iNumberOfElement. the
  //capacity will be equal to iNumberOfElement.
  template<typename T>
  void dynamicArray<T>::resize(int iNumberOfElement, const T& iVal /*=T()*/)
  {
    T *newArray = new T[iNumberOfElement];
    
    const int numElementToCopy = iNumberOfElement < size() ? iNumberOfElement : size();
    memcpy(newArray, mpData, sizeof(T) * numElementToCopy);
    
    //fill at the end if necessary with iVal without changing mLastInsertionIndex.
    if( iNumberOfElement > size() )
    {
      for(int i = size(); i < iNumberOfElement; ++i)
      { newArray[i] = iVal; }
    }
    
    //swap to new array
    clear();
    mpData = newArray;
    mLastInsertionIndex = iNumberOfElement - 1;
    mCapacity = iNumberOfElement;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  bool dynamicArray<T>::shouldReduce() const
  {
    const int optimalCapacity = computeArrayCapacity(size());
    const int currentCapacity = capacity();
    
    return (log2(currentCapacity) - log2(optimalCapacity)) > 1;
  }
  
  //----------------------------------------------------------------------------
  template<typename T>
  int dynamicArray<T>::size() const
  { return mLastInsertionIndex + 1; }
}

#endif

#include <cassert>
#include "DoubleLinkedList.h"
#include <sstream>

using namespace codingInterview;
using namespace std;

doublyLinkedList::doublyLinkedList() :
  mpFirst(nullptr),
  mpLast(nullptr),
  mCount(0)
{
}

//------------------------------------------------------------------------------
doublyLinkedList::~doublyLinkedList()
{ clear(); }

//------------------------------------------------------------------------------
doublyLinkedList::doublyLinkedList(const doublyLinkedList& iRhs) :
  mpFirst(nullptr),
  mpLast(nullptr),
  mCount(0)
{
  if(!iRhs.isEmpty())
  {
    *this = iRhs;
  }
}
//------------------------------------------------------------------------------
doublyLinkedList& doublyLinkedList::operator=(const doublyLinkedList& iRhs)
{
  clear();
  node* it = iRhs.mpFirst;
  while(it != nullptr)
  {
    push_back(it->mValue);
    
    it = it->mpNext;
  }
  return *this;
}
//------------------------------------------------------------------------------
void doublyLinkedList::clear()
{
  if(!isEmpty())
  {
    node* n = mpFirst;
    while( n != nullptr )
    {
      node* d = n;
      n = n->mpNext;
      delete d;
    }
    mpFirst = nullptr;
    mpLast = nullptr;
    mCount = 0;
  }
}
//------------------------------------------------------------------------------
bool doublyLinkedList::isEmpty() const
{ return size() == 0; }
//------------------------------------------------------------------------------
void doublyLinkedList::push_back(int v)
{
  node* n = new node();
  n->mValue = v;
  
  if(isEmpty())
  {
    n->mpPrevious = nullptr;
    n->mpNext = nullptr;
    mpFirst = n;
    mpLast = n;
  }
  else
  {
    mpLast->mpNext = n;
    n->mpPrevious = mpLast;
    n->mpNext = nullptr;
    mpLast = n;
  }
  mCount++;
}
//------------------------------------------------------------------------------
void doublyLinkedList::push_front(int v)
{
  node* n = new node();
  n->mValue = v;
  
  if(isEmpty())
  {
    n->mpPrevious = nullptr;
    n->mpNext = nullptr;
    mpFirst = n;
    mpLast = n;
  }
  else
  {
    mpFirst->mpPrevious = n;
    n->mpPrevious = nullptr;
    n->mpNext = mpFirst;
    mpFirst = n;
  }
  mCount++;
}
//------------------------------------------------------------------------------
int doublyLinkedList::pop_back()
{
  assert(!isEmpty());
  int r = 0;
  r = mpLast->mValue;
  
  node* tmp = mpLast;
  mpLast = mpLast->mpPrevious;
  mpLast->mpNext = nullptr;
  
  delete tmp;
  mCount--;
  
  return r;
}
//------------------------------------------------------------------------------
int doublyLinkedList::pop_front()
{
  assert(!isEmpty());
  int r = 0;
  r = mpFirst->mValue;
  
  node* tmp = mpFirst;
  mpFirst = mpFirst->mpNext;
  mpFirst->mpPrevious = nullptr;
  
  delete tmp;
  mCount--;
  
  return r;
}
//------------------------------------------------------------------------------
int doublyLinkedList::size() const
{ return mCount; }
//------------------------------------------------------------------------------
std::string doublyLinkedList::toString() const
{
  ostringstream oss;
  
  node* it = mpFirst;
  while (it != nullptr)
  {
    oss << "[" << it->mValue << "]" << " ";
    it = it->mpNext;
  }
  return oss.str();
}



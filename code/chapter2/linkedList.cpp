
#include "linkedList.h"
#include <sstream>

using namespace codingInterview;

//-----------------------------------------------------------------
linkedList::linkedList()
: mpRoot(nullptr),
mpTail(nullptr)
{}

//-----------------------------------------------------------------
linkedList::~linkedList()
{ clear(); }

//-----------------------------------------------------------------
void linkedList::clear()
{
  node *n = mpRoot;
  while(n != nullptr)
  {
    node *t = n;
    n = n->mpNext;
    delete t;
  }
  mpRoot = nullptr;
  mpTail = nullptr;
}

//-----------------------------------------------------------------
void linkedList::insert(int iValue)
{
  node *newNode = new node();
  newNode->mValue = iValue;
  newNode->mpNext = nullptr;

  if(mpRoot == nullptr)
  {
    mpRoot = newNode;
    mpTail = newNode;
  }
  else
  {
    mpTail->mpNext = newNode;
    mpTail = newNode;
  }
}

//-----------------------------------------------------------------
void linkedList::remove(int iValue)
{
  node *n = mpRoot;
  node *p = nullptr;
  while(n != nullptr)
  {
//    blabla;
  }
}

//-----------------------------------------------------------------
std::string linkedList::toStdString() const
{
  std::ostringstream oss;
  node *n = mpRoot;
  while(n != nullptr)
  {
    oss << n->mValue;
    n = n->mpNext;
    if(n){ oss << " -> "; }
  }
  return oss.str();
}

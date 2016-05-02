
#ifndef codingInterview_link_list_hh
#define codingInterview_link_list_hh

#include <cstddef>
#include <string>

namespace codingInterview{

  class linkedList
  {
  public:
    linkedList();
    virtual ~linkedList();
    
    void clear();
    void insert(int);
    void remove(int);
    std::string toStdString() const;
    
  protected:
    struct node
    {
      node() : mValue(0), mpNext(nullptr) {}
      int mValue;
      node* mpNext;
    };
    
    node* mpRoot;
    node* mpTail;
  };
  
}

#endif
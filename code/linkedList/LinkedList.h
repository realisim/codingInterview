
#include <cstddef>
#include <string>

namespace codingInterview
{
  class doublyLinkedList
  {
  public:
    doublyLinkedList();
    doublyLinkedList(const doublyLinkedList&);
    doublyLinkedList& operator=(const doublyLinkedList&);
    ~doublyLinkedList();
    
//    const T& back() const;
//    const T& front() const;
    
    void clear();
    bool isEmpty() const;
    int pop_back();
    int pop_front();
    void push_back(int);
    void push_front(int);
    int size() const;
    std::string toString() const;
    
  protected:
    struct node
    {
      node() : mpPrevious(nullptr), mpNext(nullptr), mValue(0) {}
      node* mpPrevious;
      node* mpNext;
      int mValue;
    };
    
    node* mpFirst;
    node* mpLast;
    int mCount;
  };
  
  
}
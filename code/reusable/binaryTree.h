
#ifndef coding_interview_binary_tree_hh
#define coding_interview_binary_tree_hh

#include <cstddef>

namespace codingInterview
{
  /*This is a simple implementation of a binary tree in the
    form KEY-VALUE (I guess similar to std::map). It is not
    meant to be use, as too many useful function will be missing.
    The goal is only to implement erase, find and insert which
    is at the heart of the binary tree.*/
  
  template<class KEY, class VALUE>
  class binaryTree
  {
  public:
    binaryTree();
    virtual ~binaryTree();
    
    void clear();
    void erase(const KEY&);
    bool find(const KEY&, VALUE*) const;
    void insert(const KEY&, const VALUE&);
    
  protected:
    
    struct node
    {
      node(); //not implemented...
      node(const KEY&, const VALUE&);
      
      KEY mKey;
      VALUE mValue;
      
      node *mpParent;
      node *mpLeft;
      node *mpRight;
    };
    
    bool findNode(const node*, const KEY&, VALUE*) const;
    void insertNode(node*, node*);
    
    node* mpRoot;
    
  };

  //---------------------------------------------------------------
  //--- Implementation binaryTree::node
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  binaryTree<KEY, VALUE>::binaryTree::node::node(const KEY& iK, const VALUE& iV) :
    mKey(iK),
    mValue(iV),
    mpParent(nullptr),
    mpLeft(nullptr),
    mpRight(nullptr)
  {}
  
  //---------------------------------------------------------------
  //--- Implementation binary tree
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  binaryTree<KEY, VALUE>::binaryTree() :
  mpRoot(nullptr)
  {}
  
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  binaryTree<KEY, VALUE>::~binaryTree()
  { clear(); }
  
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  bool
  binaryTree<KEY, VALUE>::find(const KEY &iK, VALUE* oV) const
  {
    bool r = false;
    if( mpRoot != nullptr)
    { r = findNode(mpRoot, iK, oV); }
    return r;
  }
  
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  bool
  binaryTree<KEY, VALUE>::findNode(const node* iN, const KEY &iK, VALUE* oV) const
  {
    if( iK == iN->mKey )
    { *oV = iN->mValue; return true; }
    else
    {
      if( iK < iN->mKey )
      { return findNode(iN->mpLeft, iK, oV); }
      else
      { return findNode(iN->mpRight, iK, oV); }
    }
  }
  
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  void
  binaryTree<KEY, VALUE>::insert(const KEY &iK, const VALUE &iV)
  {
    if( mpRoot == nullptr )
    {
      mpRoot = new node(iK, iV);
    }
    else
    {
      node* n = new node(iK, iV);
      insertNode(mpRoot, n);
    }
  }
  
  //---------------------------------------------------------------
  template<class KEY, class VALUE>
  void
  binaryTree<KEY, VALUE>::insertNode(node* current, node* toInsert)
  {
    //go to left child
    if( toInsert->mKey < current->mKey )
    {
      if( current->mpLeft == nullptr )
      { current->mpLeft = toInsert; return; }
      else
      { insertNode(current->mpLeft, toInsert); }
    }
    else //go to right child
    {
      if( current->mpRight == nullptr )
      { current->mpRight = toInsert; return; }
      else
      { insertNode(current->mpRight, toInsert); }
    }
  }
} // end of namespace
#endif

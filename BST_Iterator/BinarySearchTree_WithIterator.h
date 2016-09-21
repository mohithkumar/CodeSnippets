#ifndef __BINARYSEARCHTREE_WITERATOR__
#define __BINARYSEARCHTREE_WITERATOR__

typedef struct BstNode* BstNodePtr;
typedef unsigned int uint;

struct BstNode
{
    int mData;
    BstNodePtr left;
    BstNodePtr right;

    BstNodePtr parent;

    explicit BstNode(int data);
    ~BstNode();

  private:
    // Non-copyable
    BstNode(const BstNode&);
    BstNode& operator=(const BstNode&);
};


class BinarySearchTree
{
  public:
    class Iterator
    {
      public:
        Iterator();
        Iterator(BstNodePtr p);
        ~Iterator();

        void operator++();
        // Return type int corresponds to the type of mData in BstNode        
        int operator*() const;
        BstNodePtr operator->();
        bool operator==(const Iterator& r) const;
        bool operator!=(const Iterator& r) const;

        bool operator==(const BstNodePtr r) const;
        bool operator!=(const BstNodePtr r) const;

      private:
        BstNodePtr getCurrNode() const;

        BstNodePtr mCurrNode;
    };

    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int);
    void remove(int);

    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;

    void findSmallestElement() const;
    void findLargestElement() const;
    void findKthSmallestElement(uint k) const;
    void findKthLargestElement(uint k) const;

    uint findTreeDepth() const;

    // Iterator functions
    BstNodePtr first() const;
    BstNodePtr last() const;

  private:
    // Non-copyable
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree& operator=(const BinarySearchTree&);

    void preOrderTraversal(BstNodePtr p) const;
    void postOrderTraversal(BstNodePtr p) const;

    void inOrderTraversalIter(BstNodePtr p) const;

    int findLargestElement(BstNodePtr p) const;

    void findKthSmallestElementIter(BstNodePtr p, uint k) const;
    void findKthLargestElement(BstNodePtr p, uint& index) const;
    uint findTreeDepth(BstNodePtr p) const;

  private:
    BstNodePtr mRoot;
};

#endif // __BINARYSEARCHTREE_WITERATOR__


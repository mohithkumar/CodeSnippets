#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "HashMap.h"

typedef struct BstNode* BstNodePtr;
struct BstNode
{
    explicit BstNode(HashNodePtr hashNodePtr);
    ~BstNode();

    HashNodePtr mHashNodePtr;
    BstNodePtr left;
    BstNodePtr right;

  private:
    // Non-copyable
    BstNode(const BstNode&);
    BstNode& operator=(const BstNode&);
};


class BinarySearchTree
{
  public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(HashNodePtr hashNode);
    void printWordsWithLargestFreq(uint number);

  private:
    // Non-copyable
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree& operator=(const BinarySearchTree&);

    void printWordsWithLargestFreq(
        BstNodePtr node, uint number, uint& index);

    BstNodePtr mRoot;
};

#endif


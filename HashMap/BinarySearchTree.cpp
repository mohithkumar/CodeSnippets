#include "BinarySearchTree.h"
#include <iostream>

BstNode::BstNode(HashNodePtr hashNodePtr)
    : mHashNodePtr(hashNodePtr), left(NULL), right(NULL)
{
}


BstNode::~BstNode()
{
    // DO NOT DELETE mHashNodePtr
    delete left;
    delete right;
}


BinarySearchTree::BinarySearchTree() : mRoot(NULL)
{
}


BinarySearchTree::~BinarySearchTree()
{
    delete mRoot;
}


void BinarySearchTree::insert(HashNodePtr hashNode)
{
    BstNodePtr bstNode = new BstNode(hashNode);
    BstNodePtr parent(NULL);

    // New tree
    if (mRoot == NULL)
        mRoot = bstNode;
    else
    {
        BstNodePtr curr = mRoot;
        // Find the parent of bstNode
        while (curr)
        {
            parent = curr;
            if (hashNode->getFreq() > curr->mHashNodePtr->getFreq())
                curr = curr->right;
            else
                curr = curr->left;
        }

        // Insert new bstNode under the parent
        if (hashNode->getFreq() > parent->mHashNodePtr->getFreq())
           parent->right = bstNode;
        else
           parent->left = bstNode;
    }
}


void BinarySearchTree::printWordsWithLargestFreq(uint number)
{
    if (mRoot)
    {
        uint index(0);
        try
        {
            printWordsWithLargestFreq(mRoot, number, index);
        }
        catch(const char* s)
        {
            std::cout << s << std::endl;
        }
    }
    else
        std::cout << "No elements found in the BST!!" << std::endl;
}


void BinarySearchTree::printWordsWithLargestFreq(
    BstNodePtr node, uint number, uint& index)
{
    if (node)
    {
        printWordsWithLargestFreq(node->right, number, index);

        if (++index <= number)
        {
            std::cout << node->mHashNodePtr->getWord() << " "
                      << node->mHashNodePtr->getFreq() << std::endl;
        }
        else
        {
            throw "All required numbers found\n"; // Break out of recursion
        }

        printWordsWithLargestFreq(node->left, number, index);
    }
}


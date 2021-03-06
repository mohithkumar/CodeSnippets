#include "BinarySearchTree_WithIterator.h"
// #include "BstException.h"
#include <iostream>
#include <stack>

using namespace std;

BstNode::BstNode(int data)
    : mData(data), left(NULL), right(NULL), parent(NULL)
{
}


BstNode::~BstNode()
{
    delete left;
    delete right;
    parent = NULL;
}


BinarySearchTree::Iterator::Iterator() : mCurrNode(NULL)
{
}


BinarySearchTree::Iterator::Iterator(BstNodePtr p) : mCurrNode(p)
{
}


BinarySearchTree::Iterator::~Iterator()
{
    mCurrNode = NULL;
}


void BinarySearchTree::Iterator::operator++()
{
    BstNodePtr temp(NULL);
    // Case 1 - Root node; so next node will be left most node of right sub-tree
    if (mCurrNode->parent == NULL)
    {
        temp = mCurrNode->right;
        if (temp)
        {
            mCurrNode = temp;
            while (mCurrNode->left != NULL)
                mCurrNode = mCurrNode->left;
        }
    }
    // Case 2 - Left node (with no right child); so next node will be parent
    else if ((mCurrNode == mCurrNode->parent->left) &&
             (mCurrNode->right == NULL))
    {
        mCurrNode = mCurrNode->parent;
    }
    // Case 3 - Right-leaf node; 
    // so keep going up the tree until currNode.mData < currNode.parent.mData
    else if ((mCurrNode == mCurrNode->parent->right) &&
             (mCurrNode->right == NULL) && (mCurrNode->left == NULL))
    {
        temp = mCurrNode;
        while ((temp->mData > temp->parent->mData) && (temp != NULL))
            temp = temp->parent;
        if (temp != NULL)
            mCurrNode = temp;
        // else mCurrNode was the last element
    }
    // Case 4 - Middle node; 
    // so next node will be the left-most node in the right subtree
    else
    {
        temp = mCurrNode->right;
        if (temp)
        {
            mCurrNode = temp;
            while (mCurrNode->left != NULL)
                mCurrNode = mCurrNode->left;
        }
        else
        {
            mCurrNode = mCurrNode->parent;
        }
    }
}


// Return type int corresponds to the type of mData in BstNode
int BinarySearchTree::Iterator::operator*() const
{
    return mCurrNode->mData;
}


BstNodePtr BinarySearchTree::Iterator::operator->()
{
    return mCurrNode;
}


bool BinarySearchTree::Iterator::operator==(const Iterator& r) const
{
    return (mCurrNode == r.getCurrNode());
}


bool BinarySearchTree::Iterator::operator!=(const Iterator& r) const
{
    return (mCurrNode != r.getCurrNode());
}


bool BinarySearchTree::Iterator::operator==(const BstNodePtr r) const
{
    return (mCurrNode == r);
}


bool BinarySearchTree::Iterator::operator!=(const BstNodePtr r) const
{
    return (mCurrNode != r);
}


BstNodePtr BinarySearchTree::Iterator::getCurrNode() const
{
    return mCurrNode;
}


BinarySearchTree::BinarySearchTree() : mRoot(NULL)
{
}


BinarySearchTree::~BinarySearchTree()
{
    delete mRoot;
}


void BinarySearchTree::insert(int data)
{
    BstNodePtr bstNode = new BstNode(data);
    BstNodePtr parent(NULL);

    // New tree
    if (mRoot == NULL)
    {
        mRoot = bstNode;
    }
    else
    {
        BstNodePtr curr = mRoot;
        // Find the parent of bstNode
        while (curr)
        {
            parent = curr;
            if (data > curr->mData)
                curr = curr->right;
            else
                curr = curr->left;
        }

        // Throw exception if the numbers are the same
        if (data == parent->mData)
        {
            cout << "Duplicates not allowed!!" << endl;
            // throw BstException("Duplicates not allowed!!");
            return;
        }

        // Insert new bstNode under the parent
        if (data > parent->mData)
        {
            parent->right = bstNode;
            bstNode->parent = parent;
        }
        else
        {
            parent->left = bstNode;
            bstNode->parent = parent;
        }
    }
}


void BinarySearchTree::remove(int data)
{
    //Locate the element
    bool found = false;
    if (mRoot == NULL)
    {
        cout << "Tree is empty!" << endl;
        // throw BstException("Tree is empty!");
        return;
    }

    BstNodePtr curr(mRoot);
    BstNodePtr parent(NULL);

    // Check whether element is present in tree and
    // determine the curr node to be deleted and the parent of curr.
    while ((curr != NULL) && (found == false))
    {
         if (curr->mData == data)
         {
            found = true;
         }
         else
         {
             parent = curr;
             if (data > curr->mData)
                 curr = curr->right;
             else
                 curr = curr->left;
         }
    }

    if (found == false)
    {
        cout << "Data not found!" << endl;
        // throw BstException("Data not found!");
        return;
    }

    // 1. Removing a leaf node
    if (curr->left == NULL && curr->right == NULL)
    {
        if (parent->left == curr)
            parent->left = NULL;
        else
            parent->right = NULL;
        delete curr;
        return;
    }

    // 2. Removing a node with single child
    if ((curr->left == NULL && curr->right != NULL) ||
        (curr->left != NULL && curr->right == NULL))
    {
        // Removing a node with single child - right child only
        if (curr->left == NULL && curr->right != NULL)
        {
            if (parent->left == curr)
                parent->left = curr->right;
            else
                parent->right = curr->right;
        }
        else
        // Removing a node with single child - left child only
        // if (curr->left != NULL && curr->right == NULL)
        {
            if (parent->left == curr)
                parent->left = curr->left;
            else
                parent->right = curr->left;
        }
        delete curr;
        return;
    }

    // 3. Removing a node with 2 children
    // Replace node with smallest value in right subtree
    if (curr->left != NULL && curr->right != NULL)
    {
        BstNodePtr rCurr = curr->right;
        // If curr's right child has left subtree,
        // move all the way down left to locate smallest element
        if (rCurr->left != NULL)
        {
            BstNodePtr lCurrP = rCurr;
            BstNodePtr lCurr = rCurr->left;
            while (lCurr->left != NULL)
            {
                lCurrP = lCurr;
                lCurr = lCurr->left;
            }
            curr->mData = lCurr->mData;
            lCurrP->left = lCurr->right;
            delete lCurr;
        }
        else // Right child of curr has no left subtree
        {
            curr->mData = rCurr->mData;
            curr->right = rCurr->right;
            delete rCurr;
        }
    }
}


void BinarySearchTree::inOrderTraversal() const
{
    inOrderTraversalIter(mRoot);
}


void BinarySearchTree::inOrderTraversalIter(BstNodePtr p) const
{
    stack<BstNodePtr> s;
    BstNodePtr curr = p;
    while (!s.empty() || curr)
    {
        if (curr)
        {
            s.push(curr);
            curr = curr->left;
        }
        else
        {
            curr = s.top();
            s.pop();
            cout << curr->mData << " ";
            curr = curr->right;
        }
    }
}


void BinarySearchTree::preOrderTraversal() const
{
    preOrderTraversal(mRoot);
}


void BinarySearchTree::preOrderTraversal(BstNodePtr p) const
{
    if (p != NULL)
    {
        cout << " " << p->mData << " ";
        if (p->left) preOrderTraversal(p->left);
        if (p->right) preOrderTraversal(p->right);
    }
}


void BinarySearchTree::postOrderTraversal() const
{
    postOrderTraversal(mRoot);
}


void BinarySearchTree::postOrderTraversal(BstNodePtr p) const
{
    if (p != NULL)
    {
        if (p->left) postOrderTraversal(p->left);
        if (p->right) postOrderTraversal(p->right);
        cout << " " << p->mData << " ";
    }
}


void BinarySearchTree::findSmallestElement() const
{
    if (mRoot != NULL)
    {
        BstNodePtr temp = mRoot;
        while (temp->left != NULL)
            temp = temp->left;
        cout << "Smallest element (using Iteration) is " << temp->mData << endl;
    }
}


void BinarySearchTree::findLargestElement() const
{
    if (mRoot != NULL)
    {
        cout << "Largest element is " << findLargestElement(mRoot) << endl;
    }
}


int BinarySearchTree::findLargestElement(BstNodePtr p) const
{
    if (p->right != NULL)
        return findLargestElement(p->right);
    else
        return p->mData;
}


void BinarySearchTree::findKthSmallestElement(uint k) const
{
    findKthSmallestElementIter(mRoot, k);
}


void BinarySearchTree::findKthSmallestElementIter(BstNodePtr p, uint k) const
{
    stack<BstNodePtr> s;
    BstNodePtr curr = p;
    while (!s.empty() || curr)
    {
        if (curr)
        {
            s.push(curr);
            curr = curr->left;
        }
        else
        {
            curr = s.top();
            s.pop();
            if (--k == 0)
                cout << curr->mData << " ";
            curr = curr->right;
        }
    }
}


void BinarySearchTree::findKthLargestElement(uint k) const
{
    if (mRoot != NULL)
    {
        uint index(k);
        findKthLargestElement(mRoot, index);
    }
}

void BinarySearchTree::findKthLargestElement(BstNodePtr p, uint& index) const
{
    if (p != NULL)
    {
        findKthLargestElement(p->right, index);
        if (--index == 0)
        {
            cout << p->mData << " ";
        }
        findKthLargestElement(p->left, index);
    }
}


uint BinarySearchTree::findTreeDepth() const
{
    uint depth(0);
    if (mRoot != NULL)
        depth = findTreeDepth(mRoot);

    return depth;
}


uint BinarySearchTree::findTreeDepth(BstNodePtr p) const
{
    if (p == NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        uint lDepth = findTreeDepth(p->left);
        uint rDepth = findTreeDepth(p->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}


BstNodePtr BinarySearchTree::first() const
{
    BstNodePtr temp = mRoot;
    if (temp != NULL)
    {
        while (temp->left != NULL)
            temp = temp->left;
    }
    return temp;
}


BstNodePtr BinarySearchTree::last() const
{
    BstNodePtr temp = mRoot;
    if (temp != NULL)
    {
        while (temp->right != NULL)
            temp = temp->right;
    }
    return temp;
}


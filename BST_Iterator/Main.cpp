#include "BinarySearchTree_WithIterator.h"
#include <iostream>

using namespace std;

int main()
{
    BinarySearchTree b;
    b.insert(10);
    BinarySearchTree::Iterator it = b.first();
    cout << it->mData << endl;
}


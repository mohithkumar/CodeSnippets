/**
Word Frequency calculator using HashMap
Program description:
The working of this program can be divided into 2 broad things:
A) Building HashTable
1. Requests user for a filename
2. Determines whether the given file is ASCII text file
3. If not ASCII text file, prints a message and exits
4. (If ASCII text file), It parses the file, reads every word and builds HashTable.
5. HashTable is basically an array of pointers to HashNodePtr.
6. Each element of the array, in turn points to a HashNode that has the same HashValue.
7. Each HashNode contains a word, its count and pointer to the next node.
8. For every word read from the file, its HashValue is calculated and is inserted into the HashTable adjacent to corresponding array element having same HashValue.
9. If the word already exists in HashTable, its count in the respective node is incremented else a new HashNode is created.

B) Counting the frequency of occurrence of words and retrieving the 'K' most common words.
1. A Binary Search Tree is constructed from each of the nodes in HashTable.
2. First 'N' number of words in the descending order of their frequencies are printed out.
*/


// The program has 4 files:
File 1: HashMap.h
typedef unsigned int uint;
typedef class HashNode* HashNodePtr;

class HashNode
{
  public:
    explicit HashNode(char* word);
    ~HashNode();

    char* getWord() const;
    uint getFreq() const;
    HashNodePtr getNext() const;

    void incrFreq();
    void setNext(HashNodePtr next);

  private:
    // Non-copyable
    HashNode(const HashNode &);
    HashNode& operator=(const HashNode &);

    char* mWord;    // Key
    uint mFreq;     // Value

    HashNodePtr mNext;
};

class HashTable
{
  public:
    HashTable();
    ~HashTable();

    void insertWordAndIncrementCount(char* word);
    void printHashTable();
    void printMostFrequentWords(uint number);

  private:
    // Non-copyable
    HashTable(const HashTable &);
    HashTable& operator=(const HashTable &);

    char* removeNonAlphas(char* word);
    uint getHashKey(char* word);

    uint mNumOfWords;
    HashNodePtr* mTable;
};

File 2: HashMap.cpp
#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;

namespace
{
    const unsigned int TABLE_SIZE(1000);
    const unsigned int MAX_WORD_SIZE(80);
};

HashNode::HashNode(char* word)
    : mWord(word), mFreq(1), mNext(NULL)
{

}

HashNode::~HashNode()
{
    delete mWord; mWord = NULL;
    mFreq = 0;
    mNext = NULL;
}

char* HashNode::getWord() const
{
    return mWord;
}

uint HashNode::getFreq() const
{
    return mFreq;
}

HashNodePtr HashNode::getNext() const
{
    return mNext;
}

void HashNode::incrFreq()
{
    ++mFreq;
}

void HashNode::setNext(HashNodePtr next)
{
    mNext = next;
}

HashTable::HashTable() : mNumOfWords(0)
{
    mTable = new HashNodePtr[TABLE_SIZE];
    for (uint i(0); i < TABLE_SIZE; ++i)
        mTable[i] = NULL;
}

HashTable::~HashTable()
{
    // Delete individual nodes of
    for (uint i(0); i < TABLE_SIZE; ++i)
    {
        HashNodePtr curr = mTable[i];
        while (curr != NULL)
        {
            HashNodePtr prev = curr;
            curr = curr->getNext();
            delete prev;
        }
    }
    delete[] mTable;
}

void HashTable::insertWordAndIncrementCount(char* word)
{
    char* realWord = removeNonAlphas(word);

    if (strlen(realWord))
    {
        uint hashValue = getHashKey(realWord);
        HashNodePtr node = mTable[hashValue];
        if (node)
        {
            HashNodePtr prev = NULL;
            bool wordFound(false);
            while ((node != NULL) && (wordFound == false))
            {
                prev = node;
                if (strcmp(node->getWord(), realWord) == 0)
                {
                    node->incrFreq();
                    wordFound = true;
                }
                node = node->getNext();
            }

            if (wordFound == false)
            {
                HashNodePtr newNode = new HashNode(realWord);
                prev->setNext(newNode);
                ++mNumOfWords;
            }
        }
        else // New node to the HashEntry
        {
            node = new HashNode(realWord);
            mTable[hashValue] = node;
            ++mNumOfWords;
        }
        // cout << realWord << "; HashValue " << hashValue << endl;
    }
    // else
        // cout << "Empty String" << endl;
}
 
void HashTable::printHashTable()
{
    for (uint i(0); i < TABLE_SIZE; ++i)
    {
        HashNodePtr curr = mTable[i];
        while (curr != NULL)
        {
            cout << curr->getWord() << "; " << curr->getFreq() << endl;
            curr = curr->getNext();
        }
    }
}

void HashTable::printMostFrequentWords(uint number)
{
    if (number > mNumOfWords)
    {
        cout << "Requested number greater that the words in table ("
             << mNumOfWords << ")" << endl;
    }
    else
    {
        BinarySearchTree bst;
        for (uint i(0); i < TABLE_SIZE; ++i)
        {
            HashNodePtr curr = mTable[i];
            while (curr != NULL)
            {
                bst.insert(curr);
                curr = curr->getNext();
            }
        }
        bst.printWordsWithLargestFreq(number);
    }
}

char* HashTable::removeNonAlphas(char* word)
{
    char buff[MAX_WORD_SIZE];
    uint i(0);
    uint j(0);
    while (word[i])
    {
        if (isalpha(word[i]))
        {
            buff[j] = word[i];
            ++j;
        }
        ++i;
    }
    buff[j] = '\0';

    char* retWord = new char[strlen(buff)+1];
    strcpy(retWord, buff);
    return retWord;
}

uint HashTable::getHashKey(char* word)
{
    uint aggValue(0);
    uint pos(0);
    while(word[pos])
    {
        aggValue += (word[pos] * (pos+1));
        ++pos;
    }
    return aggValue%TABLE_SIZE;
}

int main()
{
    char fileName[MAX_WORD_SIZE] = "";
    cout << "Enter file name (absolute path, please!!)" << endl;
    cin >> fileName;
 
    char systemCmd[MAX_WORD_SIZE*2] = "";
    strcat(systemCmd, "file ");
    strcat(systemCmd, fileName);
    strcat(systemCmd, " | grep ASCII");
    // cout << "System Command : " << systemCmd << endl;
    int ret = system(systemCmd);
    // cout << WEXITSTATUS(ret) << endl;

    if (!ret)
    {
        ifstream inFile(fileName);
        if (inFile.is_open())
        {
            HashTable hashTable;
            while (inFile)
            {
                char word[MAX_WORD_SIZE] = "";
                inFile >> word;
                // cout << word << endl;
                hashTable.insertWordAndIncrementCount(word);
            }
            inFile.close();

            // hashTable.printHashTable();
            hashTable.printMostFrequentWords(20);
        }
    }
    else
        cout << "Input file is not a text file!!" << endl;

    return 0;
}


File 3: BinarySearchTree.h
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
File 4: BinarySearchTree.cpp
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

// Feedback and suggestions are welcome.
// Posted 10th October 2013 by Mohith Suryanarayan


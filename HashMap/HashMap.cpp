#include "BinarySearchTree.h"
#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib>

namespace
{
    const unsigned int TABLE_SIZE(1000);
    const unsigned int MAX_WORD_SIZE(80);
};

using namespace std;


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


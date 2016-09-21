#ifndef HASH_MAP_H
#define HASH_MAP_H

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

#endif


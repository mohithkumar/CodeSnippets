#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

namespace
{
    const unsigned int MAX_WORD_SIZE(80);
};

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


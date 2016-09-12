#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<uint32_t> IntegerArray;

namespace
{
    const uint32_t MAX_INT_ARR_SZ(100000);
};


size_t InversionCount(const IntegerArray& arr)
{
    uint32_t count = 0;
    size_t n = arr.size();
    for (size_t i = 0; i < (n - 1); ++i)
    {
        for (size_t j = (i+1); j < n; ++j)
        {
            if (arr[i] > arr[j])
            {
                ++count;
            }
        }
    }

    return count;
}


int main()
{
    IntegerArray numVect(MAX_INT_ARR_SZ);
    uint32_t idx(0);
    ifstream inFile("IntegerArray.txt");
    if (inFile.is_open())
    {
        while (inFile)
        {
            uint32_t number;
            inFile >> number;
            if (inFile.eof())
            {
                break;
            }
            cout << number << endl;
            numVect[idx++] = number;
        }
        inFile.close();
    }

    cout << "Final count : " << numVect.size() << endl;
    cout << "Final count : " << InversionCount(numVect) << endl;

    return 0;
}


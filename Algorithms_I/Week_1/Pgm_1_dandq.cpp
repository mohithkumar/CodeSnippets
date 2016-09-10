#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<uint32_t> IntegerArray;

namespace
{
    const uint32_t MAX_INT_ARR_SZ(100000);
};


uint32_t merge(IntegerArray&       arr, 
               const IntegerArray& left, 
               const IntegerArray& right)
{
    uint32_t count(0);
    size_t leftIdx(0);
    size_t rightIdx(0);
    size_t leftSz(left.size());
    size_t rightSz(right.size());

    while ( (leftIdx < leftSz) || (rightIdx < rightSz) )
    {
        if (leftIdx == leftSz)
        {
            arr[leftIdx + rightIdx] = right[rightIdx];
            ++rightIdx;
        }
        else if (rightIdx == rightSz)
        {
            arr[leftIdx + rightIdx] = left[leftIdx];
            ++leftIdx;
        }
        else if (left[leftIdx] <= right[rightIdx])
        {
            arr[leftIdx + rightIdx] = left[leftIdx];
            ++leftIdx;
        }
        else
        {
            // cout << left[leftIdx] << " : " << right[rightIdx] << endl;
            arr[leftIdx + rightIdx] = right[rightIdx];
            ++rightIdx;
            count += leftSz - leftIdx;
        }
    }
   
    return count;
}


uint32_t InversionCount(IntegerArray& arr)
{
    size_t arrSz(arr.size());
    if (arrSz < 2)
    {
        return 0;
    }

    size_t mid(arrSz/2);
    IntegerArray left(arr.begin(), arr.begin() + mid);
    IntegerArray right(arr.begin() + mid, arr.end());

    uint32_t count = InversionCount(left);
    count += InversionCount(right);
    count += merge(arr, left, right);

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
            // cout << number << endl;
            numVect[idx++] = number;
        }
        inFile.close();
    }

    // for_each(numVect.cbegin(), numVect.cend(), [] (uint32_t n) {cout << n << endl;} );
    cout << "Final count : " << numVect.size() << endl;
    cout << "Final count : " << InversionCount(numVect) << endl;

    return 0;
}


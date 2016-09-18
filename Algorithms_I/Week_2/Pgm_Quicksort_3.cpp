#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<uint32_t> IntegerArray;
uint32_t comparisons(0);

uint32_t ChoosePivot(IntegerArray& arr, size_t l, size_t r)
{
    auto left = arr[l];
    auto right = arr[r-1];
    auto m = 0;
    auto length = r - l;
    if ((length % 2) == 0)
        m = left + (length/2) - 1;
    else
        m = left + (length/2);
    auto middle = arr[m];
    auto pivot = 0;

    if (left > middle) 
    {
        if (right > left)
        {
            pivot = left;
            arr[l] = arr[l];
        }
        else if (right < middle)
        {
            pivot = middle;
            arr[m] = arr[l];
        }
        else
        {
            pivot = right;
            arr[r-1] = arr[l];
        }
    }
    else
    {
        if (right < left)
        {
            pivot = left;
            arr[l] = arr[l];
        }
        else if (right > middle)
        {
            pivot = middle;
            arr[m] = arr[l];
        }
        else
        {
            pivot = right;
            arr[r-1] = arr[l];
        }
    }

    arr[l] = pivot;
    return pivot;
}


void Display(IntegerArray& arr)
{
    for (auto i(0); i < arr.size();)
    {
        cout << setw(3) << arr[i] << " ";
        if ((++i % 20) == 0)
            cout << endl;
    }
    cout << endl;
}


size_t Partition(IntegerArray& arr, size_t l, size_t r, uint32_t pivot)
{
    auto temp(0);
    auto i(l+1);
    for (auto j(l+1); j < r; ++j)
    {
        if (arr[j] < pivot)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            ++i;
        }
    }

    temp = arr[l];
    arr[l] = arr[i-1];
    arr[i-1] = temp;
    return i-1;
}


void QuickSort(IntegerArray& arr, size_t l, size_t r)
{
    if (l < r)
    {
        auto pivot = ChoosePivot(arr, l, r);

        auto p = Partition(arr, l, r, pivot);

        comparisons += (r - l - 1);

        QuickSort(arr, l, p);

        QuickSort(arr, p+1, r);
    }
}


int main()
{
    IntegerArray numVect;
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
            // cout << number << endl;
            numVect.push_back(number);
        }
        inFile.close();
    }

    // for_each(numVect.cbegin(), numVect.cend(), [] (uint32_t n) {cout << n << endl;} );
    cout << "Array Size : " << numVect.size() << endl;
    QuickSort(numVect, 0, numVect.size());
    // Display(numVect);
    cout << "Count : " << comparisons << endl;
    return 0;
}


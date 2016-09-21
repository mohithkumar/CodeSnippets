// Left-Truncatable prime numbers from 1 to 1000000000 in less than 0.5 seconds
#include <sstream>
#include <iostream>
#include <boost/assign/list_of.hpp>
#include <math.h>
#include "NumberCruncher.h"

using namespace std;

namespace
{
    const unsigned int MAX_NUMBER(1000000000 + 1);
    const unsigned short MAX_IDX(2166);
    const unsigned int MAX_NUMERALS(9 + 1);
};


NumberCruncher::NumberCruncher() : mLtPrimesMasterVector(MAX_IDX+10)
{
    mLtPrimesMasterVector = boost::assign::list_of(2)(3)(5)(7);

    boost::posix_time::ptime beginTime(boost::posix_time::microsec_clock::local_time());
    buildLtPrimeList();
    boost::posix_time::ptime endTime(boost::posix_time::microsec_clock::local_time());
    mDuration = endTime - beginTime;
}


NumberCruncher::~NumberCruncher()
{
/*
    mLtPrimesMasterVector.erase(mLtPrimesMasterVector.begin(),
                                mLtPrimesMasterVector.end());
*/
}


uint NumberCruncher::findNthLeftTruncatablePrime(const uint index)
{
    // Check index value
    if ( (index < 1) || (index > MAX_IDX) )
    {
        stringstream ss;
        ss << "Given value " << index << " is out of the valid range [1..2166]\n";
        throw ss.str();
    }

    return mLtPrimesMasterVector[index - 1];
}


void NumberCruncher::printNumberCrunchingDuration()
{
    cout << "Total time taken for computing LT Primes list is - " << mDuration << endl;
}


void NumberCruncher::buildLtPrimeList()
{
    UintVector ltPrimesVector(MAX_IDX/2);   // Fixing the size to avoid resizing during computation
    ltPrimesVector = boost::assign::list_of(3)(7);
    uint vectSz = ltPrimesVector.size();

    // Runs for 9 times from Units place thru to 1Billion
    for(uint multiplier = 10; multiplier < MAX_NUMBER; multiplier *= 10)
    {
        UintVector ltPrimesPerDecimal;
        // Runs for 9 numerals from 1 to 9
        for(uint numeral = 1; numeral < MAX_NUMERALS; ++numeral)
        {
            for(uint i = 0; i < vectSz ; ++i)
            {
                const uint result = (numeral * multiplier) + ltPrimesVector[i];
                if (isPrime(result))
                {
                    ltPrimesPerDecimal.push_back(result);
                }
            }
       }
       // Overwrite ltPrimesVector as we do not want numbers with 0 in them
       ltPrimesVector = ltPrimesPerDecimal;
       vectSz = ltPrimesVector.size();
       mLtPrimesMasterVector.insert(mLtPrimesMasterVector.end(), ltPrimesVector.begin(), ltPrimesVector.end());
   }
}


bool NumberCruncher::isPrime(const uint n)
{
    bool retVal(true);
    uint sqrtN = sqrt(n);
    for (uint i = 3; i <= sqrtN; i += 2)
    {
        if (n % i == 0)
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}

File 3: Main.cpp
#include <iostream>
#include "NumberCruncher.h"

using namespace std;

int main()
{
    NumberCruncher numberCruncher;
    numberCruncher.printNumberCrunchingDuration();

    uint pos(1);
    while (pos > 0)
    {
        cout << "\nEnter position (0 to quit) : ";
        cin >> pos;

        try
        {
            uint res = numberCruncher.findNthLeftTruncatablePrime(pos);
            cout << "L-T Prime at position " << pos << " is : " << res << endl;
        }
        catch(string& s)
        {
            cout << s << endl;
        }
    }

    return 0;
}


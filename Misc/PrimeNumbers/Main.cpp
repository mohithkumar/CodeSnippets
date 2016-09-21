// Left-Truncatable prime numbers from 1 to 1000000000 in less than 0.5 seconds
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


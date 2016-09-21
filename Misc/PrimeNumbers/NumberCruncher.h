#ifndef NUMBER_CRUNCHER_H
#define NUMBER_CRUNCHER_H
// Left-Truncatable prime numbers from 1 to 1000000000 in less than 0.5 seconds
// File 1: NumberCruncher.h
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

typedef unsigned int uint;
typedef std::vector<uint> UintVector;

class NumberCruncher
{
  public:
    NumberCruncher();
    ~NumberCruncher();

    uint findNthLeftTruncatablePrime(const uint index);

    void printNumberCrunchingDuration();

  private:
    NumberCruncher(const NumberCruncher&);
    NumberCruncher& operator=(const NumberCruncher&);

    void buildLtPrimeList();
    bool isPrime(const uint n);

    UintVector mLtPrimesMasterVector;
    boost::posix_time::time_duration mDuration;
};

#endif


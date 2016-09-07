#include "RaceException.h"

RaceException::RaceException(const std::string& reason) : mReason(reason)
{
}

RaceException::~RaceException() throw()
{
}

const char* RaceException::what() const throw()
{
    return mReason.c_str();
}


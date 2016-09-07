#ifndef RACEEXCEPTION_H
#define RACEEXCEPTION_H

#include <exception>
#include <string>

class RaceException : public std::exception
{
  public:
    RaceException(const std::string& reason);
    ~RaceException() throw();
    const char* what() const throw();
 
  private:
    std::string mReason;
};

#endif // RACEEXCEPTION_H


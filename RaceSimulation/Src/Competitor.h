#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <boost/noncopyable.hpp>
#include "Typedefs.h"

class Grassy;
class Mountainous;
class Swampy;

class Strong;
class Weak;
class Flight;

class Competitor : private boost::noncopyable
{
  public:
    virtual ~Competitor();

    // Define compatibilities
    virtual bool canMoveToIsland(boost::shared_ptr<Grassy> t) = 0;
    virtual bool canMoveToIsland(boost::shared_ptr<Mountainous> t) = 0;
    virtual bool canMoveToIsland(boost::shared_ptr<Swampy> t) = 0;

    virtual bool canTakeConnection(boost::shared_ptr<Strong> t) = 0;
    virtual bool canTakeConnection(boost::shared_ptr<Weak> t) = 0;
    virtual bool canTakeConnection(boost::shared_ptr<Flight> t) = 0;

    virtual void move() = 0;

    void setStartIsland(IslandPtr pIsland);
    bool reachedFinishPoint();
    std::string getName();

  protected:
    explicit Competitor(std::string name);

    IslandPtr mCurrIsland;
    IslandPtrsList mVisitedIslands;

  private:
    std::string mName;
};

#endif // COMPETITOR_H


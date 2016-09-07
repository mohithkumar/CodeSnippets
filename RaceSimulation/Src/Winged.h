#ifndef WINGED_H
#define WINGED_H

#include <boost/enable_shared_from_this.hpp>
#include "Competitor.h"

class Winged : public Competitor
             , public boost::enable_shared_from_this<Winged>
{
  public:
    explicit Winged(std::string name);
    ~Winged() {}

    bool canMoveToIsland(boost::shared_ptr<Grassy> t)       { return true; }
    bool canMoveToIsland(boost::shared_ptr<Mountainous> t)  { return false; }
    bool canMoveToIsland(boost::shared_ptr<Swampy> t)       { return true; }

    bool canTakeConnection(boost::shared_ptr<Strong> t)     { return true; }
    bool canTakeConnection(boost::shared_ptr<Weak> t)       { return true; }
    bool canTakeConnection(boost::shared_ptr<Flight> t)     { return true; }

    void move();

  private:
    bool mInSwampyIsland;
};

#endif // WINGED_H


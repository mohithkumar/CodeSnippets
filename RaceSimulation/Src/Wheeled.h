#ifndef WHEELED_H
#define WHEELED_H

#include <boost/enable_shared_from_this.hpp>
#include "Competitor.h"

class Wheeled : public Competitor
              , public boost::enable_shared_from_this<Wheeled>
{
  public:
    explicit Wheeled(std::string name);
    ~Wheeled() {}

    bool canMoveToIsland(boost::shared_ptr<Grassy> t)       { return true; }
    bool canMoveToIsland(boost::shared_ptr<Mountainous> t)  { return true; }
    bool canMoveToIsland(boost::shared_ptr<Swampy> t)       { return false; }

    bool canTakeConnection(boost::shared_ptr<Strong> t)     { return true; }
    bool canTakeConnection(boost::shared_ptr<Weak> t)       { return true; }
    bool canTakeConnection(boost::shared_ptr<Flight> t)     { return false; }

    void move();

  private:
    // No private members here!!
};

#endif // WHEELED_H


#ifndef LEGGED_H
#define LEGGED_H

#include <boost/enable_shared_from_this.hpp>
#include "Competitor.h"

class Legged : public Competitor
             , public boost::enable_shared_from_this<Legged>
{
  public:
    explicit Legged(std::string name);
    ~Legged() {}

    bool canMoveToIsland(boost::shared_ptr<Grassy> t)       { return true; }
    bool canMoveToIsland(boost::shared_ptr<Mountainous> t)  { return false; }
    bool canMoveToIsland(boost::shared_ptr<Swampy> t)       { return true; }

    bool canTakeConnection(boost::shared_ptr<Strong> t)     { return true; }
    bool canTakeConnection(boost::shared_ptr<Weak> t)       { return false; }
    bool canTakeConnection(boost::shared_ptr<Flight> t)     { return false; }

    void move();

  private:
    // No private members here!!
};

#endif // LEGGED_H


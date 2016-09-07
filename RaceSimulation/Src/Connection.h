#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include "Typedefs.h"

class Connection 
{
  public:
    virtual ~Connection() = 0;

    virtual bool checkIfAllowed(CompetitorPtr c) = 0;

    IslandPtrsList getIslands() const;
    IslandPtr getOtherIsland(IslandPtr pIsland) const;
    void addIsland(IslandPtr pisland);
    uint getNumberOfIslands() const;
    uint getInstanceId() const;

    void printIslandInstanceIds() const;

  protected:
    explicit Connection(uint instanceId);

  private:
    uint mInstanceId;
    IslandPtrsList mIslands;
};

class Strong : public Connection
             , public boost::enable_shared_from_this<Strong>
{
  public:
    explicit Strong(uint instanceId);
    ~Strong() {}

    bool checkIfAllowed(CompetitorPtr c);

  private:
    // No private members here!!
};

class Weak : public Connection
           , public boost::enable_shared_from_this<Weak>
{
  public:
    explicit Weak(uint instanceId);
    ~Weak() {}

    bool checkIfAllowed(CompetitorPtr c);

  private:
    // No private members here!!
};

class Flight : public Connection
             , public boost::enable_shared_from_this<Flight>
{
  public:
    explicit Flight(uint instanceId);
    ~Flight() {}

    bool checkIfAllowed(CompetitorPtr c);

  private:
    // No private members here!!
};

#endif // CONNECTION_H


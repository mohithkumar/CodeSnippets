#ifndef ISLAND_H
#define ISLAND_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include "Typedefs.h"
#include "RaceEngine.h"

class Island : private boost::noncopyable
{
  public:
    virtual ~Island() = 0;

    virtual bool checkIfAllowed(CompetitorPtr c) = 0;

    ConnectionPtrsSet getConnections() const;
    uint getNumberOfConnections() const;
    void addConnection(ConnectionPtr conn);
    IslandType getIslandType() const;

    bool isFinishPoint();
    uint getInstanceId() const;

    void printConnInstanceIds() const;

    virtual bool isSwampyIsland() = 0;

  protected:
    Island(uint instanceId, IslandType islandType);

  private:
    uint mInstanceId;
    IslandType mIslandType;
    ConnectionPtrsSet mConns;
};

class Grassy : public Island
             , public boost::enable_shared_from_this<Grassy>
{
  public:
    Grassy(uint instanceId, IslandType islandType);
    ~Grassy() {}

    bool checkIfAllowed(CompetitorPtr c);
    bool isSwampyIsland();

  private:
    // No private members here!! 
};

class Mountainous : public Island
                  , public boost::enable_shared_from_this<Mountainous>
{
  public:
    Mountainous(uint instanceId, IslandType islandType);
    ~Mountainous() {}

    bool checkIfAllowed(CompetitorPtr c);
    bool isSwampyIsland();

  private:
    // No private members here!!
};

class Swampy : public Island
             , public boost::enable_shared_from_this<Swampy>
{
  public:
    Swampy(uint instanceId, IslandType islandType);
    ~Swampy() {}

    bool checkIfAllowed(CompetitorPtr c);
    bool isSwampyIsland();

  private:
    // No private members here!!
};

#endif // ISLAND_H


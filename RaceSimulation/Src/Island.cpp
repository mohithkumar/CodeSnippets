#include <boost/foreach.hpp>
#include <iostream>
#include "Island.h"
#include "Connection.h"
#include "Competitor.h"

Island::Island(uint instanceId, IslandType islandType) 
    : mInstanceId(instanceId)
    , mIslandType(islandType)
    , mConns()
{
}

Island::~Island()
{
}

ConnectionPtrsSet Island::getConnections() const
{
    return mConns;
}

uint Island::getNumberOfConnections() const
{
    return mConns.size();
}

void Island::addConnection(ConnectionPtr conn)
{
    std::pair<ConnectionPtrsSet::iterator, bool> connPtrSetReturn;
    connPtrSetReturn = mConns.insert(conn);

    if (connPtrSetReturn.second == false)
    {
        std::cerr << "Failed to add connection with Id " 
                  << conn->getInstanceId() << " to Island - " 
                  << mInstanceId << std::endl;
    }
}

bool Island::isFinishPoint()
{
    bool retVal(false);
    if (mIslandType == FINISH)
        retVal = true;

    return retVal;
}

IslandType Island::getIslandType() const
{
    return mIslandType;
}

uint Island::getInstanceId() const
{
    return mInstanceId;
}

void Island::printConnInstanceIds() const
{
    // Print ALL Islands and Connections
    BOOST_FOREACH(const ConnectionPtr& pConn, mConns)
    {
        std::cout << pConn->getInstanceId() << " ";
    }
    std::cout << std::endl;
}

Grassy::Grassy(uint instanceId, IslandType islandType) 
    : Island(instanceId, islandType)
{
}

bool Grassy::checkIfAllowed(CompetitorPtr c)
{
    return c->canMoveToIsland(shared_from_this());
}

bool Grassy::isSwampyIsland()
{
    return false;
}

Mountainous::Mountainous(uint instanceId, IslandType islandType) 
    : Island(instanceId, islandType)
{
}

bool Mountainous::checkIfAllowed(CompetitorPtr c)
{
    return c->canMoveToIsland(shared_from_this());
}

bool Mountainous::isSwampyIsland()
{
    return false;
}

Swampy::Swampy(uint instanceId, IslandType islandType) 
    : Island(instanceId, islandType)
{
}

bool Swampy::checkIfAllowed(CompetitorPtr c)
{
    return c->canMoveToIsland(shared_from_this());
}

bool Swampy::isSwampyIsland()
{
    return true;
}



#include <iostream>
#include "Connection.h"
#include "Island.h"
#include "Competitor.h"

Connection::Connection(uint instanceId)
    : mInstanceId(instanceId)
    , mIslands()
{
}

Connection::~Connection()
{
}

IslandPtrsList Connection::getIslands() const
{
    return mIslands;
}

IslandPtr Connection::getOtherIsland(IslandPtr pIsland) const
{
    for (size_t i = 0; i < mIslands.size(); ++i)
    {
        if (pIsland->getInstanceId() != mIslands[i]->getInstanceId())
        {
            return mIslands[i];       
        }
    }
    return IslandPtr();
}

void Connection::addIsland(IslandPtr pIsland)
{
    // IslandPtrsSet, instead of IslandPtrsList, needed probably ?!
    if (mIslands.size() < 2)
    {
        if (mIslands.empty())
            mIslands.push_back(pIsland);
        else
        {
            if (mIslands[0]->getInstanceId() != pIsland->getInstanceId())
            {
                mIslands.push_back(pIsland);
            }
            else
            {
                std::cerr << "Island with InstanceId " 
                          << pIsland->getInstanceId() 
                          << " already exists." << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "This connection has islands on either sides!!" << std::endl;
    }
}

uint Connection::getNumberOfIslands() const
{
    return mIslands.size();
}

uint Connection::getInstanceId() const
{
    return mInstanceId;
}

void Connection::printIslandInstanceIds() const
{
    for(uint i(0); i < mIslands.size(); ++i)
    {
        std::cout << mIslands[i]->getInstanceId() << " ";
    }
    std::cout << std::endl;
}

Strong::Strong(uint instanceId) : Connection(instanceId)
{
}

bool Strong::checkIfAllowed(CompetitorPtr c)
{
    return c->canTakeConnection(shared_from_this());
}

Weak::Weak(uint instanceId) : Connection(instanceId)
{
}

bool Weak::checkIfAllowed(CompetitorPtr c)
{
    return c->canTakeConnection(shared_from_this());
}

Flight::Flight(uint instanceId) : Connection(instanceId)
{
}

bool Flight::checkIfAllowed(CompetitorPtr c)
{
    return c->canTakeConnection(shared_from_this());
}



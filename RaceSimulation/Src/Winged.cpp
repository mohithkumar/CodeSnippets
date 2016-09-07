#include <boost/foreach.hpp>
#include <iostream>
#include "Winged.h"
#include "Island.h"
#include "Connection.h"
#include "RaceEngine.h"

Winged::Winged(std::string name) : Competitor(name)
                                 , mInSwampyIsland(false)
{
}

void Winged::move()
{
    std::cout << "Before movement : " << getName()
              << " (having WING) is at Island " << mCurrIsland->getInstanceId()
              << std::endl;

    if (mInSwampyIsland)
    {
        mInSwampyIsland = false;
    }
    else
    {
        // Get all possible connections
        ConnectionPtrsSet connPtrs = mCurrIsland->getConnections();

        // From the list of all possible conns, extract the ones that are favourable into takeableConnxns
        ConnectionPtrsList takeableConnxns;
        BOOST_FOREACH(const ConnectionPtr& pConn, connPtrs)
        {
            if (pConn->checkIfAllowed(shared_from_this()))
            {
                takeableConnxns.push_back(pConn);
            }
        }

        // Get the other end of the connexn and check if the island is go-able
        // If yes, add the island to goableIslands
        bool adjacentToFinish(false);
        IslandPtr newIsland; IslandPtr finishIsland;
        IslandPtrsList goableIslands;

        ConnectionPtrsList::iterator it = takeableConnxns.begin();
        ConnectionPtrsList::iterator itEnd = takeableConnxns.end();
        for (; (it != itEnd) && (adjacentToFinish == false); ++it)
        {
            newIsland = (*it)->getOtherIsland(mCurrIsland);
            if (newIsland)
            {
                if (newIsland->checkIfAllowed(shared_from_this()))
                {
                    goableIslands.push_back(newIsland);
                    if (newIsland->isFinishPoint())
                    {
                        finishIsland = newIsland;
                        adjacentToFinish = true;
                    }
                }
            }
        }

        // Store current island into the Visited Islands list
        mVisitedIslands.push_back(mCurrIsland);

        if (adjacentToFinish)
        {
            mCurrIsland = finishIsland;
        }
        else
        {
            if (goableIslands.size() != 0)
            {
                // Go to next island [but randomise the decision]
                uint idx = rand() % goableIslands.size();
                mCurrIsland = goableIslands[idx];
            }
        }

        if (mCurrIsland->isSwampyIsland()) 
            mInSwampyIsland = true;
    }

    std::cout << "After movement  : " << getName()
              << " (having WING) is at Island " << mCurrIsland->getInstanceId()
              << std::endl;
}


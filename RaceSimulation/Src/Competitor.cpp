#include <boost/foreach.hpp>
#include "Competitor.h"
#include "Island.h"

Competitor::Competitor(std::string name)
    : mCurrIsland()
    , mVisitedIslands()
    , mName(name)
{
}

Competitor::~Competitor()
{
}

void Competitor::setStartIsland(IslandPtr pIsland)
{
    mCurrIsland = pIsland;
}

std::string Competitor::getName()
{
    return mName;
}

bool Competitor::reachedFinishPoint()
{
    return mCurrIsland->isFinishPoint();
}


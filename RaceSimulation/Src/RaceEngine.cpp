#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include "RaceEngine.h"
#include "Winged.h"
#include "Wheeled.h"
#include "Legged.h"
#include "Island.h"
#include "Connection.h"
#include "RaceException.h"

using namespace std;

namespace
{
    const unsigned short MAX_MOVES_PER_COMPETITOR(10);
};

RaceEngine* RaceEngine::mInstance = 0;

RaceEngine& RaceEngine::getInstance()
{
    if (!mInstance)
    {
        RaceEngine* p = new RaceEngine();
        mInstance = p;
        atexit(&RaceEngine::destroyInstance);
    }
    return *mInstance;
}

void RaceEngine::destroyInstance()
{
    if (mInstance)
    {
        delete mInstance;
        mInstance = NULL;
    }
}

RaceEngine::RaceEngine() : mpCompetitors()
                         , mpIslands()
                         , mpConnections()
                         , mpRaceResults()
{
}

RaceEngine::~RaceEngine()
{
}

void RaceEngine::readCompetitorsFiles()
{
    uint n;
    string fileName("Competitor_");
    stringstream ss;
    string valueStr;
    StringVector lineEntry;

    cout << "Enter the number of competitors : ";
    cin >> n;

    if (n < 1)
        return;

    for (uint i(1); i <= n; ++i)
    {
        ss << fileName << i << ".csv";
        cout << "Reading " << ss.str() << ".." << endl;

        string relativeFilePath = "../";
        relativeFilePath += ss.str();
        ifstream inputFile(relativeFilePath.c_str());
        if (inputFile.is_open())
        {
            while (getline (inputFile, valueStr, ','))
            {
                lineEntry.push_back(valueStr);
            }
            if (checkCompFileAndCreate(lineEntry) == false)
            {
                cerr << "File " << ss.str() << " does not conform to syntax/semantics; please check!!" << endl;
            }
            lineEntry.clear();
            inputFile.close();
            inputFile.clear();
        }
        else
        {
            cerr << "Error opening file for competitor number " << i+1 << endl;
        }
        ss.str("");
    }

#if 0
    // Print ALL Competitors
    BOOST_FOREACH(const CompetitorPtr& pCompetitor, mpCompetitors)
    {
        cout << "Instance Id - " << pCompetitor->getName() 
             << "; Instance Type - " << typeid(*pCompetitor).name()
             << endl;
    }
#endif
}

void RaceEngine::readIslandMapFile()
{
    if (mpCompetitors.size() > 0)
    {
        string line;
        StringVector lineEntry;

        string relativeFilePath = "../";
        relativeFilePath += "MapFile.csv";
        ifstream inputFile(relativeFilePath.c_str());
        if (inputFile.is_open())
        {
            cout << "Reading MapFile.csv.." << endl;
            // Read each line
            while (getline(inputFile, line))
            {
                // cout << "Line is " << line << endl;
                boost::split(lineEntry, line, boost::is_any_of(","), boost::token_compress_off);

                // Perform check!!
                if (checkMapFileAndCreate(lineEntry) == false)
                {
                    cerr << "File MapFile.csv does not conform to syntax/semantics; please check!!" << endl;
                }
            }

            // Some checks for MapFile entries
            uint numOfStartPoints(0); uint numOfFinishPoints(0);
            IslandPtr startIsland;
            BOOST_FOREACH(IslandPtr pIsland, mpIslands)
            {
                if (pIsland->getIslandType() == START)
                {
                    // Store startIsland to be assigned to ALL competitors initially
                    startIsland = pIsland;
                    ++numOfStartPoints;
                }
                if (pIsland->getIslandType() == FINISH)
                    ++numOfFinishPoints;

                if ((numOfFinishPoints > 1) || (numOfFinishPoints > 1))
                    throw RaceException("More than 1 islands identified as START and/or FINISH points");
            }
           
            inputFile.close();

            // printIslandsAndConns();  

            // Place ALL Competitors on START Island
            BOOST_FOREACH(const CompetitorPtr& pCompetitor, mpCompetitors)
            {
                pCompetitor->setStartIsland(startIsland);
            }
        }
        else
        {
            cerr << "Error opening the file MapFile.csv. Check for file permissions." << endl;
        }
    }
    else
    {
        cerr << "No competitor's details entered. Please try again." << endl;
        readCompetitorsFiles();
    }
}

void RaceEngine::runSimulation()
{
    uint numOfCompetitors(mpCompetitors.size());
    bool toContinue(true);
    uint numOfMoves(0);
    uint maxMoves(MAX_MOVES_PER_COMPETITOR * numOfCompetitors);

    while ((toContinue) && (numOfMoves < maxMoves))
    {
        uint numOfFinishedCompetitors(0);

        CompetitorPtrsList::iterator it = mpCompetitors.begin();
        CompetitorPtrsList::iterator itEnd = mpCompetitors.end();
        while (it != itEnd)
        {
            CompetitorPtrsList::iterator next = it;
            ++next;
            if ((*it)->reachedFinishPoint())
            {
                ++numOfFinishedCompetitors;

                mpRaceResults.push_back(*it);
                mpCompetitors.erase(it);
            }
            else
            {
                (*it)->move();
            }
            it = next;
        }

        if (numOfFinishedCompetitors == numOfCompetitors)
            toContinue = false;

        ++numOfMoves;
    }

    // printIslandsAndConns();  
}

void RaceEngine::printResults()
{
    uint numOfFinishedCompetitors(mpRaceResults.size());
    for(uint i(0); i < numOfFinishedCompetitors; ++i)
    {
        cout << "Name - " << (mpRaceResults[i])->getName()
             << "; Overall position - " << i+1 << endl;
    }
}

bool RaceEngine::checkCompFileAndCreate(StringVector& lineEntry)
{
    bool retVal(true);
    if (lineEntry.size() != 2)
    {
        retVal = false;
    }
    else
    {
        CompetitorType vehicle = static_cast<CompetitorType>(atoi(lineEntry[1].c_str()));
        // uint vehicle = boost::lexical_cast<uint>(lineEntry[1]);
        switch(vehicle)
        {
          case WINGED:
            {
                CompetitorPtr pCompetitor(new Winged(lineEntry[0]));
                mpCompetitors.push_back(pCompetitor);
            }
            break;

          case WHEELED:
            {
                CompetitorPtr pCompetitor(new Wheeled(lineEntry[0]));
                mpCompetitors.push_back(pCompetitor);
            }
            break;

          case LEGGED:
            {
                CompetitorPtr pCompetitor(new Legged(lineEntry[0]));
                mpCompetitors.push_back(pCompetitor);
            }
            break;

          default:
            retVal = false;
        }
    }
    return retVal;
}

bool RaceEngine::checkMapFileAndCreate(StringVector& lineEntry)
{
    bool retVal(true);
    if (lineEntry.size() != 5)
    {
        retVal = false;
    }
    else
    {
        IslandType islandType = static_cast<IslandType>(atoi(lineEntry[0].c_str()));
        IslandTerrain islandTerrain = static_cast<IslandTerrain>(atoi(lineEntry[1].c_str()));
        uint islandInstId = atoi(lineEntry[2].c_str());
        ConnectionType connType = static_cast<ConnectionType>(atoi(lineEntry[3].c_str()));
        uint connInstId = atoi(lineEntry[4].c_str());

        if ( ((islandType < 1) || (islandType > 3)) ||
             ((islandTerrain < 1) || (islandTerrain > 3)) ||
             ((connType < 1) || (connType > 3)) )
        {
            retVal = false;
        }

        IslandPtr pIsland;
        pair<IslandPtrsSet::iterator, bool> islandPtrSetReturn; // TODO - Really Needed?
        switch(islandTerrain)
        {
          case GRASSY:
            {
                pIsland.reset(new Grassy(islandInstId, islandType));
                islandPtrSetReturn = mpIslands.insert(pIsland);
            }
            break;

          case MOUNTAINOUS:
            {
                pIsland.reset(new Mountainous(islandInstId, islandType));
                islandPtrSetReturn = mpIslands.insert(pIsland);
            }
            break;

          case SWAMPY:
            {
                pIsland.reset(new Swampy(islandInstId, islandType));
                islandPtrSetReturn = mpIslands.insert(pIsland);
            }
            break;

          default:
            break;
        }

        ConnectionPtr pConnection;
        pair<ConnectionPtrsSet::iterator, bool> connPtrSetReturn; // TODO - Really Needed?
        switch(connType)
        {
          case STRONG:
            {
                pConnection.reset(new Strong(connInstId));
                connPtrSetReturn = mpConnections.insert(pConnection);
            }
            break;

          case WEAK:
            {
                pConnection.reset(new Weak(connInstId));
                connPtrSetReturn = mpConnections.insert(pConnection);
            }
            break;

          case FLIGHT:
            {
                pConnection.reset(new Flight(connInstId));
                connPtrSetReturn = mpConnections.insert(pConnection);
            }
            break;

          default:
            break;
        }

        // Add Connection to the Island
        if (pConnection)
        {
            IslandPtrsSet::iterator it = mpIslands.begin();
            IslandPtrsSet::iterator itEnd = mpIslands.end();

            for(; it != itEnd; ++it)
            {
                if (islandInstId == (*it)->getInstanceId())
                {
                    (*it)->addConnection(pConnection);
                }
            }
        }

        // Add Island to the Connection
        if (pIsland)
        {
            ConnectionPtrsSet::iterator it = mpConnections.begin();
            ConnectionPtrsSet::iterator itEnd = mpConnections.end();

            for(; it != itEnd; ++it)
            {
                if (connInstId == (*it)->getInstanceId())
                {
                    (*it)->addIsland(pIsland);
                }
            }
        }
    }
    return retVal;
}

void RaceEngine::printIslandsAndConns()
{
    // Print ALL Islands and Connections
    BOOST_FOREACH(const IslandPtr& pIsland, mpIslands)
    {
        cout << "Island Id - " << pIsland->getInstanceId() 
             // << "; Instance Type - " << typeid(*pIsland).name()
             << "; Num of Connxns - " << pIsland->getNumberOfConnections()
             << "; FinishPoint - " << pIsland->isFinishPoint();
        cout << ". Connxn Ids are : ";
        pIsland->printConnInstanceIds();
    }

    BOOST_FOREACH(const ConnectionPtr& pConn, mpConnections)
    {
        cout << "Connxn Id - " << pConn->getInstanceId() 
             // << "; Instance Type - " << typeid(*pConn).name()
             << "; Num of Islands - " << pConn->getNumberOfIslands();
        cout << ". Island Ids are : ";
        pConn->printIslandInstanceIds();
    }
}

bool CompareConnPtrs::operator() (const ConnectionPtr lhs, const ConnectionPtr rhs) const
{
    return (lhs->getInstanceId() < rhs->getInstanceId());
}

bool CompareIslandPtrs::operator() (const IslandPtr lhs, const IslandPtr rhs) const
{
    return (lhs->getInstanceId() < rhs->getInstanceId());
}


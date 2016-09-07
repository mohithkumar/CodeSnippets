#ifndef RACEENGINE_H
#define RACEENGINE_H

#include "Typedefs.h"

struct CompareConnPtrs 
{
    bool operator() (const ConnectionPtr lhs, const ConnectionPtr rhs) const;
};
typedef std::set<ConnectionPtr, CompareConnPtrs> ConnectionPtrsSet;

struct CompareIslandPtrs 
{
    bool operator() (const IslandPtr lhs, const IslandPtr rhs) const;
};
typedef std::set<IslandPtr, CompareIslandPtrs> IslandPtrsSet;

class RaceEngine
{
  public:
    static RaceEngine& getInstance();
    void readCompetitorsFiles();
    void readIslandMapFile();
    void runSimulation();
    void printResults();

  private:
    static void destroyInstance();

    RaceEngine();
    ~RaceEngine();

    RaceEngine(const RaceEngine&);
    RaceEngine& operator=(const RaceEngine&);

    // These functions carry out syntactic/semantic checks and create required objects
    bool checkCompFileAndCreate(StringVector& lineEntry);
    bool checkMapFileAndCreate(StringVector& lineEntry);

    void printIslandsAndConns();

    CompetitorPtrsList mpCompetitors;
    IslandPtrsSet mpIslands;
    ConnectionPtrsSet mpConnections;

    CompetitorPtrsList mpRaceResults;

    static RaceEngine* mInstance;
};

#endif // RACEENGINE_H


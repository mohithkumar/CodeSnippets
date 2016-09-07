#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <vector>
#include <set>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

// #include "Connection.h"
// #include "Island.h"
// #include "Competitor.h"

class Connection;
typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef std::vector<ConnectionPtr> ConnectionPtrsList;

class Island;
typedef boost::shared_ptr<Island> IslandPtr;
typedef std::vector<IslandPtr> IslandPtrsList;

class Competitor;
typedef boost::shared_ptr<Competitor> CompetitorPtr;
typedef std::vector<CompetitorPtr> CompetitorPtrsList;

typedef std::vector<std::string> StringVector;

typedef unsigned int uint;
typedef unsigned short ushort;

typedef enum 
{
    START = 1,
    INTERMEDIATE,
    FINISH,
} IslandType;

typedef enum 
{
    GRASSY = 1,
    MOUNTAINOUS,
    SWAMPY,
} IslandTerrain;

typedef enum 
{
    STRONG = 1,
    WEAK,
    FLIGHT,
} ConnectionType;

typedef enum 
{
    WINGED = 1,
    WHEELED,
    LEGGED,
} CompetitorType;

#endif // TYPEDEFS_H


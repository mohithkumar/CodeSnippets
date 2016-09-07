#include <iostream>
#include "RaceEngine.h"
#include "RaceException.h"

using namespace std;

typedef unsigned int uint;

int main()
{
    RaceEngine& raceEngine = RaceEngine::getInstance();

    try
    {
        raceEngine.readCompetitorsFiles();
        raceEngine.readIslandMapFile();
        raceEngine.runSimulation();
        raceEngine.printResults();
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unrecognised exception" << endl;
    }

    return 0;
}


Competitor File details:
-----------------------
The file name will be of the form 'Competitor_*.csv' where * starts from 1 and gets incremented sequentially by 1.
There shall be present only one entry in the file; any more than this will not be considered. Syntax of the entry will be:
<Name>,<Vehicle>

where 'Name' is a string
      'Vehicle' is a number ranging from 1 to 3 to represent 'WINGED', 'WHEELED' and 'LEGGED' respectively.

E.g.,
Peter,1


===============================================================================


Map File details:
----------------
The file name will be MapFile.csv and will have multiple entries with the following syntax:
<IslandType>,<IslandTerrain>,<IslandInstanceId>,<ConnectionType>,<ConnectionInstanceId>

where 'IslandType' is a number ranging from 1 to 3 to represent 'START', 'INTERMEDIATE' and 'FINISH' respectively.
      'IslandTerrain' is a number ranging from 1 to 3 to represent 'GRASSY', 'MOUNTAINOUS' and 'SWAMPY' respectively.
      'IslandInstanceId' is a number that starts from 1 and gets incremented sequentially by 1; this number is unique across ALL Islands.
      'ConnectionType' is a number ranging from 1 to 3 to represent 'STRONG', 'WEAK' and 'FLIGHT' connections respectively.
      'ConnectionInstanceId' is a number that starts from 1 and gets incremented sequentially by 1; this number is unique across ALL Connections.

As per the diagram, IslandInstanceId varies from 1 to 14
                    ConnectionInstanceId varies from 1 to 19

E.g.,

1,1,1,1,1


===============================================================================


This file contains the input csv files for Competitors (viz., Competitor_1.csv, Competitor_2.csv and Competitor_3.csv) and Map (MapFile.csv).

MapFile.csv has been drawn up as per the above syntax; legend for the file can be found in MapLegend.pdf.

To compile the project:
----------------------
$ cd Src
$ make

To run the project:
------------------
$ ./RaceSimulator
Enter the number of competitors : <Enter the number, eg. 3>
...
...
...


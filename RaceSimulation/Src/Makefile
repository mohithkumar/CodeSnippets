CXX = g++
INCLUDES= -I. -I/usr/include/
LIBS = -L/usr/lib/ -lboost_system -lboost_program_options
CXXFLAGS = -g -Wall $(INCLUDES) # -DFILE_BASED
SRCM = RaceEngine.cpp Island.cpp Connection.cpp Competitor.cpp Winged.cpp Wheeled.cpp Legged.cpp RaceException.cpp
OBJM = $(SRCM:.cpp=.o)
TARGET = RaceSimulator

all: $(TARGET)

$(TARGET): Main.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ Main.cpp $(LIBS) $(OBJM)

# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJM) $(TARGET)


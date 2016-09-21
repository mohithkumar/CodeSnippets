CXX = g++ --std=c++11
INCLUDES= -I. -I/usr/include/
LIBS = -L/usr/lib/ -lboost_system -lboost_program_options
CXXFLAGS = -g -Wall $(INCLUDES) # -DFILE_BASED
SRCM = BFS_Graphs.cpp
OBJM = $(SRCM:.cpp=.o)
TARGET = BFS_Graphs

all: $(TARGET)

$(TARGET): Main.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ Main.cpp $(LIBS) $(OBJM)

# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJM) $(TARGET)


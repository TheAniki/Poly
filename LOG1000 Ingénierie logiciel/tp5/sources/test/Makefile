CXX = g++
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
SRCM= ../Emission.cpp ../Chaine.cpp
OBJM = $(SRCM:.cpp=.o)
LINKFLAGS= -lcppunit

EmissionTests: EmissionTest.h main.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(OBJM) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

.cpp.o: 
	$(CXX) $(CXXFLAGS) -c $< -o $@


#
# Created  by rbh
# Modified by nas, 16/01/16
#

INCLUDEDIR = ../headers

vpath %.h   $(INCLUDEDIR)

CXXFLAGS = -std=c++11 -g -I $(INCLUDEDIR) -Wall -Wfatal-errors

OBJECTS =  position.o route.o track.o utilities.o xmlparser.o


main : main.cpp $(OBJECTS)
	g++ $(CXXFLAGS) main.cpp $(OBJECTS) -o main


position.o : position.cpp position.h gpxp.h utilities.h
	g++ $(CXXFLAGS) -c position.cpp -o position.o

route.o : route.cpp route.h gpxp.h position.h xmlparser.h
	g++ $(CXXFLAGS) -c route.cpp -o route.o

track.o : track.cpp track.h gpxp.h position.h route.h utilities.h xmlparser.h
	g++ $(CXXFLAGS) -c track.cpp -o track.o

utilities.o : utilities.cpp utilities.h gpxp.h
	g++ $(CXXFLAGS) -c utilities.cpp -o utilities.o

xmlparser.o : xmlparser.cpp xmlparser.h
	g++ $(CXXFLAGS) -c xmlparser.cpp -o xmlparser.o


clean:
	rm -f *.o main

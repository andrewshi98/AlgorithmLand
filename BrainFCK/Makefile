SRCS=BFK.cpp BFKparser.cpp BFKengine.cpp
OBJS=$(subst .cpp,.o, $(SRCS))

BFK: $(OBJS)
	g++ -o BFK $(OBJS)

BFK.o : BFK.cpp BFKparser.hpp BFKengine.hpp
	g++ -c BFK.cpp

BFKparser.o: BFKparser.hpp BFKparser.cpp
	g++ -c BFKparser.cpp

BFKengine.o: BFKengine.hpp BFKengine.cpp
	g++ -c BFKengine.cpp

clean:
	rm *.o BFK

CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: RandomGraph

RandomGraph: RandomGraph.o euler_circuit.o graph.o
	$(CXX) $(CXXFLAGS) -o RandomGraph RandomGraph.o euler_circuit.o graph.o

RandomGraph.o: RandomGraph.cpp graph.hpp euler_circuit.hpp
	$(CXX) $(CXXFLAGS) -c RandomGraph.cpp

euler_circuit.o: euler_circuit.cpp graph.hpp euler_circuit.hpp
	$(CXX) $(CXXFLAGS) -c euler_circuit.cpp

graph.o: graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

clean:
	rm -f *.o RandomGraph

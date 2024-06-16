CXX=clang++
CXXFLAGS=-std=c++11 -Werror
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCESDemo = Board.cpp Card.cpp Catan.cpp Edge.cpp Hexagon.cpp Player.cpp Vertex.cpp Demo.cpp
SOURCESTest = Board.cpp Card.cpp Catan.cpp Edge.cpp Hexagon.cpp Player.cpp Vertex.cpp testCounter.cpp tests.cpp
SOURCESOneRoad = Board.cpp Card.cpp Catan.cpp Edge.cpp Hexagon.cpp Player.cpp Vertex.cpp OneRoad.cpp

OBJECTSDemo = $(SOURCESDemo:.cpp=.o) 
OBJECTSTest = $(SOURCESTest:.cpp=.o) 
OBJECTSOneRoad = $(SOURCESOneRoad:.cpp=.o) 

fullGame: demo
	./demo

tests: testCounter
	./testCounter
catan: oneRoad
	./oneRoad

demo: $(OBJECTSDemo)
	$(CXX) $(CXXFLAGS) $^ -o $@

testCounter: $(OBJECTSTest)
	$(CXX) $(CXXFLAGS) $^ -o $@

oneRoad: $(OBJECTSOneRoad)
	$(CXX) $(CXXFLAGS) $^ -o $@

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

catanvalgrind: oneRoad
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./oneRoad 2>&1 | { egrep "lost| at " || true; }

testvalgrind: testCounter
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testCounter 2>&1 | { egrep "lost| at " || true; }

demovalgrind: demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo testCounter oneRoad

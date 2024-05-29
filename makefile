# 211344015 alonsuissa12@gmail.com

CXX = g++
CXXFLAGS = -std=c++14 -Werror -Wsign-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Catan.cpp Player.cpp Resources.cpp Test.cpp Demo.cpp
OBJECTS = Catan.o Resources.o Player.o Test.o Demo.o

.PHONY: all clean run valgrind tidy catan

all: demo test

catan: demo
	./demo

demo: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(filter-out Test.o,$(OBJECTS)) -o demo

test: $(OBJECTS) Test.o TestCounter.o
	$(CXX) $(CXXFLAGS) $(filter-out Demo.o,$(OBJECTS)) TestCounter.o  -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

Catan.o: Catan.cpp
	$(CXX) $(CXXFLAGS) -c Catan.cpp -o Catan.o

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o

Resources.o: Resources.cpp
	$(CXX) $(CXXFLAGS) -c Resources.cpp -o Resources.o

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp -o Test.o

TestCounter.o: TestCounter.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c TestCounter.cpp -o TestCounter.o


Demo.o: Demo.cpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp -o Demo.o

clean:
	rm -f *.o demo test
# 211344015 alonsuissa12@gmail.com

CXX=g++
CXXFLAGS=-std=c++14 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=Board.cpp Catan.cpp Player.cpp Resources.cpp
OBJECTS=Resources.o Board.o Catan.o Player.o

.PHONY: all clean run valgrind tidy catan

all: demo

catan: demo
	./demo

demo: $(OBJECTS) Demo.o
	$(CXX) -std=c++14 -Werror -Wsign-conversion $(OBJECTS) Demo.o -o demo

#test: TestCounter.o Test.o $(OBJECTS)
#	$(CXX) -std=c++14 -Werror -Wsign-conversion  $(OBJECTS) -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo #test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

Board.o: Board.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Board.cpp -o Board.o

Catan.o: Catan.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Catan.cpp -o Catan.o

Player.o: Player.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Player.cpp -o Player.o

Resources.o: Resources.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Resources.cpp -o Resources.o

#Test.o: Test.cpp
#	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Test.cpp -o Test.o

Demo.o: Demo.cpp
	$(CXX) -std=c++14 -Werror -Wsign-conversion -c Demo.cpp -o Demo.o

clean:
	rm -f *.o demo #test

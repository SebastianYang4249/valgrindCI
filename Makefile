CXX = g++
all : valgrind_analysis.cpp
	$(CXX) utils.cpp utils.h valgrind_analysis.cpp valgrind_analysis.h file.cpp file.h list.cpp list.h -o main
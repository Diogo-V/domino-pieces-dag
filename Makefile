CC = g++
debug_flags = -O3 -Wall -std=c++11 -g -lm
flags = -O3 -Wall -std=c++11 -lm

# randomDAG input parameters
params = 8 0.3

# Compiles randomDAG, creates a new dag and puts it into a file
random: src/randomDAG.cpp
	$(CC) $(flags) -o cmake-build-debug/create-graph src/randomDAG.cpp
	./cmake-build-debug/create-graph $(params) > tests/problems.txt

all: random src/main.cpp src/graph.cpp
	cat tests/problems.txt
	$(CC) $(flags) -o cmake-build-debug/main src/main.cpp src/graph.cpp

run: all
	time ./cmake-build-debug/main < tests/problems.txt

debug: src/main.cpp
	$(CC) $(debug_flags) -o cmake-build-debug/debug src/main.cpp

clean:
	rm -f cmake-build-debug/main cmake-build-debug/randomDAG

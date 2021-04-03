CC = g++
debug_flags = -O3 -Wall -std=c++11 -g -lm
flags = -O3 -Wall -std=c++11 -lm

# randomDAG input parameters
params = 30000 0.3

# Compiles randomDAG, creates a new dag and puts it into a file
random: src/randomDAG.cpp
	$(CC) $(flags) -o cmake-build-debug/create-graph src/randomDAG.cpp
	./cmake-build-debug/create-graph $(params) > tests/problems.txt

all: random src/final.cpp
	$(CC) $(flags) -o cmake-build-debug/final src/final.cpp

run: all
	time ./cmake-build-debug/final < tests/problems.txt

debug: src/main.cpp
	$(CC) $(debug_flags) -o cmake-build-debug/debug src/main.cpp

clean:
	rm -f cmake-build-debug/final cmake-build-debug/randomDAG

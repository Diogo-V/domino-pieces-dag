CC = g++
dflags = -O3 -Wall -std=c++11 -g -lm
flags = -O3 -Wall -std=c++11 -lm

# randomDAG input parameters
params = 10 1

# Compiles randomDAG, creates a new dag and puts it into a file
random: src/randomDAG.cpp
	$(CC) $(flags) -o build/randomDAG src/randomDAG.cpp
	./build/randomDAG $(params) > build/problem.txt 

build: random src/main.cpp
	cat build/problem.txt
	$(CC) $(flags) -o build/main src/main.cpp

run: build
	time ./build/main < build/problem.txt

debug: src/main.cpp
	$(CC) $(dflags) -o build/debug src/main.cpp

sanity: run
	./build/main < .tests/sanity.in > build/out
	diff build/out .tests/sanity.out

clean:
	rm -f build/*

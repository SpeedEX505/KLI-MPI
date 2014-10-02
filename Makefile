#macros
CC=g++
CCFLAGS=
LBFLAGS=
Remove=rm -rf
Objects=src/objects/main.o src/objects/Graph.o src/objects/Stack.o src/objects/ProblemSolver.o
RUN=./kli
GRAPHFILE=graph.txt
CPATH=src/objects/

     
#generates final binary and documentation
all: $(Objects)
	make compile
     
#build into final binary
compile: $(RUN)
     
clean:
	$(Remove) src/objects $(RUN) $(GRAPHFILE)
     
#rules to make objects ----------------------------------------------------------------------------------
$(RUN): $(Objects)
	$(CC) $(CCFLAGS) $(Objects) -o $(RUN) $(LBFLAGS)
     
src/objects/main.o: src/main.cpp
	mkdir -p src/objects
	./graph
	$(CC) $(CCFLAGS) -c src/main.cpp -o src/objects/main.o $(LBFLAGS)

src/objects/Graph.o: src/Graph.cpp src/Graph.h
	mkdir -p src/objects
	$(CC) $(CCFLAGS) -c src/Graph.cpp -o src/objects/Graph.o $(LBFLAGS)

src/objects/Stack.o: src/Stack.cpp src/Stack.h
	mkdir -p src/objects
	$(CC) $(CCFLAGS) -c src/Stack.cpp -o src/objects/Stack.o $(LBFLAGS)

src/objects/ProblemSolver.o: src/ProblemSolver.cpp src/ProblemSolver.h
	mkdir -p src/objects
	$(CC) $(CCFLAGS) -c src/ProblemSolver.cpp -o src/objects/ProblemSolver.o $(LBFLAGS)


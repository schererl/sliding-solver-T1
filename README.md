# sliding-solver-T1
Sliding Puzzle Solver - AI Advanced course UFRGS 2024/1

Authors:
Leonardo Dorneles 
Victor Scherer

## Compiling
To compile the code with the standard configurations, just make it:  
```
make
```
To use the bucket data structure in the A*
```
make bucket
```
## Running with the instances
The available solvers are `-astar`, `-bfs`, `-gbfs`, `-idastar`, `-idfs`.
To run A* solver with input files, for instance:   
```
./main -astar < 15puzzle_example.txt 
```

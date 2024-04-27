#!/bin/bash
# Running GBFS 10 times
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_1.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_2.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_3.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_4.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_5.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_6.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_7.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_8.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_9.csv
./main -gbfs < 8puzzle_instances.txt > gbfs_8puzzle_10.csv

# Running BFS 10 times
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_1.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_2.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_3.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_4.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_5.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_6.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_7.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_8.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_9.csv
./main -bfs < 8puzzle_instances.txt > bfs_8puzzle_10.csv

# Running A* 10 times
./main -astar < 8puzzle_instances.txt > astar_8puzzle_1.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_2.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_3.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_4.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_5.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_6.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_7.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_8.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_9.csv
./main -astar < 8puzzle_instances.txt > astar_8puzzle_10.csv

# Running IDFS 10 times
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_1.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_2.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_3.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_4.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_5.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_6.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_7.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_8.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_9.csv
./main -idfs < 8puzzle_instances.txt > idfs_8puzzle_10.csv

# Running IDA* 10 times
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_1.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_2.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_3.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_4.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_5.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_6.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_7.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_8.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_9.csv
./main -idastar < 8puzzle_instances.txt > idastar_8puzzle_10.csv

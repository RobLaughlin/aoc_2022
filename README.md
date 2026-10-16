# Advent of Code 2022 — C++

My solutions to all 25 days of [Advent of Code 2022](https://adventofcode.com/2022),
written in C++17. Each day is a small standalone program with its own `Solution`
class, and shared helpers live in `data_structures/`.

## Highlights

| Technique | Days |
|---|---|
| Graph search: lazy Dijkstra, BFS over time-varying states | 12, 24 |
| State-space search with pruning and memoization | 16, 19 |
| Union-find to separate exterior air from trapped pockets | 18 |
| Cycle detection to extrapolate a simulation to 10^12 steps | 17 |
| Interval merging over Manhattan-distance ranges | 15 |
| Recursive parsing and expression trees, solved by inverting operations | 13, 21 |
| Folding a 2D map onto the faces of a cube | 22 |

## Days

| Day | Puzzle | Approach |
|---|---|---|
| 1 | Calorie Counting | Group sums, tracking the top N |
| 2 | Rock Paper Scissors | Outcome lookup tables |
| 3 | Rucksack Reorganization | Set intersection |
| 4 | Camp Cleanup | Interval containment and overlap |
| 5 | Supply Stacks | Stack simulation with regex-parsed moves |
| 6 | Tuning Trouble | Sliding window with a set of distinct characters |
| 7 | No Space Left On Device | Directory tree built from a command log; recursive sizes |
| 8 | Treetop Tree House | Grid scans for visibility and scenic score |
| 9 | Rope Bridge | Rope physics simulation with hashed visited cells |
| 10 | Cathode-Ray Tube | Cycle-accurate CPU simulation driving a CRT grid |
| 11 | Monkey in the Middle | Deque simulation; worry levels kept modulo the product of the divisors |
| 12 | Hill Climbing Algorithm | Lazy Dijkstra with a min priority queue |
| 13 | Distress Signal | Recursive packet comparison over parsed trees; sorting for the decoder key |
| 14 | Regolith Reservoir | Falling-sand simulation on a hashed point set |
| 15 | Beacon Exclusion Zone | Per-row intervals merged into disjoint ranges |
| 16 | Proboscidea Volcanium | Shortest paths between valves, then DFS over time-budgeted routes |
| 17 | Pyroclastic Flow | Falling-rock simulation with cycle detection on the tower surface |
| 18 | Boiling Boulders | Surface-area counting; union-find over air cubes |
| 19 | Not Enough Minerals | BFS over robot-building states with resource and robot-count pruning |
| 20 | Grove Positioning System | Circular mixing with (value, id) pairs to handle duplicates |
| 21 | Monkey Math | Expression tree with memoized DFS; solve for the unknown leaf |
| 22 | Monkey Map | Grid walk with wrap-around; part 2 folds the map into a cube |
| 23 | Unstable Diffusion | Cellular automaton with rotating direction priority |
| 24 | Blizzard Basin | BFS over (position, minute) states |
| 25 | Full of Hot Air | Balanced base-5 (SNAFU) conversion |

## Layout

```text
aoc_2022/
├── 1/ … 25/          # one folder per day: entry point (N.cpp), Solution class, helpers
└── data_structures/  # shared helpers: Grid, TreeNode, UnionFind, hashable pairs/tuples,
                      # and a standalone rope-simulation visualizer
```

## Build and run

Requirements:
- A C++17 compiler (tested with g++ 13).
- Boost headers for days 18, 20, 21, and 23 (`sudo apt install libboost-dev`).

From inside a day's folder:

```bash
cd 12
g++ -std=c++17 -O2 *.cpp -o solution
./solution
```

Each program reads `input.txt` from the current directory and prints the answers to
both parts.

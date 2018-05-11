# CDD Project

WaTor simulation using C++

## Wator Simulation

Part 1: Serial Implementation

Part 2: Concurrent Implementation

Part 3: Benchmarking

Part 4: Optimisations

### Implementation
Project implemented using C++ on Linux using g++ compiler.

Documentation using Doxygen.

Makefile: Debug and release, performs clean up and generates documentation.

### Run

To run:

        make

	./ [executable]

Generate docs:

	make docs

### Benchmarking

## Benchmarking
### Hardware Info
* MacBook Pro 2017 - macOS High Sierra (Ubuntu 16.04 Parallels Desktop)
* Processor 3.1 GHz Intel Core i5
* Memory 16 GB 2133 MHz LPDDR3
* Dual Core

### Serial Test
Grid Size     | 30 x 30       | 60 x 60       | 120 x 120     | 150 x 150
------------- | ------------- | ------------- | ------------- | -------------
Average(ms)   | 0.003939963   | 0.012211743   | 0.035332249   | 0.057491424
Min(ms)       | 0.000639      | 0.000997      | 0.002384      | 0.003092
Max(ms)       | 0.027821      | 0.059312      | 0.209131      | 0.30537
Stdev         | 0.003633349   | 0.011383074   | 0.036173861   | 0.030868732

#### Result
![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/gridsize.png)

### Concurrent Test
Using: 
- 1, 2, 3, 4, 8 threads
- 30x30 grid
- 100x100 grid

#### Result
![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/charts/30x30totalruntime.png)

![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/charts/100x100runtime.png)

![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/charts/loop30.png)

![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/charts/Picture1.png)


## Profiler

Using: GProf

Output: [Analysis](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/analysis.txt)

## Release
Serial Implementation [1.0](https://github.com/Kelly-David/CDD-Wator-Project/releases/tag/1.0)

Concurrent Implementation [1.1](https://github.com/Kelly-David/CDD-Wator-Project/releases/tag/1.1)

## Branch History

### [Master](https://github.com/Kelly-David/CDD-Wator-Project/tree/master)
Working...

### [Serial](https://github.com/Kelly-David/CDD-Wator-Project/tree/serial)
Serial Implementation

### [Concurrent](https://github.com/Kelly-David/CDD-Wator-Project/tree/parallel)
Using OpenMP

### [Testing](https://github.com/Kelly-David/CDD-Wator-Project/tree/testing)
For Benchmarking
* Using OpenMp.
* Outputs run time(ms) to csv file.
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

#### Test
Grid Size     | 30 x 30       | 60 x 60       | 120 x 120     | 150 x 150
------------- | ------------- | ------------- | ------------- | -------------
Average(ms)   | 0.003939963   | 0.012211743   | 0.035332249   | 0.057491424
Min(ms)       | 0.000639      | 0.000997      | 0.002384      | 0.003092
Max(ms)       | 0.027821      | 0.059312      | 0.209131      | 0.30537
Stdev         | 0.003633349   | 0.011383074   | 0.036173861   | 0.030868732

#### Hardware Info
* MacBook Pro 2017 - macOS High Sierra
* Processor 3.1 GHz Intel Core i5
* Memory 16 GB 2133 MHz LPDDR3

#### Result
![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/gridsize.png)

### Release
[1.0]()

### Branch History

#### [Master](https://github.com/Kelly-David/CDD-Wator-Project/tree/master)
Working...

#### [Serial](https://github.com/Kelly-David/CDD-Wator-Project/tree/serial)
Serial Implementation

#### [Parallel](https://github.com/Kelly-David/CDD-Wator-Project/tree/parallel)
Using OpenMP

#### [Testing](https://github.com/Kelly-David/CDD-Wator-Project/tree/testing)
* Using OpenMp.
* Outputs run time(ms) to file.
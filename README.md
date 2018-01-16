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

        cd lab[number]

        make

	./ [executable]

Generate docs:

	cd lab[number]

	doxygen

### Benchmarking

Grid Size
    30 x 30
    60 x 60
    120 x 120
    150 x 150

MacBook Pro 2017 - macOS High Sierra
Processor 3.1 GHz Intel Core i5
Memory 16 GB 2133 MHz LPDDR3

![alt text](https://raw.githubusercontent.com/Kelly-David/CDD-Wator-Project/master/gridsize.png)


### Branch History

#### Master
Serial Implementation

#### Parallel
Using OpenMP

#### Testing
Using OpenMp. Outputs run time to file.
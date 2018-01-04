/*
    Wator Simulation : Sharks and Fish
    Created by: David Kelly, Vaidas Suipienus
    Date: 29/11/2017
*/

/* Includes */
#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

int const _X = 20;      // Ocean width
int const _Y= 20;       // Ocean height
int const LIMIT = 20;   // Must match array bounds, expects ocean to be square
char const WATER = ' '; // Water is blank space
char const FISH = 'o';  // Fish are o
char const SHARK = '$'; // Sharks are $

/**
 * Create 2d arrays representing ocean; breeding time; starving time
 * ocean, breed, starve are for display
 * ...next arrays are for updating animal position and state
 */
char ocean[_X][_Y];
char oceanNext[_X][_Y];
int breed[_X][_Y];
int breedNext[_X][_Y];
int starve[_X][_Y];
int starveNext[_X][_Y];

std::vector<int> neighbours;

int totalFish = 10;
int allFish = totalFish;    // Running count of fish
int totalSharks = 10;
int allSharks = totalSharks;// Running count of sharks

int fishBreedTime = 5;      // Iteration count until fish breed
int sharkBreedTime = 5;     // Iteration count until sharks breed
int sharkStarveTime = 5;    // Iteration count until shark dies

int breedLife = 5;
int starveLife = 5;

int randomXPos, randomYPos = 0;

long int microseconds = 1000000; // Timer variable

/**
 * \brief void populateAllArrays()() :: Initialises 6 arrays:
 * ocean arrays with WATER character
 * breed arrays with 0
 * starve arrays with 0
 */
void populateAllArrays() {
    for (int i = 0; i < _X; ++i) {
        for (int k = 0; k < _Y; ++k) {
            ocean[i][k] = WATER;
            oceanNext[i][k] = WATER;
            breed[i][k] = 0;
            breedNext[i][k] = 0;
            starve[i][k] = 0;
            starveNext[i][k] = 0;
        }
    }
}

/**
 * \brief void populateWithFish() :: Randomly places Fish in the ocean array
 * Sets corresponding breed/starve arrays
 */
void populateWithFish() {
    for (int i = 0; i < totalFish; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = FISH;
        breed[randomXPos][randomYPos] = breedLife;
        starve[randomXPos][randomXPos] = starveLife;
    }
}

/**
 * \brief void populateWithSharkss() :: Randomly places Sharks in the ocean array
 * Sets corresponding breed/starve arrays
 */
void populateWithSharks() {
    for (int i = 0; i < totalSharks; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = SHARK;
        breed[randomXPos][randomYPos] = breedLife;
        starve[randomXPos][randomYPos] = starveLife;
    }
}

/**
 * \brief void create() :: Populates the ocean array with respective characters
 */
void create() {
    populateAllArrays();
    populateWithFish();
    populateWithSharks();
}

/**
 * \brief Copies the contents of ...next arrays to display arrays
 */
void updateOceanContents(
        char toOcean[LIMIT][LIMIT], char fromOcean[LIMIT][LIMIT],
        int toBreed[LIMIT][LIMIT], int fromBreed[LIMIT][LIMIT],
        int toStarve[LIMIT][LIMIT], int fromStarve[LIMIT][LIMIT]) {
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            toOcean[i][k] = fromOcean[i][k];
            toBreed[i][k] = fromBreed[i][k];
            toStarve[i][k] = fromStarve[i][k];
            // Reset ...next arrays
            fromOcean[i][k] = WATER;
            fromBreed[i][k] = 0;
            fromStarve[i][k] = 0;
        }
    }

}
/**
 * \brief Update totals for display
 */
void updateTotals() {
    allSharks = 0;
    allFish = 0;
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            if (ocean[i][k] == FISH) {
                ++allFish;
            }
            if (ocean[i][k] == SHARK) {
                ++allSharks;
            }
        }
    }
}

/**
 * \brief Delete Fish
 */
void deleteFish(int xpos, int ypos) {
    ocean[xpos][ypos] = SHARK;
    starve[xpos][ypos] = 0;
    breed[xpos][ypos] = 0;
}

/**
 * \brief Delete Fish
 */
void deleteShark( int xpos, int ypos) {

}

/**
 * \brief int randomGen(long int limit)::returns a random integer between 1 and limit
 */
int randomGen(long int range) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, range); // define the range

    return distr(eng);
}

/**
 * \brief int getMoveDirection(
 */
int getMoveDirection(char type, int xpos, int ypos) {
    neighbours.clear();

    if (type == SHARK) {
        if(ocean[xpos - 1][ypos] == FISH){
            neighbours.push_back(1);
            breed[xpos][ypos]++; //found a fish increment breed time
        }
        else if(ocean[xpos + 1][ypos] == FISH){
            neighbours.push_back(2);
            breed[xpos][ypos]++; //found a fish increment breed time
        }
        else if(ocean[xpos][ypos + 1] == FISH){
            neighbours.push_back(3);
            breed[xpos][ypos]++; //found a fish increment breed time
        }
        else if(ocean[xpos][ypos -1] == FISH){
            neighbours.push_back(4);
            breed[xpos][ypos]++; //found a fish increment breed time
        }
    }
    if ((type == FISH ) || ((type == SHARK) && (neighbours.size() == 0))) {
        if(type == SHARK) { starve[xpos][ypos]++; } // No neighbouring fish - decrement starve time.

        if(ocean[xpos - 1][ypos] == WATER){
            neighbours.push_back(1);
        }
        if(ocean[xpos + 1][ypos] == WATER){
            neighbours.push_back(2);
        }
        if(ocean[xpos][ypos + 1] == WATER){
            neighbours.push_back(3);
        }
        if(ocean[xpos][ypos -1] == WATER){
            neighbours.push_back(4);
        }
    }
    if(neighbours.size() == 0) {
        return 0;
    }
    else {
        if(type == FISH) { breed[xpos][ypos]++; } //Fish can move increment breed time
        int direction = randomGen(neighbours.size());
        return neighbours[direction];
    }
}

/**
 * \brief Prints the ocean array to screen
 */
void simulate() {
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            if ((ocean[i][k] == FISH) || (ocean[i][k] == SHARK)) {
                int direction = getMoveDirection(ocean[i][k], i, k);
                if (direction == 1) { // North
                    if (ocean[i][k] == FISH) {
                        oceanNext[(i + LIMIT -1) % LIMIT][k] = FISH;
                    }
                    if (ocean[i][k] == SHARK) {
                        oceanNext[(i + LIMIT -1) % LIMIT][k] = SHARK;
                    }
                    starveNext[(i + LIMIT -1) % LIMIT][k] = starve[i][k];
                    breedNext[(i + LIMIT -1) % LIMIT][k] = breed[i][k];

                } else if (direction == 2) { // South
                    if (ocean[i][k] == FISH) {
                        oceanNext[(i + 1) % LIMIT][k] = FISH;
                    }
                    if (ocean[i][k] == SHARK) {
                        oceanNext[(i + 1) % LIMIT][k] = SHARK;
                    }
                    starveNext[(i + 1) % LIMIT][k] = starve[i][k];
                    breedNext[(i + 1) % LIMIT][k] = breed[i][k];

                } else if (direction == 3) { // East
                    if (ocean[i][k] == FISH) {
                        oceanNext[i][(k + 1) % LIMIT] = FISH;
                    }
                    if (ocean[i][k] == SHARK) {
                        oceanNext[i][(k + 1) % LIMIT] = SHARK;
                    }
                    starveNext[i][(k + 1) % LIMIT] = starve[i][k];
                    breedNext[i][(k + 1) % LIMIT] = breed[i][k];

                } else if (direction == 4) { // West
                    if (ocean[i][k] == FISH) {
                        oceanNext[i][(k + LIMIT -1) % LIMIT] = FISH;
                    }
                    if (ocean[i][k] == SHARK) {
                        oceanNext[i][(k + LIMIT -1) % LIMIT] = SHARK;
                    }
                    starveNext[i][(k + LIMIT -1) % LIMIT] = starve[i][k];
                    breedNext[i][(k + LIMIT -1) % LIMIT] = breed[i][k];

                } else if (direction == 0) { // Can't move
                    if (ocean[i][k] == FISH) {
                        oceanNext[i][k] = FISH;
                    }
                    if (ocean[i][k] == SHARK) {
                        oceanNext[i][k] = SHARK;
                    }
                    breedNext[i][k] = breed[i][k];
                    starveNext[i][k] = starve[i][k];
                }
            }
        }
    }
}
/**
 * \brief Prints the ocean array to screen
 */
void print() {
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            std::cout << ocean[i][k];
        }
        std::cout << std::endl;
    }
    // Display the running totals
    std::cout << "Fish[" << allFish << "] Sharks[" << allSharks << "]" << std::endl;
}

/**
 * \brief Main
 */
int main() {

    //Initialize random seed for random number generator
    srand (time(NULL));

    std::cout << "Wator World Simulation" << std::endl;

    // Create the Wator world
    create();

    // Start main loop
    do {
        // Prints the ocean
        print();
        std::cout << "---------------------" << std::endl;
        // Timer
        usleep(microseconds);
        // Simulate
        simulate();
        // Update the arrays
        updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
        // Update Shark and Fish totals
        updateTotals();
    } while ((allSharks > 0) && (allFish > 0)); // Run until all animals are gone

    return 0;
}
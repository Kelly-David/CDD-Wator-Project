/*
    Wator Simulation : Sharks and Fish
    Created by: David Kelly, Vaidas Suipienus
    Date: 29/11/2017


    Description:
    Fish:   move to a non-occupied index.
            breed when breedLife == 0 (spawn a new fish in their place)
    Shark:  move to nearby index occupied by a fish
            if no fish are nearby :
                move to a non-occupied index
                decrement starveLife
            die when starveLife == 0
*/

/* Includes */
#include <iostream>
#include <random>
#include <unistd.h>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <fstream>

int const _X = 30;      // Ocean width
int const _Y= 30;       // Ocean height
int const LIMIT = 30;   // Must match array bounds, expects ocean to be square
char const WATER = ' '; // Water is blank space
char const FISH = '.';  // Fish are o
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
int totalSharks = 50;
int allSharks = totalSharks;// Running count of sharks

int breedLife = 5;
int starveLife = 5;

int randomXPos, randomYPos = 0;

long int microseconds = 100000; // Timer variable

/**
 * \brief void populateAllArrays()() :: Initialises 6 arrays:
 * ocean arrays with WATER character
 * breed arrays with 0
 * starve arrays with 0
 */
void populateAllArrays() {
    #pragma omp parallel for
    for (int i = 0; i < _X; ++i) {
        for (int k = 0; k < _Y; ++k) {
            ocean[i][k] = WATER;
            oceanNext[i][k] = WATER;
            breed[i][k] = breedLife;
            breedNext[i][k] = breedLife;
            starve[i][k] = starveLife;
            starveNext[i][k] = starveLife;
        }
    }
}

/**
 * \brief void populateWithFish() :: Randomly places Fish in the ocean array
 * Sets corresponding breed/starve arrays
 */
void populateWithFish() {
    #pragma omp parallel for
    for (int i = 0; i < totalFish; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = FISH;
        breed[randomXPos][randomYPos] = breedLife;
        starve[randomXPos][randomXPos] = starveLife;
    }
}

/**
 * \brief void populateWithSharks() :: Randomly places Sharks in the ocean array
 * Sets corresponding breed/starve arrays
 */
void populateWithSharks() {
    #pragma omp parallel for
    for (int i = 0; i < totalSharks; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = SHARK;
        breed[randomXPos][randomYPos] = breedLife;
        starve[randomXPos][randomYPos] = starveLife;
    }
}

/**
 * \brief Copies the contents of ...next arrays to display arrays
 */
void updateOceanContents(
        char toOcean[LIMIT][LIMIT], char fromOcean[LIMIT][LIMIT],
        int toBreed[LIMIT][LIMIT], int fromBreed[LIMIT][LIMIT],
        int toStarve[LIMIT][LIMIT], int fromStarve[LIMIT][LIMIT]) {
    #pragma omp parallel for
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            toOcean[i][k] = fromOcean[i][k];
            toBreed[i][k] = fromBreed[i][k];
            toStarve[i][k] = fromStarve[i][k];
        }
    }

}

/**
 * \brief void create() :: Populates the ocean array with respective characters
 */
void create() {
    populateAllArrays();
    populateWithFish();
    populateWithSharks();
    updateOceanContents(oceanNext, ocean, breedNext, breed, starveNext, starve);
}

/**
 * \brief Update totals for display
 */
void updateTotals() {
    allSharks = 0;
    allFish = 0;
    #pragma omp parallel for
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
 * \brief Breed Fish
 */
void breedFish(int xpos, int ypos) {
    // New fish are placed in the pre-move location of parent.
    oceanNext[xpos][ypos] = FISH;
    breedNext[xpos][ypos] = breedLife;
    starveNext[xpos][ypos] = breedLife;
    // ...then parent will move
}

/**
 * \brief Eat Fish
 * Removes the Fish from the oceanNext array at the corresponding position
 */
void eatFish(int xpos, int ypos) {
    oceanNext[xpos][ypos] = WATER;
    breedNext[xpos][ypos] = breedLife;
    starveNext[xpos][ypos] = starveLife;
    ocean[xpos][ypos] = WATER;
    breed[xpos][ypos] = breedLife;
    starve[xpos][ypos] = starveLife;
    // Shark will then be moved into this position - so do we need to remove the fish?
}

/**
 * \brief Kill Shark
 */
void killShark( int xpos, int ypos) {
    oceanNext[xpos][ypos] = WATER;
    breedNext[xpos][ypos] = breedLife;
    starveNext[xpos][ypos] = starveLife;
    ocean[xpos][ypos] = WATER;
    breed[xpos][ypos] = breedLife;
    starve[xpos][ypos] = starveLife;
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

    // Reset the neighbours vector
    neighbours.clear();

    if (type == SHARK) {
        if(oceanNext[xpos][(ypos + LIMIT - 1) % LIMIT] == FISH) {
            // Fish is North
            neighbours.push_back(1);
            // Remove the fish
            eatFish(xpos, (ypos + LIMIT - 1) % LIMIT);
            // return 1;
        }
        else if (oceanNext[xpos][(ypos + 1) % LIMIT] == FISH){
            // Fish is South
            neighbours.push_back(2);
            eatFish(xpos, (ypos + 1) % LIMIT);
            // return 2;
        }
        else if (oceanNext[(xpos + 1) % LIMIT][ypos] == FISH){
            //Fish is East
            neighbours.push_back(3);
            eatFish((xpos + 1) % LIMIT, ypos);
            // return 3;
        }
        else if (oceanNext[(xpos + LIMIT - 1) % LIMIT][ypos] == FISH){
            // Fish is West
            neighbours.push_back(4);
            eatFish((xpos + LIMIT - 1) % LIMIT, ypos);
            // return 4;
        }
    }
    // If it's a FISH or ( a SHARK and the neighbours is still empty )
    if ((type == FISH ) || ((type == SHARK) && (neighbours.empty()))) {
        // If it's a SHARK it hasn't found a fish so starve it...
        if (type == SHARK) { ocean[xpos][ypos]--; }

        if (oceanNext[xpos][(ypos + LIMIT - 1) % LIMIT] == WATER){
            // North
            neighbours.push_back(1);
        }
        if (oceanNext[xpos][(ypos + 1) % LIMIT] == WATER){
            // South
            neighbours.push_back(2);
        }
        if (oceanNext[(xpos + 1) % LIMIT][xpos] == WATER){
            // East
            neighbours.push_back(3);
        }
        if (oceanNext[(xpos + LIMIT - 1) % LIMIT][ypos] == WATER){
            //West
            neighbours.push_back(4);
        }
    }
    if (neighbours.empty()) {
        // Animal cannot move
        return 0;
    }
    else {
        // Select a random direction
        int direction = randomGen(neighbours.size());
        return neighbours[direction];
    }
}

/**
 * \brief Moves the Fish or Sharks to their new location
 * Moves the contents of array at xpos and ypos to the index of array ...next at xMove yMove
 */
void move(char animal, int xpos, int ypos, int xMove, int yMove) {

    oceanNext[xMove][yMove] = animal;
    breedNext[xMove][yMove] = breed[xpos][ypos];
    starveNext[xMove][yMove] = starve[xpos][ypos];
    oceanNext[xpos][ypos] = WATER;
    breedNext[xpos][ypos] = breedLife;
    starveNext[xpos][ypos] = starveLife;
}

/**
 * \brief Prints the ocean array to screen
 */
void simulate() {
    int moveDirection = 0;
    bool canBreed = false;
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            // If it's a FISH...
            if ((ocean[i][k] == FISH)) {
                // Find the move direction. Will be 0-4
                moveDirection = getMoveDirection(FISH, i, k);

                if (moveDirection != 0) {
                    //Fish can move - decrement breed time
                    breed[i][k]--;
                    if (breed[i][k] == 0) {
                        // Fish can breed...
                        // Make a new fish in the current fish location in both ocean arrays
                        canBreed = true;
                    }
                }
                if (moveDirection == 1) { // North: decrease Y

                    move(FISH, i, k, i, (k + LIMIT - 1) % LIMIT);

                } else if (moveDirection == 2) { // South: Increase Y

                    move(FISH, i, k, i, (k + 1) % LIMIT);

                } else if (moveDirection == 3) { // East: Increase X

                    move(FISH, i, k, (i + 1) % LIMIT, k);

                } else if (moveDirection == 4) { // West: Decrease X

                    move(FISH, i, k, (i + LIMIT - 1) % LIMIT, k);
                }
                if (canBreed) { breedFish(i,k); }
            }
            // If its a SHARK...
            else if ((ocean[i][k] == SHARK)) {
                moveDirection = getMoveDirection(SHARK, i, k);

                if (moveDirection != 0) {
                    // Shark can move - decrement breed time
                    breed[i][k]--;
                    if (breed[i][k] == 0) {
                        // Shark can breed - are sharks allowed to breed?
                    }
                }

                if (starve[i][k] == 0) {
                    killShark(i, k);

                } else if (moveDirection == 1) { // North: decrease Y

                    oceanNext[i][(k + LIMIT - 1) % LIMIT] = SHARK;
                    starveNext[i][(k + LIMIT - 1) % LIMIT] = starve[i][k];
                    breedNext[i][(k + LIMIT - 1) % LIMIT] = breed[i][k];
                    // Clear the current position and associated breed & starve times
                    oceanNext[i][k] = WATER;
                    breedNext[i][k] = breedLife;
                    starveNext[i][k] = starveLife;

                } else if (moveDirection == 2) { // South: Increase Y

                    oceanNext[i][(k + 1) % LIMIT] = SHARK;
                    starveNext[i][(k + 1) % LIMIT] = starve[i][k];
                    breedNext[i][(k + 1) % LIMIT] = breed[i][k];
                    // Clear the current position and associated breed & starve times
                    oceanNext[i][k] = WATER;
                    breedNext[i][k] = breedLife;
                    starveNext[i][k] = starveLife;

                } else if (moveDirection == 3) { // East: Increase X

                    oceanNext[(i + 1) % LIMIT][k] = SHARK;
                    starveNext[(k + 1) % LIMIT][k] = starve[i][k];
                    breedNext[(k + 1) % LIMIT][k] = breed[i][k];
                    // Clear the current position and associated breed & starve times
                    oceanNext[i][k] = WATER;
                    breedNext[i][k] = breedLife;
                    starveNext[i][k] = starveLife;

                } else if (moveDirection == 4) { // West: Decrease X

                    oceanNext[(i + LIMIT - 1) % LIMIT][k] = SHARK;
                    starveNext[(i + LIMIT - 1) % LIMIT][k] = starve[i][k];
                    breedNext[(i + LIMIT - 1) % LIMIT][k] = breed[i][k];
                    // Clear the current position and associated breed & starve times
                    oceanNext[i][k] = WATER;
                    breedNext[i][k] = breedLife;
                    starveNext[i][k] = starveLife;
                }

            }
        }
    }
    updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
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

    // Set the number of threads OMP will use
    omp_set_num_threads(8);

    std::ofstream output;
    output.open ("4threads.csv");

    // Testing loop
    for (int i = 0; i < 3; ++i ){


        // Start timer:
        std::clock_t start;
        double duration;

        start = std::clock();

        //Initialize random seed for random number generator
        srand (time(NULL));

        std::cout << "Wator World Simulation" << std::endl;

        // Create the Wator world
        create();

        // Start main loop
        do {
            // Prints the ocean
            print();
            std::cout << "--------------------------------------------------------------" << std::endl;
            // Timer
            usleep(microseconds);
            // Simulate
            simulate();
            // Update the arrays
            updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
            // Update Shark and Fish totals
            updateTotals();
        } while ((allSharks > 0) && (allFish > 0)); // Run until all animals are gone

        // Get time difference
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        // Write to file
        output << duration << ",\n";
    }

    output.close();

    return 0;
}
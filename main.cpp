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

int const _X = 20;
int const _Y= 20;
int const LIMIT = 20; // Must match array bounds
char const WATER = '_';
char const FISH = 'o';
char const SHARK = '$';

// Create 2d array representing ocean; breeding time; starving time
char ocean[_X][_Y];
char oceanNext[_X][_Y];
int breed[_X][_Y];
int starve[_X][_Y];

std::vector<int> neighbours;

int totalFish = 300;
int allFish = totalFish;
int totalSharks = 5;
int allSharks = totalSharks;

int fishBreedTime = 5;
int sharkBreedTime = 5;
int sharkStarveTime = 5;

int randomXPos, randomYPos = 0;

long int microseconds = 500000;

/**
 * \brief void makeOcean() :: Fills each element of the ocean array with char: underscore
 */
void makeOcean() {
    for (int i = 0; i < _X; ++i) {
        for (int k = 0; k < _Y; ++k) {
            ocean[i][k] = WATER;
            oceanNext[i][k] = WATER;
            breed[i][k] = 0;
            starve[i][k] = 0;
        }
    }
}

/**
 * \brief void makeFish() :: Fills each element of the ocean array with char: lowercase
 */
void makeFish() {
    for (int i = 0; i < totalFish; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = FISH;
        breed[randomXPos][randomYPos] = fishBreedTime;
    }
}

/**
 * \brief void makeSharks() :: Fills each element of the ocean array with char: dollar
 */
void makeShark() {
    for (int i = 0; i < totalSharks; ++i) {
        randomXPos = (int) random() % LIMIT;
        randomYPos = (int) random() % LIMIT;
        ocean[randomXPos][randomYPos] = SHARK;
        breed[randomXPos][randomYPos] = sharkBreedTime;
        starve[randomXPos][randomYPos] = sharkStarveTime;
    }
}

/**
 * \brief void create() :: Populates the ocean array with respective characters
 */
void create() {
    makeOcean();
    makeFish();
    makeShark();
}

/**
 * \brief Update totals
 */
void copyOcean(char to[LIMIT][LIMIT], char from[LIMIT][LIMIT]) {
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            to[i][k] = from[i][k];
            oceanNext[i][k] = WATER;
        }
    }

}
/**
 * \brief Update totals
 */
void updateAnimals() {
    allSharks = 0;
    allFish = 0;
    for (int i = 0; i < _X; ++i) {
        for (int k = 0; k < _Y; ++k) {
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
 * \brief int direction() : returns integer between 1 - 4 = 1:Left | 2:Up | 3:Right | 4:Down
 */
int randomGen(long int limit) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, limit); // define the range

    return distr(eng);
}

int getMoveDirection(char type, int xpos, int ypos) {
    neighbours.clear();

    if (type == SHARK) {
        if(ocean[xpos - 1][ypos] == FISH){
            neighbours.push_back(1);
            return 1;
        }
        if(ocean[xpos + 1][ypos] == FISH){
            neighbours.push_back(2);
            return 2;

        }
        if(ocean[xpos][ypos + 1] == FISH){
            neighbours.push_back(3);
            return 3;

        }
        if(ocean[xpos][ypos -1] == FISH){
            neighbours.push_back(4);
            return 4;
        }
    } else if ((type == FISH ) || ((type == SHARK) && (neighbours.size() == 0))) {
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
        //std::cout << neighbours.size();
        //int direction = (int) random() % neighbours.size() ;
        int direction = randomGen(neighbours.size());
        return neighbours[direction];
    }
}

/**
 * \brief Prints the ocean array to screen
 */
void move() {
    for (int i = 0; i < LIMIT; ++i) {
        for (int k = 0; k < LIMIT; ++k) {
            if ((ocean[i][k] == FISH) || (ocean[i][k] == SHARK)) {
                int direction = getMoveDirection(ocean[i][k], i, k);
                if (direction == 1) {
                    if (ocean[i][k] == FISH) { oceanNext[(i % LIMIT) - 1][k] = FISH; }
                    if (ocean[i][k] == SHARK) { oceanNext[(i % LIMIT) - 1][k] = SHARK; }
                } else if (direction == 2) {
                    if (ocean[i][k] == FISH) { oceanNext[(i + 1) % LIMIT][k] = FISH; }
                    if (ocean[i][k] == SHARK) { oceanNext[(i + 1) % LIMIT][k] = SHARK; }
                } else if (direction == 3) {
                    if (ocean[i][k] == FISH) { oceanNext[i][(k + 1) % LIMIT] = FISH; }
                    if (ocean[i][k] == SHARK) { oceanNext[(i % LIMIT) - 1][k] = SHARK; }
                } else if (direction == 4) {
                    if (ocean[i][k] == FISH) { oceanNext[i][(k % LIMIT) - 1] = FISH; }
                    if (ocean[i][k] == SHARK) { oceanNext[i][(k % LIMIT) - 1] = SHARK; }
                } else if (direction == 0) {
                    if (ocean[i][k] == FISH) { oceanNext[i][k] = FISH; }
                    if (ocean[i][k] == SHARK) { oceanNext[i][k] = SHARK; }
                }
            }
        }
    }
}
/**
 * \brief Prints the ocean array to screen
 */
void print() {
    for (int i = 0; i < _X; ++i) {
        for (int k = 0; k < _Y; ++k) {
            std::cout << ocean[i][k];
        }
        std::cout << std::endl;
    }
    std::cout << "Fish[" << allFish << "] Sharks[" << allSharks << "]" << std::endl;
}

/**
 * \brief Main
 */
int main() {
    /* initialize random seed: */
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    create();
    do {
        print();
        std::cout << "---------------------" << std::endl;
        usleep(microseconds);
        move();
        copyOcean(ocean, oceanNext);
        updateAnimals();
    } while ((allSharks > 0) && (allFish > 0));

    return 0;
}
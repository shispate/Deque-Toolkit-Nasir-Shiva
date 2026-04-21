#include "deque.h"

// constructor
Deque::Deque() {
    mapSize = 4;
    blockmap = new int*[mapSize];
    for (int i = 0; i < mapSize; i++)
        blockmap[i] = nullptr;

    // starts in the middle of the blockmap
    first_block = mapSize / 2;
    last_block  = mapSize / 2;

    // allocates the starting block
    blockmap[first_block] = new int[blockSize];

    // starts in the middle of the block
    first_element = blockSize / 2;
    last_element  = blockSize / 2 - 1;

    numElements = 0;
}

// destructor
Deque::~Deque() {
    for (int i = 0; i < mapSize; i++) {
        if (blockmap[i] != nullptr)
            delete[] blockmap[i]; // block
    }
    delete[] blockmap; // the whole blockmap
}

// size
int Deque::size() {
    return numElements;
}

// empty
bool Deque::empty() {
    return numElements == 0;
}

// this "grows" aka resizing the blockmap from the front when it runs out of room
void Deque::growFront() {
    int newMapSize = mapSize * 2;
    int** newMap = new int*[newMapSize];

    for (int i = 0; i < newMapSize; i++)
        newMap[i] = nullptr;

    // offsets and puts the old points into the middle of the map
    int offset = newMapSize / 2 - mapSize / 2;

    for (int i = 0; i < mapSize; i++)
        newMap[i + offset] = blockmap[i];

    first_block += offset;
    last_block  += offset;

    delete[] blockmap;
    blockmap = newMap;
    mapSize = newMapSize;
}

// this "grows" aka resizing the blockmap from the back when it runs out of room
void Deque::growBack() {
    int newMapSize = mapSize * 2;
    int** newMap = new int*[newMapSize];

    for (int i = 0; i < newMapSize; i++)
        newMap[i] = nullptr;

    // copies the old pointers and puts them in front of the map
    for (int i = 0; i < mapSize; i++)
        newMap[i] = blockmap[i];

    delete[] blockmap;
    blockmap = newMap;
    mapSize = newMapSize;
}
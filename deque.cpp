#include "deque.h"

// constructor
Deque::Deque()
{
  mapSize = 4;
  blockmap = new int *[mapSize];
  for (int i = 0; i < mapSize; i++)
    blockmap[i] = nullptr;

  // starts in the middle of the blockmap
  first_block = mapSize / 2;
  last_block = mapSize / 2;

  // allocates the starting block
  blockmap[first_block] = new int[blockSize];

  // starts in the middle of the block
  first_element = blockSize / 2;
  last_element = blockSize / 2 - 1;

  numElements = 0;
}

// destructor
Deque::~Deque()
{
  for (int i = 0; i < mapSize; i++)
  {
    if (blockmap[i] != nullptr)
      delete[] blockmap[i]; // block
  }
  delete[] blockmap; // the whole blockmap
}

// size
int Deque::size()
{
  return numElements;
}

// empty
bool Deque::empty()
{
  return numElements == 0;
}

// this "grows" aka resizing the blockmap from the front when it runs out of room
void Deque::growFront()
{
  int newMapSize = mapSize * 2;
  int **newMap = new int *[newMapSize];

  for (int i = 0; i < newMapSize; i++)
    newMap[i] = nullptr;

  // offsets and puts the old points into the middle of the map
  int offset = newMapSize / 2 - mapSize / 2;

  for (int i = 0; i < mapSize; i++)
    newMap[i + offset] = blockmap[i];

  first_block += offset;
  last_block += offset;

  delete[] blockmap;
  blockmap = newMap;
  mapSize = newMapSize;
}

// this "grows" aka resizing the blockmap from the back when it runs out of room
void Deque::growBack()
{
  int newMapSize = mapSize * 2;
  int **newMap = new int *[newMapSize];

  for (int i = 0; i < newMapSize; i++)
    newMap[i] = nullptr;

  // copies the old pointers and puts them in front of the map
  for (int i = 0; i < mapSize; i++)
    newMap[i] = blockmap[i];

  delete[] blockmap;
  blockmap = newMap;
  mapSize = newMapSize;
}

void Deque::push_back(int element)
{
  last_element++; // move the last marker forward by one slot, new value goes here

  if (last_element >= blockSize) // if last_element has gone past the end of the current block (index 0-4)
                                 // so if we're outside the blockSize it triggers
  {
    last_block++; // and so if the block is full we move to the next block

    if (last_block >= mapSize) // if we've run out of block slots in the blockmap
      growBack();              // double the blockmap size which is this function growBack()

    if (blockmap[last_block] == nullptr)         // if the new block hasn't been allocated yet
      blockmap[last_block] = new int[blockSize]; // allocate a fresh block
                                                 // because last_block++ doesn't actually
                                                 // create a new block it just moves the
                                                 // pointer to the next slot in the blockmap

    last_element = 0; // reset to the beginning of the new block
  }

  blockmap[last_block][last_element] = element; // store the value at the correct block and slot
  numElements++;                                // increment the element counter cuz we added that new element with push_back
}

void Deque::push_front(int element)
{
  // instead of moving forward we are going the first marker backward by one slot, new value goes here
  first_element--;

  if (first_element < 0)
  { // if the first element has gone past the front of the current block
    first_block--;

    if (first_block < 0)
    {              // if we've run out of room in the front
      growFront(); // double the map size from the front
    }

    if (blockmap[first_block] == nullptr)
    {                                             // if the new block hasn't been allocated just like push_back
      blockmap[first_block] = new int[blockSize]; // create a new block
    }
    first_element = blockSize - 1; // make the first_element = to the last slot in the blocksize
  }

  blockmap[first_block][first_element] = element; // store the value
  numElements++;                                  // increment the element counter
}

void Deque::pop_back()
{
  // first check if the block is empty
  if (empty())
  {
    return;
  }

  last_element--; // update the last_element in place

  if (last_element < 0)
  {
    delete[] blockmap[last_block];
    blockmap[last_block] = nullptr;
    last_block--;
    last_element = blockSize - 1; // last slot index of the new block
  }

  numElements--; // since we're removing an element
}

void Deque::pop_front()
{
  if (empty())
  {
    return;
  }

  first_element++; // update the first_element

  // check if it went past the end of the block
  if (first_element >= blockSize)
  {
    delete[] blockmap[first_block];
    blockmap[first_block] = nullptr;
    first_block++;     // move to the next block
    first_element = 0; // reset to the beginning of that block which is data[0]
  }

  numElements--;
}

// return the front block and element
int Deque::front()
{
  return blockmap[first_block][first_element];
}

// return the back block and element
int Deque::back()
{
  return blockmap[last_block][last_element];
}

int &Deque::operator[](unsigned int index)
{
  // similar to finding a seat in a movie theater
  //  you know which row to start in first_block and the seat first_element
  //  just count forward
  int actual = first_element + index;

  // once you know how many seats forward you need to go
  // find the row that puts you in
  // dividing by blockSize tells you how many rows to jump forward
  int block = first_block + (actual / blockSize);

  // now you know the row, but you need to know exactly which seat within that row
  // the remainder gives you how far into the row you land
  int slot = actual % blockSize;

  // return a reference to the exact seat so you can read and write to it
  return blockmap[block][slot];
}
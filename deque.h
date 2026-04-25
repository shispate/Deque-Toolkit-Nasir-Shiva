#ifndef DEQUE_H
#define DEQUE_H

class Deque{

 private:
  int** blockmap; // array of pointers, each are pointing to a fixed block of elements
  int first_element; //a slot within the first block and is the first element
  int last_element; // a slot within the last block and is the last element
  int first_block; // the first block within the blockmap, this holds the first element
  int last_block; // the last block within the blockmap, this holds the last element
  int capacity; // total number of block slots available in blockmap
  int mapSize; // current number of blocks in use
  int numElements;  // total elements stored
  const static int blockSize = 5; // fixed number of slots in each block
  void growFront(); // used for when blockmap runs out of room
  void growBack();  // and needs to be resized

 public:
 /**
  * @brief Construct a new Deque object
  * 
  */
  Deque();

  /**
   * @brief Destroy the Deque object
   * 
   */
  ~Deque();

  /**
   * @brief returns how many elements are currently in the deque
   * 
   * @return int 
   */
  int size();

  /**
   * @brief adds an element to the back of the deque
   * 
   * @param element is the value to add
   */
  void push_back(int element);

  /**
   * @brief adds an element to the front of the deque 
   * 
   * @param element is the value to add
   */
  void push_front(int element);

  /**
   * @brief removes an element from the back of the deque
   * 
   */
  void pop_back();

  /**
   * @brief removes the element from the front of the deque
   * 
   */
  void pop_front();

  /**
   * @brief returns the element at the front of the deque without removing it
   * 
   * @return int 
   */
  int front();

  /**
   * @brief returns the element at the back of the deque without removing it
   * 
   * @return int 
   */
  int back();

  /**
   * @brief checks if the deque is empty
   * 
   * @return true 
   * @return false 
   */
  bool empty();

  /**
   * @brief Accesses an element by its index which the index would be 0 at the front. 
   *  uses block and slot to determine the exact memory location 
   * @param index is the logical positon from the front of the deque
   * @return int& reference to the element at that position
   */
  int& operator[] (unsigned int index);
  



};

#endif

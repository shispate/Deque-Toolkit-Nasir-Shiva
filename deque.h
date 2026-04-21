#ifndef DEQUE_H
#define DEQUE_H

class Deque{

 private:
  int** blockmap;
  int first_element;
  int last_element;
  int first_block;
  int last_block;
  int capacity;
  int mapSize;
  int numElements;  // total elements stored
  const static int blockSize = 5;
  void growFront(); // used for when blockmap runs out of room
  void growBack();  // and needs to be resized

 public:
  Deque();

  ~Deque();

  int size();

  void push_back(int element);

  void push_front(int element);

  void pop_back();

  void pop_front();

  int front();

  int back();

  bool empty();

  int& operator[] (unsigned int index);
  



};

#endif

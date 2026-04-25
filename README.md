# Deque-Toolkit
### Authors: Shiva and Nasir

## Description
This is a block-based deque data structure that allows you to add and remove elements from the front and back efficiently O(1). The deque uses a blockmap which is an array of pointers where each pointer points to a fixed block size of elements. The goal in doing this is to prevent it from being similar to a vector and to keep the add and remove functions to an O(1) time complexity. The deque automatically grows the blockmap when it runs out of room in either direction.

## Compile
Compile the program by entering 'make' command in linux-based systems

## How to run
Run the program by entering the ./deque_toolkit command in linux-based systems

## How it works
The deque stores elements and are tracked by four pointers
1. first_block()
2. first_element()
3. last_block()
4. last_element()

When a block fills up, a new one is allocated. When the blockmap fills up, it then doubles in size using 
- growFront()
- growBack()

## Operations Used
- **push_back(element)**
- **push_front(element)**
- **pop_back()**
- **pop_front()**
- **front()**
- **back()**
- **size()**
- **empty()**
- **operator[]** 

## Testing
- Basic tests: verifies push_back(), push_front(), pop_back(), pop_front(), front(), back(), and size() works with a small set of values.
- Empty Deque tests: comfirms that pop_back() and pop_front() on an empty deque does not crash the program.
- operator[] tests: pushes 20 elements and verifies every index returns the correct value.
- Push back stress tests: pushes 5000 elements to the back and verifies every index, then drains from the front to ensure that it is empty.
- Push front stress tests: does the same as back but instead drains from the back.
- Refill test: drains the deque then refills it with push_front and verifies the order
- Mixed push and pop: alternates the push_back and push_front to verify that it works while alternating functions, then drains both ends alternatively until it is empty.

## Files included
- main.cpp
- deque.cpp
- deque.h
- Makefile
- README.md
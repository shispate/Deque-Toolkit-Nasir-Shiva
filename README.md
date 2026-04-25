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

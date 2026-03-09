# Monopoly Board Simulator

## Overview
This project implements a Monopoly-style board using a circular linked list in C++. The circular linked list serves as a function for both traversal and gameplay

This program emphasizes: 
- Circular linked list operations
- Pointer-based traversal under constraints
- Node modification (insertion and deletion)
- Size enforcement (MAX_SPACES = 40)
- Edge case handling

## Data Structures Used: 
1. MonopolySpace (class)
Represents a board space
- propertyName (string)
- propertyColor (string)
- value (int)
- rent (int)

2. Node<T> (template class)
- Generic node that contains data and a reference pointer to the next node

3. CircularLinkedList<T> (template class)
Used to implement the board as a circular linked list
- headNode = first node
- tailNode = last node
- playerNode = current node
- nodeCount = tracks the number of nodes
- passGOCount = tracks the number of times GO is passed

## Functions:

### Core Requirements
- addSpace(T value)
Adds a space after checking that nodeCount is not MAX_SPACES. Returns false if the board is full.

- addMany(vector<T> values)
Adds all spaces to the board sequentially until MAX_SPACES is reached. Returns the number of spaces successfully added.

- movePlayer(int steps)
Safely moves playerNode forward step times, incrementing passGOCount when passing GO space.
  
- printFromPlayer(int count)
Prints 'count' spaces starting from playerNode.

- printBoardOnce()
Traverses the entire board and prints each node once.

### Advanced A Requirements
- removeByName(string name)
Deletes a node by name, returns true if deleted or false otherwise.
Enforces edge cases and maintains circular link.
Decrements nodeCount when a node is deleted.

- findByColor(string color)
Returns a vector<string> of all space names that match 'color'.

### Additional Function
- clear()
Safely deletes all nodes.

## Build and Run Instructions

### Build
- `g++ -std=c++17 monopoly_board_S26_template.cpp -o monopoly_board`

### Run
- `./monopoly_board'

## Player Traveraal Logic
- The player's current position is 'PlayerNode'.
- Each dice roll (2-12) moves the player forward node-by-node.
- Traversal is fully pointer-based.
- When 'playerNode' moves from the tail to the head, 'passGoCount' is incremented.



  

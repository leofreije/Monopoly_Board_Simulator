# Developer Log (DEVLOG.md)
## Monopoly Board Simulator (Spring 2026)

Minimum **6 entries** required.

Each entry must document learning and reasoning. Fabricated bugs are not expected.

---

## Allowed Entry Types
Each entry may be one of the following:

1) **Bug Fix Entry**
- The issue encountered.
- Error messages or symptoms.
- Attempts made.
- Final resolution.

2) **Edge Case / Testing Entry**
- A failure discovered through testing.
- The specific input/state that caused it.
- The change you made to handle it correctly.

3) **Engineering Decision Entry (up to 2 allowed)**
- A design decision you made.
- An alternative approach you considered.
- Why you chose one approach over another (tradeoffs).

---

### Entry 1
**Date:** 2026-02-28

**Entry Type:** Bug Fix

**Task worked on:** MonopolySpace(string propertyName, string propertyColor, int value, int rent)

**Issue or decision:** I realized that I had copy and pasted 'propertyName' as a placeholder which I meant to update later to the correct variables.

**Error message / symptom (if applicable):**  The overloaded constructor did not work.

**What I tried:** I initially tried to save time by copying and pasting the same line 'this->propertyName = propertyName;' but did not update each one to the correct logic.

**Fix / resolution (or final decision):** I changed the three cases of the incorrect use of 'this->propertyName' to include the correct variables (propertyColor, value, rent).

**Commit(s):** -Fixed constructor values (a225b19), -Created the base monopoly board template (db059ba)

---

### Entry 2
**Date:** 2026-03-04

**Entry Type:** Engineering Decision

**Task worked on:** clear()

**Issue or decision:** I needed to determine how to safely delete all nodes in circular linked list without an infinite loop.

**Error message / symptom (if applicable):** NA

**What I tried:** I initially considered using traversal through the circular linked list using a do-while loop, but I realized that was unnecessary and deemed it overly complicated.

**Fix / resolution (or final decision):** I decided to break the circular structure of the linked list using 'tailNode->nextNode = nullptr', turning it into a singly linked list rather than a circular linked list. This prevented infinite looping and made the logic simple.

**Commit(s):** Destructor Commit (c8b9105)

---

### Entry 3
**Date:** 2026-03-06  

**Entry Type:** Engineering Decision  

**Task worked on:** Creating the board

**Issue or decision:** I needed to choose between reading/writing from a file or manually hardcoding spaces.

**Error message / symptom (if applicable):**  

**What I tried:** I initially experimented with reading spaces from a file, but realized that it add unneeded complexity and hardcoding the spaces was more simple.

**Fix / resolution (or final decision):** I manually hardcoded 40 spaces in a vector and inserted them using addMany(). This made the logic simple and saved time because of my inexperience with reading a file in C++.

**Commit(s):** Board Commit (de74ced)

---

### Entry 4
**Date:** 2026-03-07  

**Entry Type:** Edge Case  

**Task worked on:** findByColor(string color)

**Issue or decision:** 
I initially did not check for the edge case that the board is empty when trying to traverse the circular linked list.

**Error message / symptom (if applicable):**  The program crashed when attempting to access 'temp->data' while 'temp' was nullptr.

**What I tried:** I tested findByColor with an empty board and found that the traversal attempted to start at headNode without checking it exists.

**Fix / resolution (or final decision):**  I added an if statement that checks if the headNode is nullptr and returns empty matches if the board contains no nodes.

**Commit(s):** Advanced A findByColor() Commit (69d2609)

---

### Entry 5
**Date:** 2026-03-08  

**Entry Type:** Bug Fix  

**Task worked on:**  printBoardOnce()

**Issue or decision:**  The board was not being printed at all.

**Error message / symptom (if applicable):**  The while loop never executed because nothing was printed.

**What I tried:**  I tried to set the 'temp' node used for traversal to 'headNode', but in the while loop condition I checked for 'tempNode != headNode'.

**Fix / resolution (or final decision):**  I created a do while loop that allows the first case of 'Node<T> *temp = headNode' to run before the condition is checked.

**Commit(s):** printBoardOnce() Commit (3497f6c)

---

### Entry 6
**Date:** 2026-03-08

**Entry Type:** Bug Fix 

**Task worked on:** removeByName(string name)

**Issue or decision:**  Deleting the only node in the circular linked list did not update playerNode.

**Error message / symptom (if applicable):** Invalid pointer access caused by the program trying access a node when the list was empty.

**What I tried:** I reviewed the logic that updated playerNode during deletion and realized that my assignment statement was wrong.

**Fix / resolution (or final decision):** I changed 'playerNode == nullptr' to 'playerNode = nullptr'

**Commit(s):** Advanced A removeByName(string name) Commit (c7e9f75)

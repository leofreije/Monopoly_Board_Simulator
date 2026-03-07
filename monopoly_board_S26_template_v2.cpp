#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        // TODO: define default constructor (recommended)
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        /* TODO: Define overloaded constructor here */
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    bool isEqual(MonopolySpace other) {
        /* TODO: Define isEqual here (compare by name is fine if you enforce uniqueness) */
        return this->propertyName == other.propertyName;;
    }

    void print() {
        /* TODO: Define print here */
        cout << "Name: " << propertyName << ", Color: " << propertyColor << ", Value: $" << value << ", Rent: " << rent;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) {
        // TODO:
        // - If nodeCount == MAX_SPACES return false (do not corrupt list)
        // - Create new node
        // - If empty list: head=tail=player=new, new->next=head
        // - Else: tail->next=new, tail=new, tail->next=head
        // - nodeCount++

        if (nodeCount == MAX_SPACES) {
            return false;
        }

        Node<T> *newNode = new Node<T>(value);

        if (headNode == nullptr) {
            headNode = tailNode = newNode;
            newNode->nextNode = headNode;
            playerNode = headNode;
        }
        else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
        }

        nodeCount++;
        return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        // TODO:
        // - Add sequentially until full
        // - Stop exactly when you reach MAX_SPACES
        // - Return number successfully added
        // - Do not corrupt pointers if capacity is exceeded
        int ctr = 0;

        for (int i = 0; i < values.size(); i++) {
            if (!addSpace(values[i])) {
                break;
            }

            ctr++;
        }

        //cout << "addMany " << ctr << endl;
        return ctr;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Move playerNode forward 'steps' times, node-by-node
        // - Wrap naturally because list is circular
        // - Detect and track passing GO:
        //   increment passGoCount when a move crosses from tail back to head
        // - Must handle empty list safely

        if (headNode == nullptr) {
            cout << "Error, board is empty" << endl;
            return;
        }

        for (int i = 0; i < steps; i++) {
            if (playerNode == tailNode) {
                playerNode = playerNode->nextNode;
                passGoCount++;
            }
            else {
                playerNode = playerNode->nextNode;
            }
        }
    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Print exactly 'count' nodes starting from playerNode
        // - Must not infinite loop
        // - Must handle empty list
        // - Output must be deterministic and readable
        if (headNode == nullptr || count <= 0) {
            cout << "Error, board is empty or count is too small" << endl;
            return;
        }

        Node<T> *temp = playerNode;
        for (int i = 0; i < count; i++) {
            cout << temp->data.propertyName << ", " << temp->data.propertyColor << ", " << temp->data.value << ", " << temp->data.rent << endl;
            temp = temp->nextNode;
        }
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        // TODO:
        // - Traverse exactly one full cycle and print each node
        cout << "printBoardOnce unwritten" << endl;
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--
        cout << "removeByName unwritten" << endl;
        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches
        cout << "findByColor unwritten" << endl;
        vector<string> matches;
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    // void mirrorBoard() {
    //     // TODO:
    //     // - Reverse the direction of the circular list by reversing next pointers
    //     // - Preserve circular structure
    //     // - Correctly handle empty list and single-node list
    //     // - Player cursor must remain on the same logical space after reversal
    //     cout << "mirrorBoard unwritten" << endl;
    // }
    //
    // // -------------------------------
    // // Edge-case helper: countSpaces O(n)
    // // -------------------------------
    // int countSpaces() {
    //     // TODO:
    //     // - Must be O(n), traverse exactly once with correct stop condition
    //     // - Do NOT rely on nodeCount for this method
    //     cout << "countSpaces unwritten" << endl;
    //     return 0;
    // }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        if (tailNode != nullptr) {
            tailNode->nextNode = nullptr;
        }

        Node<T> *temp = headNode;

        while (headNode != nullptr) {
            headNode = headNode->nextNode;
            delete temp;
            temp = headNode;
        }

        headNode = nullptr;
        tailNode = nullptr;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.

    //Board creation
    vector<MonopolySpace> spaces;
    spaces.push_back(MonopolySpace("GO","Gray",0,0));

    spaces.push_back(MonopolySpace("Mediterranean Avenue","Brown",60,2));
    spaces.push_back(MonopolySpace("Baltic Avenue","Brown",60,4));
    spaces.push_back(MonopolySpace("Beacon Street", "Brown", 80, 6));

    spaces.push_back(MonopolySpace("Reading Railroad","Railroad",200,25));

    spaces.push_back(MonopolySpace("Oriental Avenue","Light Blue",100,6));
    spaces.push_back(MonopolySpace("Vermont Avenue","Light Blue",100,6));
    spaces.push_back(MonopolySpace("Connecticut Avenue","Light Blue",120,8));
    spaces.push_back(MonopolySpace("Liberty Avenue", "Light Blue", 130, 10));

    spaces.push_back(MonopolySpace("Electric Company","Utility",150,10));

    spaces.push_back(MonopolySpace("St. Charles Place","Pink",140,10));
    spaces.push_back(MonopolySpace("States Avenue","Pink",140,10));
    spaces.push_back(MonopolySpace("Virginia Avenue","Pink",160,12));
    spaces.push_back(MonopolySpace("Sunset Boulevard", "Pink", 170, 14));

    spaces.push_back(MonopolySpace("Pennsylvania Railroad","Railroad",200,25));
    spaces.push_back(MonopolySpace("Grand Central Station", "Railroad", 250, 30));

    spaces.push_back(MonopolySpace("St. James Place","Orange",180,14));
    spaces.push_back(MonopolySpace("Tennessee Avenue","Orange",180,14));
    spaces.push_back(MonopolySpace("New York Avenue","Orange",200,16));
    spaces.push_back(MonopolySpace("Maple Avenue", "Orange", 210, 18));
    spaces.push_back(MonopolySpace("Crescent Park", "Orange", 200, 16));

    spaces.push_back(MonopolySpace("Water Works","Utility",150,10));

    spaces.push_back(MonopolySpace("Kentucky Avenue","Red",220,18));
    spaces.push_back(MonopolySpace("Indiana Avenue","Red",220,18));
    spaces.push_back(MonopolySpace("Illinois Avenue","Red",240,20));
    spaces.push_back(MonopolySpace("Midtown Commons", "Red", 240, 20));
    spaces.push_back(MonopolySpace("Broadway Heights", "Red", 260, 22));

    spaces.push_back(MonopolySpace("B. & O. Railroad","Railroad",200,25));

    spaces.push_back(MonopolySpace("Atlantic Avenue","Yellow",260,22));
    spaces.push_back(MonopolySpace("Ventnor Avenue","Yellow",260,22));
    spaces.push_back(MonopolySpace("Marvin Gardens","Yellow",280,24));
    spaces.push_back(MonopolySpace("Riverfront Drive", "Yellow", 300, 26));

    spaces.push_back(MonopolySpace("Short Line","Railroad",200,25));

    spaces.push_back(MonopolySpace("Pacific Avenue","Green",300,26));
    spaces.push_back(MonopolySpace("North Carolina Avenue","Green",300,26));
    spaces.push_back(MonopolySpace("Pennsylvania Avenue","Green",320,28));
    spaces.push_back(MonopolySpace("Silver Lake Avenue", "Green", 340, 30));
    spaces.push_back(MonopolySpace("Harborview Avenue", "Green", 360, 32));

    spaces.push_back(MonopolySpace("Park Place","Dark Blue",350,35));
    spaces.push_back(MonopolySpace("Boardwalk","Dark Blue",400,50));
    spaces.push_back(MonopolySpace("Imperial Gardens", "Dark Blue", 420, 55));
    board.addMany(spaces);

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();

    return 0;
}

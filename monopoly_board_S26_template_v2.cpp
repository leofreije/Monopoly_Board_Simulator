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
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    //checks if two spaces have the same name
    bool isEqual(MonopolySpace other) {
        return this->propertyName == other.propertyName;
    }

    void print() {
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
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    //adds a space after checking that nodeCount is not MAX_SPACES
    bool addSpace(T value) {
        if (nodeCount == MAX_SPACES) {
            return false;
        }

        Node<T> *newNode = new Node<T>(value);

        if (headNode == nullptr) {
            headNode = newNode;
            tailNode = newNode;
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
    //adds all spaces to the board sequentially until MAX_SPACES is reached, returning number of spaces successfully added
    int addMany(vector<T> values) {
        int ctr = 0;

        for (int i = 0; i < values.size(); i++) {
            if (!addSpace(values[i])) {
                break;
            }

            ctr++;
        }

        return ctr;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    //safely moves playerNode forward step times, incrementing passGOCount when passing GO space
    void movePlayer(int steps) {

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
    //prints 'count' spaces starting from playerNode
    void printFromPlayer(int count) {
        if (headNode == nullptr || count <= 0) {
            cout << "Error, board is empty or count is too small" << endl;
            return;
        }

        Node<T> *temp = playerNode;
        for (int i = 0; i < count; i++) {
            temp->data.print();
            cout << endl;
            temp = temp->nextNode;
        }
    }

    //Traverses the entire board and prints each node once
    void printBoardOnce() {
        if (headNode == nullptr) {
            return;
        }

        Node<T> *temp = headNode;
        do {
            temp->data.print();
            cout << endl;
            temp = temp->nextNode;
        } while (temp != headNode);
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    //deletes a node by name, returns true if deleted or false otherwise
    //enforces edge cases and maintains circular link
    //decrements nodeCount when a node is deleted
    bool removeByName(string name) {
        Node<T> *temp = headNode;
        Node<T> *prev = tailNode;

        if (headNode == nullptr) { //Check if list is empty
            return false;
        }

        if (headNode == tailNode && headNode->data.propertyName == name) { //Delete single node list

            if (playerNode == headNode) {
                playerNode = nullptr;
            }

            delete headNode;
            headNode = nullptr;
            tailNode = nullptr;
            nodeCount--;
            return true;
        }

        do {
            if(temp->data.propertyName == name && playerNode == temp) { //ensures playerNode points to a valid node
                playerNode = temp->nextNode;
            }

            if (temp->data.propertyName == name && temp == headNode) { //deletes head
                headNode = headNode->nextNode;
                tailNode->nextNode = headNode;
                delete temp;
                nodeCount--;
                return true;
            }
            else if (temp->data.propertyName == name && temp == tailNode) { //deletes tail
                tailNode = prev;
                tailNode->nextNode = headNode;
                delete temp;
                nodeCount--;
                return true;
            }
            else if (temp->data.propertyName == name) { //deletes middle
                prev->nextNode = temp->nextNode;
                delete temp;
                nodeCount--;
                return true;
            }

            prev = temp;
            temp = temp->nextNode;

        } while (temp != headNode);
        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    //returns a vector<string> of all space names that match color
    vector<string> findByColor(string color) {
        vector<string> matches;
        Node<T> *temp = headNode;

        if (headNode == nullptr) {
            return matches;
        }

        do {
            if (temp->data.propertyColor == color) {
                matches.push_back(temp->data.propertyName);
            }
            temp = temp->nextNode;
        } while (temp != headNode);

        return matches;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    //safely deletes all nodes
    void clear() {
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
        playerNode = nullptr;
        nodeCount = 0;
        cout << "\nBoard Cleared" << endl;
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

    //Board creation using hardcoded spaces
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
    // Advanced A Feature Demo
    // -------------------------------

    string name = "Reading Railroad";
    cout<< "\nRemove Space by Name: " << name << endl;
    board.removeByName(name);
    board.printBoardOnce();

    cout<< "\nFind Spaces by Color:" << endl;
    vector<string> brownProps = board.findByColor("Brown");
    for (int i = 0; i < brownProps.size(); i++) {
        cout << brownProps[i] << endl;
    }

    board.clear();
    return 0;
}

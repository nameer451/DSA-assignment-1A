#include <iostream>
#include <random>
#include <cstdint>

using namespace std;

class Node { 
public:
    unsigned long long data;
    Node* next;

    Node(unsigned long long data) : data(data), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    bool isEmpty() {
        return head == nullptr;
    }

    void append(unsigned long long data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    unsigned long long generate64BitRandom() {
        random_device rd; 
        mt19937_64 gen(rd());
        uniform_int_distribution<unsigned long long> dist(0, numeric_limits<unsigned long long>::max());
        return dist(gen);
    }

    void generate1024bitNumber() {
        for (int i = 0; i < 16; i++) { 
            unsigned long long newNum = generate64BitRandom();
            append(newNum); 
        }
    }

    void printList() { 
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;
    list.generate1024bitNumber();
    list.printList();
    return 0;
}

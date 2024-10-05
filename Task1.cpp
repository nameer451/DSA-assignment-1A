#include <iostream>
#include <string>
using namespace std;

class node{
    public:
    int process_id;
    float execution_time, remaining_time;
    node * next;
    node(int process_id, float execution_time, float remaining_time) :  process_id(process_id), execution_time(execution_time), remaining_time(remaining_time), next(nullptr){}
};

class circularLinkedList{
    public:
    node * head;
    node * tail;
    int idNums = 0;
    int size = 0;

    circularLinkedList() : head(nullptr), tail(nullptr), idNums(0) {}

    bool isEmpty(){
        return head == nullptr;
    }

    void addNode(float execution_time){
        idNums++;
        size++;
        node * newNode = new node(idNums, execution_time, execution_time);

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    void initialize(){
        addNode(10);
        addNode(10);
        addNode(15);
        cout << "Bootup Processes: \nID\tExecution Time\n1 \t10\n2 \t10\n3 \t15\n";
    }

    void deleteNode(int process_id) {
        if (isEmpty()) return;

        node *loc = head;
        node *ploc = tail;

        do {
            if (loc->process_id == process_id) {
                if (loc == head && loc == tail) {
                    head = tail = nullptr;
                } else if (loc == head) {
                    
                    head = loc->next;
                    tail->next = head;
                } else if (loc == tail) {
                    
                    tail = ploc;
                    tail->next = head;
                } else {
                    ploc->next = loc->next;
                }

                delete loc;
                size--;
                return;
            }
            ploc = loc;
            loc = loc->next;
        } while (loc != head);
    }


    void printCycle(int cycleCount){
        if (isEmpty()) {
            cout << "No processes to show." << endl;
            return;
        }
        node * loc = head;
        cout << "Cycle #" << cycleCount << endl;
        do {
            cout << "Process ID: " << loc->process_id << " | Time Remaining: " << loc->remaining_time << endl;
            loc = loc->next;
        } while (loc != head);
    }

    void runCycle(float run_time) {
        if (isEmpty()) return;

        int numOfNodesProccessed = 0;
        int initial_size = size;

        node* loc = head;
        node* nextNode = nullptr;

        do {
            loc->remaining_time -= run_time;
            nextNode = loc->next; 

            if (loc->remaining_time <= 0) {
                cout << "Process " << loc->process_id << " completed!" << endl;
                deleteNode(loc->process_id);

                if (isEmpty()) {
                    break;
                }
            }

            loc = nextNode;
            numOfNodesProccessed++;
        } while (!isEmpty() && (numOfNodesProccessed<initial_size));
    }

};

int main(){
    circularLinkedList processes;
    float timePerProcess;
    int cycleNum = 1;

    cout << "Initializing PC upon bootup....." << endl;
    processes.initialize();

    cout << endl << "CPU time per Process per Cycle: ";
    cin >> timePerProcess;

    while (!processes.isEmpty()) {
        processes.runCycle(timePerProcess);
        processes.printCycle(cycleNum);
        cycleNum++;

        if (!processes.isEmpty()) {
            cout << "Add Process(Y/N)? ";
            char addProcess;
            cin >> addProcess;
            if (addProcess == 'y' || addProcess == 'Y') {
                float execution_time;
                cout << endl << "Enter the time needed to execute the process: ";
                cin >> execution_time;
                processes.addNode(execution_time);
            }
        }
    }

    cout << "All processes complete!";
    return 0;
}

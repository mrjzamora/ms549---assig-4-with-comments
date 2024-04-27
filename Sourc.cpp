// Include necessary library headers
#include <iostream>  // For input and output
#include <chrono>    // For high-resolution timing
#include <cstdlib>   // For random number generation
#include <vector>    // To use the vector container
#include <iomanip>   // For controlling input/output formatting

// Definition of a Node in a doubly linked list
struct Node {
    int data;        // Data stored in the node
    Node* prev;      // Pointer to the previous node
    Node* next;      // Pointer to the next node
    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
    // Constructor initializes node with data and null pointers to next and previous nodes
};

// Base class for Doubly Linked List
class DoublyLinkedList {
protected:
    Node* head;  // Pointer to the first node in the list
    Node* tail;  // Pointer to the last node in the list
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}  // Constructor initializes an empty list
    virtual void insert(int data) = 0;  // Pure virtual function for inserting data
    virtual void remove(int data) = 0;  // Pure virtual function for removing data

    // Function to print all contents of the list
    void printContents() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";  // Print the data at the current node
            current = current->next;  // Move to the next node
        }
        std::cout << std::endl;
    }
};

// Derived class for implementing a Stack using Doubly Linked List
class Stack : public DoublyLinkedList {
public:
    void insert(int data) override {
        Node* newNode = new Node(data);  // Create a new node with the given data
        if (head == nullptr) {  // If the stack is empty, both head and tail point to the new node
            head = tail = newNode;
        }
        else {  // Otherwise, add the new node at the beginning of the list
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void remove(int data) override {
        Node* temp = head;  // Start at the head of the list
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;  // Traverse the list to find the node with the specified data
        }
        if (temp == nullptr) return;  // If the node wasn't found, exit the function
        // Adjust pointers and delete the node
        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (temp == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;  // Free the memory of the node
    }
};

// Derived class for implementing a Queue using Doubly Linked List
class Queue : public DoublyLinkedList {
public:
    void insert(int data) override {
        Node* newNode = new Node(data);  // Create a new node
        if (tail == nullptr) {  // If the queue is empty, both head and tail point to the new node
            head = tail = newNode;
        }
        else {  // Otherwise, add the new node at the end of the list
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove(int data) override {
        Node* temp = head;  // Start at the head of the list
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;  // Traverse the list to find the node with the specified data
        }
        if (temp == nullptr) return;  // If the node wasn't found, exit the function
        // Adjust pointers and delete the node
        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (temp == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;  // Free the memory of the node
    }
};

// Function to test performance of insertions and deletions on the list
void performanceTest(DoublyLinkedList& obj, const std::string& name, const std::vector<int>& sizes) {
    std::vector<long long> insertionTimes;  // To store times for insert operations
    std::vector<long long> deletionTimes;   // To store times for delete operations

    for (int n : sizes) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = std::rand() % 100000;  // Generate random data to insert
        }

        // Timing insert operations
        auto start = std::chrono::high_resolution_clock::now();
        for (int num : data) {
            obj.insert(num);
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertionTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

        // Timing remove operations
        start = std::chrono::high_resolution_clock::now();
        for (int num : data) {
            obj.remove(num);
        }
        end = std::chrono::high_resolution_clock::now();
        deletionTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }

    // Printing the timing results
    std::cout << "Performance Results for " << name << ":\n";
    std::cout << "Operation\t\t100\t\t1000\t\t10000\n";
    std::cout << "Insert (ms)\t\t" << insertionTimes[0] << "\t\t"
        << insertionTimes[1] << "\t\t" << insertionTimes[2] << "\n";
    std::cout << "Delete (ms)\t\t" << deletionTimes[0] << "\t\t"
        << deletionTimes[1] << "\t\t" << deletionTimes[2] << "\n";
}

// Main function to demonstrate Stack and Queue operations and performance testing
int main() {
    Stack myStack;  // Create a Stack
    Queue myQueue;  // Create a Queue
    std::vector<int> testSizes = { 100, 1000, 10000 };  // Different sizes for performance testing

    // Demonstrating basic operations for Stack
    std::cout << "Stack operations:\n";
    myStack.insert(10);
    myStack.insert(20);
    myStack.insert(30);
    std::cout << "Stack contents after inserts: ";
    myStack.printContents();  // Print stack contents after inserts
    myStack.remove(20);  // Remove a specific item
    std::cout << "Stack contents after removing 20: ";
    myStack.printContents();

    // Demonstrating basic operations for Queue
    std::cout << "\nQueue operations:\n";
    myQueue.insert(10);
    myQueue.insert(20);
    myQueue.insert(30);
    std::cout << "Queue contents after inserts: ";
    myQueue.printContents();  // Print queue contents after inserts
    myQueue.remove(30);  // Remove a specific item
    std::cout << "Queue contents after removing 30: ";
    myQueue.printContents();

    // Perform and display performance testing for both Stack and Queue
    std::cout << "\nPerformance Measurements:\n";
    performanceTest(myStack, "Stack", testSizes);
    performanceTest(myQueue, "Queue", testSizes);

    return 0;
}

// Queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

// Queue class definition
class Queue {
private:
    // Node structure for queue elements
    struct Node {
        char data;         // Character data
        Node* next;        // Pointer to the next node
        Node(char d) : data(d), next(NULL) {} // Constructor for Node
    };
    Node* front;           // Pointer to the front of the queue
    Node* rear;            // Pointer to the rear of the queue

public:
    // Constructor to initialize an empty queue
    Queue() : front(NULL), rear(NULL) {}
    
    // Method to clear the queue
    void clear() {
        while (!isEmpty()) {
            dequeue(); // Dequeue all elements to free memory
        }
        //cout << "\nQueue has been cleared." << endl; // Debug output
    }
    
    // Destructor to clean up the queue
    ~Queue() {
        clear(); // Dequeue all elements to free up memory
    }

    // Method to add an element to the rear of the queue
    void enqueue(char letter) {
        Node* newNode = new Node(letter); // Create a new node with the letter
        if (rear) {
            rear->next = newNode; // Link the new node to the rear
        }
        rear = newNode;           // Update the rear to the new node
        if (!front) {
            front = rear;         // If the queue was empty, set front to the new node
        }
    }

    // Method to remove an element from the front of the queue
    char dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty"); // Throw an error if the queue is empty
        }
        Node* temp = front;      // Temporarily store the front node
        char data = front->data; // Get the data from the front node
        front = front->next;     // Move the front pointer to the next node
        if (!front) {
            rear = NULL;         // If the queue is now empty, set rear to NULL
        }
        delete temp;             // Delete the old front node
        return data;             // Return the dequeued data
    }

    // Method to check if the queue is empty
    bool isEmpty() const {
        return front == NULL; // Return true if front is NULL
    }

    // Method to get the data from the front of the queue without removing it
    char peek() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty"); // Throw an error if the queue is empty
        }
        return front->data; // Return the data from the front node
    }

    // Method to display all elements in the queue
    void display() const {
        Node* current = front;    // Start from the front of the queue
        cout << "\nAll guessed letters & bought vowels: (";
		while (current) {
            cout << current->data << ' '; // Print the data of each node
            current = current->next;      // Move to the next node
        }
        cout << ")";
        cout << endl;            // Print a newline at the end
    }
    
    // Method to check if a character is already present in the queue
    bool contains(char c) const {
	    Node* current = front;
	    while (current != NULL) {
	        if (current->data == c) {
	            return true;
	        }
	        current = current->next;
	    }
	    return false;
	}
};

#endif // QUEUE_H

/*Note: calling the destructor directly is not a recommended practice in c++ because there can be incomplete cleanup
calling the destructor directly doesn't automatically free memory allocated for the object, so there can be memory leaks if the 
deallocation isnt handled manually. There are other reasons, like the object still being in scope after the destructor is 
explicitly called, the object can still be accessed in an invalid state leading to undefined behaviour.*/


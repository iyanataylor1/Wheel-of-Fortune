//WHEEL CLASS
#ifndef WHEEL_H
#define WHEEL_H

#include "Node.h"
#include <cstdlib>
#include <ctime>

class Wheel {
private:
    Node* head;
    Node* current; //special pointer to point to the current card position on the wheel

    //function that calls addCard multiple times to populate the wheel with cards
    void initializeWheel() {
        addCard(Card(Card::BANKRUPT, 0)); // (bankrupt, 1 million, bankrupt) -> Bankrupt
        addCard(Card(Card::MONEY, 500));
        addCard(Card(Card::MONEY, 1000));
        addCard(Card(Card::LOSE_TURN, 0)); // [WILD]00 -> Lose a Turn
        addCard(Card(Card::MONEY, 1500));
        addCard(Card(Card::MONEY, 2000));
        addCard(Card(Card::MONEY, 2500));
        addCard(Card(Card::BANKRUPT, 0));
        addCard(Card(Card::MONEY, 500));
        addCard(Card(Card::MONEY, 1000));
        addCard(Card(Card::LOSE_TURN, 0));
        addCard(Card(Card::MONEY, 1500));
        addCard(Card(Card::MONEY, 2000));
        addCard(Card(Card::MONEY, 2500));
        addCard(Card(Card::BANKRUPT, 0));
        addCard(Card(Card::MONEY, 500));
        addCard(Card(Card::MONEY, 1000));
        addCard(Card(Card::LOSE_TURN, 0));
        addCard(Card(Card::MONEY, 1500));
        addCard(Card(Card::MONEY, 2000));
        addCard(Card(Card::MONEY, 2500));
        addCard(Card(Card::BANKRUPT, 0));
        addCard(Card(Card::MONEY, 850)); // Free Play -> Money $850
        addCard(Card(Card::MONEY, 1000));
        addCard(Card(Card::MONEY, 2000));

        // Making the list circular
        if (head) {
            Node* temp = head;
            while (temp->getNext() && temp->getNext() != head) {
                temp = temp->getNext();
            }
            temp->setNext(head);
        }
    }

    //function that adds a new Card to the circular linked list
    void addCard(const Card& card) {
        Node* newNode = new Node(card); // Create a new node with the given card
        if (!head) { // If the list is empty, set head to the new node
            head = newNode;
        } else {  // Otherwise, find the last node in the list
            Node* temp = head;

            // Traverse the list until we reach the node whose next points back to head
            while (temp->getNext() && temp->getNext() != head) {
                temp = temp->getNext();
            }
            temp->setNext(newNode); // Set the next pointer of the last node to the new node
        }
        // Make the new node's next point to head, maintaining the circular structure
        newNode->setNext(head);
    }


public:

    //constructor
    Wheel() : head(nullptr), current(nullptr) {
        initializeWheel();
        current = head;
    }

    void spinWheel() {
        int randomSpaces = (rand() % 51) + 50; // Random number between 50 and 100
        for (int i = 0; i < randomSpaces; ++i) {
            current = current->getNext();
        }
    }

    Card getCurrentCard() const {
        return current->getCard();
    }
};

#endif // WHEEL_H

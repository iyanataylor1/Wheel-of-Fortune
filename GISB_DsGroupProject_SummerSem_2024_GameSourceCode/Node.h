//NODE CLASS

#ifndef NODE_H
#define NODE_H

#include "Card.h"

class Node {
private:
    Card card;
    Node* next;

public:
    Node(const Card& card) : card(card), next(nullptr){
	}

    Card getCard() const { 
		return card; 
	}
	
    void setCard(const Card& card) { 
		this->card = card; 
	}

    Node* getNext() const { 
		return next; 
	}
	
    void setNext(Node* next) { 
		this->next = next; 
	}
};

#endif // NODE_H


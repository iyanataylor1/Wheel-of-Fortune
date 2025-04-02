#include<iostream>
using namespace std;

class Card{
    public:
    //enumeration for the card types
        enum CardType{MONEY, LOSE_TURN, BANKRUPT};

    private:
    CardType type;// enum type for card type
    int value;

    public:
    //Default constructor
    Card(): type (MONEY), value (0){
	}
	
    //Constructor with parameters
    Card(CardType cardType, int cardValue): type (cardType), value(cardValue){
	}

    //Copy Constructor
    Card(const Card& other): type(other.type), value(other.value){
	}
     
	//Getter for card type
    CardType getType() const{
		return type;
	}
	
    //Getter for card value
    int getValue() const{
		return value;
	}
	
    //Setter for card type
    void setType(CardType cardType){
		type = cardType;
	}
	
    //Setter for card value
    void setValue(int cardValue){
		value = cardValue;
	}
};


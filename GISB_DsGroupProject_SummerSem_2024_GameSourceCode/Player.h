#include <iostream>
using namespace std;
#include<string>

class Player{
private:
    int playernumber; //Unique identifier for each player
    string name; //The players name
    int grandtotal;//Total money accumulated by the player across all the rounds
    int roundtotal;//Total money accumulated by the player in the current round

public:	
    // Default Constructor
    Player(): playernumber(0), name(""), grandtotal(0), roundtotal(0){
	}

    // Constructor with parameters
    Player(int number,const string& playername ): playernumber(number), name(playername), grandtotal (0), roundtotal(0){
	}
	
    //Copy constructor
    Player(const Player& other): playernumber(other.playernumber), name(other.name), grandtotal(other.grandtotal), roundtotal(other.roundtotal){
	}

    //Getters
    int getplayernumber() const{ 
    	return playernumber;
    }
    
    string getname() const{
    	return name; 
    }
    
    int getgrandtotal(){
        return grandtotal; 
    }
    int getroundtotal() const{ 
        return roundtotal; 
    }

    //Setters
    void setplayernumber(int number){ 
        playernumber = number; 
    }
    void setname(const string& playername){
        name = playername; 
    }

    //Methods to add up the round total and grand total
    void addroundtotal(int amount){ 
        roundtotal += amount;
    }
    
    /*
    void addtograndtotal(){
    	grandtotal += roundtotal;
	}*/ 
	
	void addtograndtotal(int amount) {
        grandtotal += amount;
    } 
	       
    //Method to reset the round total
    void resetroundtotal(){ 
        roundtotal = 0; 
    }
    
    //Method to reset grandtotal (if starting a new game)
    void resetgrandtotal(){ 
        grandtotal = 0; 
    }
};


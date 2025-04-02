// GAME class

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Wheel.h"
#include "Puzzle.h"
#include "Player.h"
#include "Queue.h"

using namespace std;

// Game class definition
class Game {
	
	// PRIVATE class members
private:
    // List of players participating in the game
    vector<Player> players;

    // Instance of the Wheel class
    Wheel wheel;

    // The current round number (1 to 3)
    int currentRound;

    // Index of the current player in the players list
    int currentPlayerIndex;
    
    // Index of the current puzzle in the puzzles list
    int currentPuzzleIndex;

    // Instance of the Puzzle class
    Puzzle currentPuzzle;

    // Queue to track guessed letters
    Queue guessedLettersQueue;
    
    // List of puzzles
    vector<Puzzle> puzzles;
    
    // Method to load puzzles from a file
    void loadPuzzlesFromFile(const string& filename) {
        ifstream file(filename); // Open the file
        if (!file.is_open()) {
            cerr << "\nError opening file: " << filename << endl;
            return;
        }
        
        puzzles.clear(); // Clear the previous puzzles
        string line;
        while (getline(file, line)) { // Read each line
            size_t delimiterPos = line.find(','); // Find the comma
            if (delimiterPos != string::npos) {
                string category = line.substr(0, delimiterPos); // Extract category
                string puzzle = line.substr(delimiterPos + 1); // Extract puzzle
                puzzles.push_back(Puzzle(category, puzzle)); // Create and store Puzzle object
            }
        }

        if (!puzzles.empty()) {
        	currentPuzzleIndex = 0;
            currentPuzzle = puzzles[currentPuzzleIndex]; // Set the initial puzzle to the first loaded puzzle
            
            cout << "\nRound " << currentRound << endl;
            cout << "\nCategory: " << currentPuzzle.getCategory() << endl;
            cout << "Puzzle: " << currentPuzzle.revealPuzzle() << endl;
        }

        file.close(); // Close the file
    }
    
    // Helper function to count occurrences of a letter in a string
	int countOccurrences(const string& str, char letter) {
    	return count(str.begin(), str.end(), letter);
	}
	
	// Helper function to move to the next puzzle after each round is complete
	void advanceToNextPuzzle() {
        currentPuzzleIndex++;
        if (currentPuzzleIndex >= puzzles.size()) {
            currentPuzzleIndex = 0; // Reset to the first puzzle if we've used all puzzles
        }
        currentPuzzle = puzzles[currentPuzzleIndex];
        guessedLettersQueue.clear(); // Clear the queue at the end of each round

		//cout << "\nAdvancing to next puzzle. Current Puzzle Index: " << currentPuzzleIndex << endl; // Debugging line
        cout << "\nRound " << currentRound + 1 << endl;
        cout << "\nCategory: " << currentPuzzle.getCategory() << endl;
        cout << "Puzzle: " << currentPuzzle.revealPuzzle() << endl;
    }
   
    // Method to guess a letter
	bool guessLetter(Player& player, int cardValue) {
	    try {
	        cout << player.getname() << ", guess a consonant: ";
	        char guessedLetter;
	        cin >> guessedLetter;
	        guessedLetter = toupper(guessedLetter); // Convert to uppercase for consistency
	        
	        // Validate the input to ensure it's a letter
	        if (!isalpha(guessedLetter)) {
	            cout << "\nInvalid input. Please enter a letter." << endl;
	            return false; // Allow the player to guess again
	        }
	        
	        // Check if the guessed letter is a vowel
	        if (guessedLetter == 'A' || guessedLetter == 'E' || guessedLetter == 'I' || guessedLetter == 'O' || guessedLetter == 'U') {
	            cout << "\nVowels cannot be guessed. You need to buy them." << endl;
	            return false; // Allow the player to guess again
	        }
	
	        // Check if the guessed letter is already in the queue
	        if (guessedLettersQueue.contains(guessedLetter)) {
	            cout << "\nLetter already guessed. Try a different letter." << endl;
	            return false; // Allow the player to guess again
	        }
	
	        // Add the guessed letter to the queue and display all gueesed letters
	        guessedLettersQueue.enqueue(guessedLetter);
	        guessedLettersQueue.display();
    		
    		// Call the method to update guessed letters
	        currentPuzzle.guessLetterInPuzzle(guessedLetter);
	
	        // Count the occurrences of the guessed letter in the revealed puzzle
	        int occurrences = countOccurrences(currentPuzzle.getPuzzle(), guessedLetter);
	        int totalValue = occurrences * cardValue;
	
	        if (occurrences > 0) {
	            player.addroundtotal(totalValue);
	            cout << "\nCorrect! " << guessedLetter << " appears " << occurrences << " times. You earned $" << totalValue << "." << endl;
	            cout << "Puzzle: " << currentPuzzle.revealPuzzle() << endl;
	            
	            if(currentPuzzle.isSolved()){
	            	cout << "\nCongratulations! You solved the puzzle!" << endl;
	            	player.addtograndtotal(player.getroundtotal());
	                cout << player.getname() << "'s total earnings: $" << player.getgrandtotal() << endl;
	                currentRound++; // Move to the next round
	                
	                if(currentRound >= 3){
	                	endGame(); // End the game if all rounds are complete
					} else {
						advanceToNextPuzzle();
					}
				}
	            
	            return false; // Allow the player to continue their turn
	        } else {
	            cout << "\nIncorrect guess. The letter " << guessedLetter << " is not in the puzzle." << endl;
	            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
	            return true; // End the player's turn
	        }
    		
	    } catch (exception& e) {
	        cout << "\nAn error occurred: " << e.what() << endl;
	        return true; // End the player's turn on error
	    }
	}

	// Method to buy a vowel
	bool buyVowel(Player& player) {
	    try {
	        const int vowelCost = 50;
	        
	        if (player.getroundtotal() < vowelCost) {
	            cout << "\nInsufficient funds to buy a vowel. You need at least $" << vowelCost << "." << endl;
	            return false; // Allow the player to choose another action
	        }
	
	        cout << player.getname() << ", buy a vowel: ";
	        char guessedVowel;
	        cin >> guessedVowel;
	        guessedVowel = toupper(guessedVowel); // Convert to uppercase for consistency
	        
	        // Validate the input to ensure it's a letter
	        if (!isalpha(guessedVowel)) {
	            cout << "\nInvalid input. Please enter a letter." << endl;
	            return false; // Allow the player to guess again
	        }
	
	        // Check if the guessed vowel is already in the queue
	        if (guessedLettersQueue.contains(guessedVowel)) {
	            cout << "\nVowel already guessed. Try a different vowel." << endl;
	            return false; // Allow the player to guess again
	        }
	        
	        // Add the bought vowel to the queue
	        guessedLettersQueue.enqueue(guessedVowel);
	        guessedLettersQueue.display();
	
	        // Deduct the cost of the vowel from the player's round total
	        player.addroundtotal(-vowelCost);
	
	        // Add the guessed vowel to the queue
	        guessedLettersQueue.enqueue(guessedVowel);
	
	        // Check if the guessed vowel is in the puzzle
	        if (currentPuzzle.guessLetterInPuzzle(guessedVowel)) {
	            cout << "\nCorrect! The vowel " << guessedVowel << " is in the puzzle." << endl;
	            cout << "Puzzle: " << currentPuzzle.revealPuzzle() << endl;
	            
	            if(currentPuzzle.isSolved()){
	            	cout << "\nCongratulations! You solved the puzzle!" << endl;
	            	player.addtograndtotal(player.getroundtotal());
	                cout << player.getname() << "'s total earnings: $" << player.getgrandtotal() << endl;
	                currentRound++; // Move to the next round
	                
	                if(currentRound >= 3){
	                	endGame(); // End the game if all rounds are complete
					} else {
						advanceToNextPuzzle();
					}
				}
	            
	            return false; // Allow the player to continue their turn
	        } else {
	            cout << "\nIncorrect guess. The vowel " << guessedVowel << " is not in the puzzle." << endl;
	            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
	            return true; // End the player's turn
	        }
	    } catch (exception& e) {
	        cout << "\nAn error occurred: " << e.what() << endl;
	        return true; // End the player's turn on error
	    }
	}

	// Method to solve puzzle
	bool solvePuzzle(Player& player, int cardValue) {
	    try {
	        cout << player.getname() << ", enter your solve attempt: ";
	        cin.ignore(); // Ignore any remaining newline character from previous input
	        string solveAttempt;
	        getline(cin, solveAttempt);
	
	        // Convert the solve attempt to uppercase for case-insensitive comparison
	        transform(solveAttempt.begin(), solveAttempt.end(), solveAttempt.begin(), ::toupper);
	
	        // Convert the actual puzzle to uppercase for comparison
	        string actualPuzzle = currentPuzzle.getPuzzle();
	        transform(actualPuzzle.begin(), actualPuzzle.end(), actualPuzzle.begin(), ::toupper);
	
	        // Check if the solve attempt matches the puzzle
	        if (solveAttempt == actualPuzzle) {
	            cout << "\nCorrect! You solved the puzzle: " << currentPuzzle.getPuzzle() << endl;
	            // Award the player the money for the spin
				player.addroundtotal(cardValue);
				player.addtograndtotal(player.getroundtotal());
	            cout << player.getname() << "'s total earnings: $" << player.getgrandtotal() << endl;
	            
				currentRound++; // Move to the next round
				// Load the next puzzle if available
	            if(currentRound >= 3){
	                endGame(); // End the game if all rounds are complete
				} else {
					advanceToNextPuzzle();
				}
				
	            return true; // End the player's turn and the round
	        } else {
	            cout << "\nIncorrect solve attempt. The turn moves to the next player." << endl;
	            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
	            return true; // End the player's turn
	        }
	    } catch (exception& e) {
	        cout << "\nAn error occurred: " << e.what() << endl;
	        return true; // End the player's turn on error
	    }
	}
	
	// Method to determine the winner based on the highest grand total.
	void checkWinner() {
	    Player* winner = nullptr;
	    int highestTotal = 0;
	    
	    for (Player& player : players) {
	        if (player.getgrandtotal() > highestTotal) {
	            highestTotal = player.getgrandtotal();
	            winner = &player;
	        }
	    }
	    
	    if (winner) {
	        cout << "\nThe winner is " << winner->getname() << " with a grand total of $" << highestTotal << "!" << endl;
	    } else {
	        cout << "\nNo winner this game." << endl;
	    }
	    
	    // Reset the current round number at the end of the game
    	currentRound = 1;
	    
	    // Prompt to choose to go for another 3 rounds or end the game
	    char choice;
	    cout << "\nDo you want to play another game? (y/n): ";
	    cin >> choice;
	    
	    if (tolower(choice) == 'y') {
	    	// Reset the players' grand totals
	        for (Player& player : players) {
	            player.resetgrandtotal();
	        }
	    
	        startGame();
	    } else {
	        cout << "\nThank you for playing Wheel of Fortune!" << endl;
	    }
	}

	// PUBLIC class members
public:
	// Constructor to initialize the game with players
    Game() : currentRound(1), currentPlayerIndex(0), currentPuzzle("", "") {
        for (int i = 1; i <= 3; ++i) {
            string name;
            cout << "Hello player " << i << "! Tell us your name: ";
            getline(cin, name);
            players.push_back(Player(i, name));
        }
    }
   
    // Method to handle player turns
    void handlePlayerTurn(Player& player) {
	    Player& currentPlayer = players[currentPlayerIndex];
	
	    // Spin the wheel
	    wheel.spinWheel(); // Spin the wheel
	    Card currentCard = wheel.getCurrentCard(); // Get the card the wheel landed on
	    int cardValue = currentCard.getValue(); // Get the value of the card
	
	    // Display the result of the wheel spin
	    cout << "\n" << currentPlayer.getname() << " spun the wheel and landed on ";
	    switch (currentCard.getType()) {
	        case Card::MONEY: // If the card is a money card
	            cout << "$" << cardValue << endl; // Display the money value
	            break;
	        case Card::BANKRUPT: // If the card is a BANKRUPT card
	            cout << "BANKRUPT" << endl;
	            currentPlayer.resetroundtotal(); // Reset the player's round total
	            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
	            return; // End the turn
	        case Card::LOSE_TURN: // If the card is a LOSE TURN card
	            cout << "LOSE TURN" << endl;
	            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
	            return; // End the turn
	    }
	
	    // Handle player actions
	    bool turnComplete = false;
	    while (!turnComplete) {
	        // Prompt the player for their action
	        cout << currentPlayer.getname() << ", choose an action (guess, buy, solve): ";
	        string action;
	        cin >> action; // Get the action from the player
	        transform(action.begin(), action.end(), action.begin(), ::tolower); // Convert the action to lowercase
	
	        // Determine the action to take
	        if (action == "guess") {
	            // Call a function to handle guessing a letter
	            turnComplete = guessLetter(currentPlayer, cardValue);
	        } else if (action == "buy") {
	            // Call a function to handle buying a vowel
	            turnComplete = buyVowel(currentPlayer);
	        } else if (action == "solve") {
	            // Call a function to handle solving the puzzle
	            turnComplete = solvePuzzle(currentPlayer, cardValue);
	        } else {
	            // If the action is invalid, prompt the player again
	            cout << "\nInvalid action. Please choose 'guess', 'buy', or 'solve'." << endl;
	        }
	    }
	}
	
	// Method to print a welcome message, load puzzles from a file, and initialize the first round. It will then call playRounds() to start the rounds.
	void startGame() {
	    // Print a welcome message
	    cout << "\nWelcome to Wheel of Fortune!" << endl;
	    
	    try {
	        // Load puzzles from file
	        loadPuzzlesFromFile("puzzles.txt");
	    } catch (const exception& e) {
	        cerr << "\nError loading puzzles: " << e.what() << endl;
	        return;
	    }
	    
	    // Initialize the first round
	    currentRound = 0;
	    
	    // Start the rounds
	    playRounds();
	}

	// Method to loop through three rounds, calling playRound() for each and endGame() after each round.
	void playRounds() {
	    for (int i = 0; i < 3; ++i) {
	        try {
	            // Play a single round
	            playRound();
	            
	            // End the current round and prepare for the next
	            endGame();
	        } catch (const exception& e) {
	            cerr << "\nError during round " << currentRound << ": " << e.what() << endl;
	            break;
	        }
	        
	        // Move to the next round
	        ++currentRound;
	    }
	    
	    // Determine the winner at the end of the game
	    checkWinner();
	}
	
	// Method to loop through players, allowing each to take turns and calling handlePlayerTurn() for each player's turn. It will check for round completion (e.g., puzzle solved).
	void playRound() {
	    bool roundCompleted = false;
	    
	    while (!roundCompleted) {
	        for (int i = 0; i < players.size(); ++i) {
	            currentPlayerIndex = i;
	            
	            try {
	                // Handle the current player's turn
	                handlePlayerTurn(players[i]);
	            } catch (const exception& e) {
	                cerr << "\nError during player " << players[i].getname() << "'s turn: " << e.what() << endl;
	            }
	            
	            // Check if the round is completed (e.g., puzzle solved)
	            if (currentPuzzle.isSolved()) {
	                roundCompleted = true;
	                break;
	            }
	        }
	    }
	}
	
	// Method to update scores, reset round-specific data, and check if the game should end or move to the next round.
	void endGame() {
	    // Check if the game should end or move to the next round
	    if (currentRound == 3) {
	        cout << "\nEnd of the game. Let's see who the winner is!" << endl;
	        checkWinner();
	    } else {
	        cout << "\nEnd of round " << currentRound << ". Moving to the next round." << endl;
	    }
	}
};

#endif // GAME_H


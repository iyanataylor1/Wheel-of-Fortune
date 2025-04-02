#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Puzzle {
private:
	string category;
	string puzzle;
	//string guessedLetters;
	unordered_set<char> guessedLetters;
	
public:
/*
    // Constructor
    Puzzle(const string& category, const string& puzzle): category(category), puzzle(puzzle) {
	}
*/	
	// Constructor
	Puzzle(const string& category, const string& puzzle): category(category) {
    	this->puzzle = puzzle;
    	// Convert the puzzle to uppercase
    	transform(this->puzzle.begin(), this->puzzle.end(), this->puzzle.begin(), ::toupper);
	}

    // Method to load a puzzle from a string
    void loadPuzzle(const string& newPuzzle) {
        puzzle = newPuzzle;
        guessedLetters.clear();
    }

	/*
    // Method to check if a guessed letter is in the puzzle
    bool guessLetterInPuzzle(char letter) {
        guessedLetters += letter;
        return puzzle.find(letter) != string::npos;
    }*/
    
    // Method to check if a guessed letter is in the puzzle
    bool guessLetterInPuzzle(char letter) {
        letter = toupper(letter); // Ensure letter is uppercase
        guessedLetters.insert(letter);
        
        // Debug print statements
    	//cout << "Guessed Letter: " << letter << endl;
    	//cout << "Puzzle: " << puzzle << endl;
        
        return puzzle.find(letter) != string::npos;
        //bool found;
        //cout << "Found: " << (found ? "Yes" : "No") << endl;
    	//return found;
    }

	/*
    // Method to reveal the current state of the puzzle with guessed letters
    string revealPuzzle() const {
        string revealedPuzzle;
        for (char ch : puzzle) {
            if (guessedLetters.find(ch) != string::npos || ch == ' ') {
                revealedPuzzle += ch;
            } else {
                revealedPuzzle += '_';
            }
        }
        return revealedPuzzle;
    }*/
    
    // Method to reveal the current state of the puzzle with guessed letters
    string revealPuzzle() const {
        string revealedPuzzle;
        for (char ch : puzzle) {
            if (guessedLetters.count(toupper(ch)) > 0 || ch == ' ') {
                revealedPuzzle += ch;
            } else {
                revealedPuzzle += '_';
            }
        }
        return revealedPuzzle;
    }

	/*
    // Method to check if the puzzle is solved
    bool isSolved() const {
        for (char ch : puzzle) {
            if (ch != ' ' && guessedLetters.find(ch) == string::npos) {  //'npos' means 'no position'
                return false;
            }
        }
        return true;
    }*/
    
    // Method to check if the puzzle is solved
    bool isSolved() const {
        for (char ch : puzzle) {
            if (ch != ' ' && guessedLetters.count(toupper(ch)) == 0) {  //'npos' means 'no position'
                return false;
            }
        }
        return true;
    }

    // Getter for category
    string getCategory() const {
        return category;
    }
    
    // Getter for the original puzzle string (to be used to count letter occurrences)
	string getPuzzle() const {
    	return puzzle;
	}
};

/*
int main() {
    // Example usage
    Puzzle puzzle("Phrase", "Hello World"); //'Hello world' is the phrase the user should guess

    cout << "Category: " << puzzle.getCategory() << endl;

    puzzle.guessLetterInPuzzle('H');
    puzzle.guessLetterInPuzzle('e');
    puzzle.guessLetterInPuzzle('o');

    cout << "Current State: " << puzzle.revealPuzzle() << endl;
    cout << "Is Solved: " << (puzzle.isSolved() ? "Yes" : "No") << endl;

    return 0;
}
*/

/*Note: 

//string guessedLetters;
unordered_set<char> guessedLetters;

In the attribute list guessedLetters was declared as a string originally but then it was changed to guessed letters to fix a comparison issue.
*/

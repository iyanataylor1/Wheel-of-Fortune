// Method to write categories and puzzles to a file to be read from for the game
// Store "puzzles.txt" in the same folder with the game files, this can be somewhere else

#include <fstream>
#include <iostream>
using namespace std;

int main() {
    // Open the file in write mode
    ofstream outFile("puzzles.txt");
    if (!outFile) {
        cerr << "Error creating file." << endl;
        return 1;
    }
    
    // Write the puzzles to the file
    outFile << "Occupation,Engineer" << endl;
    outFile << "Phrase,Hello World" << endl;
    outFile << "Vehicle Brand,Porsche" << endl;
    outFile << "Country,Democratic Republic of the Congo" << endl;

    // Close the file
    outFile.close();

    cout << "Puzzles written to puzzles.txt" << endl;
    return 0;
}


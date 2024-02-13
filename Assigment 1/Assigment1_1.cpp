#include <iostream>
#include "stackt.h" // Assuming stackt.h contains the Stackt class definition

// Function to move disks from source to target using auxiliary pegs
void Towers(int N, Stackt<int>* DisplayPegs[], Stackt<int>& Source, Stackt<int>& Target, Stackt<int>& Aux, char CharSource, char CharTarget, char CharAux, int& moveCount) {
    if (N == 1) {
        // Base case: move the top disk from Source to Target
        Target.push(Source.top());
        Source.pop();
        moveCount++;
        
        // Print the move and display the state of each peg
        std::cout << "Move " << moveCount << ": " << "Disk " << Target.top() << " from " << CharSource << " to " << CharTarget << std::endl;
        std::cout << "Peg A:" << std::endl;
        DisplayPegs[0]->display();
        std::cout << "Peg B:" << std::endl;
        DisplayPegs[1]->display();
        std::cout << "Peg C:" << std::endl;
        DisplayPegs[2]->display();
        std::cout << std::endl;
    } else {
        // Recursive case: move N-1 disks from Source to Aux using Target as auxiliary
        Towers(N - 1, DisplayPegs, Source, Aux, Target, CharSource, CharAux, CharTarget, moveCount);
        
        // Move the remaining disk from Source to Target
        Target.push(Source.top());
        Source.pop();
        moveCount++;
        
        // Print the move and display the state of each peg
        std::cout << "Move " << moveCount << ": " << "Disk " << Target.top() << " from " << CharSource << " to " << CharTarget << std::endl;
        std::cout << "Peg A:" << std::endl;
        DisplayPegs[0]->display();
        std::cout << "Peg B:" << std::endl;
        DisplayPegs[1]->display();
        std::cout << "Peg C:" << std::endl;
        DisplayPegs[2]->display();
        std::cout << std::endl;
        
        // Move the N-1 disks from Aux to Target using Source as auxiliary
        Towers(N - 1, DisplayPegs, Aux, Target, Source, CharAux, CharTarget, CharSource, moveCount);
    }
}

int main() {
    int N;
    std::cout << "Enter the number of disks: ";
    std::cin >> N;
    
    // Create three pegs
    Stackt<int> pegA, pegB, pegC;
    int moveCount = 0;
    
    // Initialize pegA with disks
    for (int i = N; i >= 1; --i) {
        pegA.push(i);
    }
    
    // Array of pointers to the three pegs
    Stackt<int>* pegs[] = { &pegA, &pegB, &pegC };
    // Characters representing the pegs
    char CharPegs[] = { 'A', 'B', 'C' };

    // Call Towers function to solve the problem
    Towers(N, pegs, pegA, pegC, pegB, CharPegs[0], CharPegs[2], CharPegs[1], moveCount);

    // Print the total number of moves needed
    std::cout << "Number of moves needed: " << moveCount << std::endl;

    return 0;
}
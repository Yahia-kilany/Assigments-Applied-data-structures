#include <iostream>
#include <map>
#include "stackt.h"

void Towers (int N , Stackt<int>* DisplayPegs[] , Stackt<int>& Source , Stackt<int>& Target , Stackt<int>& Aux , char CharSource , char CharTarget , char CharAux , int& moveCount) {
    if (N == 1) {
        Target.push (Source.top ());
        Source.pop ();
        moveCount++;
        std::cout << "Move " << moveCount << ": " << "Disk " << Target.top () << " from " << CharSource << " to " << CharTarget << std::endl;
        std::cout << "Peg A:" << std::endl;
        DisplayPegs[0]->display ();
        std::cout << "Peg B:" << std::endl;
        DisplayPegs[1]->display ();
        std::cout << "Peg C:" << std::endl;
        DisplayPegs[2]->display ();
        std::cout << std::endl;
    }
    else {
        Towers (N - 1 , DisplayPegs , Source , Aux , Target , CharSource , CharAux , CharTarget , moveCount);
        Target.push (Source.top ());
        Source.pop ();
        moveCount++;
        std::cout << "Move " << moveCount << ": " << "Disk " << Target.top () << " from " << CharSource << " to " << CharTarget << std::endl;
        std::cout << "Peg A:" << std::endl;
        DisplayPegs[0]->display ();
        std::cout << "Peg B:" << std::endl;
        DisplayPegs[1]->display ();
        std::cout << "Peg C:" << std::endl;
        DisplayPegs[2]->display ();
        std::cout << std::endl;
        Towers (N - 1 , DisplayPegs , Aux , Target , Source , CharAux , CharTarget , CharSource , moveCount);
    }
}


int main () {
    int N;
    std::cout << "Enter the number of disks: ";
    std::cin >> N;
    Stackt<int> pegA , pegB , pegC;
    int moveCount = 0;
    // Initialize pegA with disks
    for (int i = N; i >= 1; --i) {
        pegA.push (i);
    }
    Stackt<int>* pegs[] = { &pegA,&pegB,&pegC };
    char CharPegs[] = { 'A','B','C' };

    Towers (N , pegs , pegA , pegC , pegB , CharPegs[0] , CharPegs[2] , CharPegs[1] , moveCount);

    std::cout << "Number of moves needed: " << moveCount << std::endl;

    return 0;
}
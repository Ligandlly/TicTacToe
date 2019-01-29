//
//  card.hpp
//  card
//
//  Created by 冰凌 on 2019/1/28.
//  Copyright © 2019 lly. All rights reserved.
//

#ifndef card_hpp
#define card_hpp

#include <array>
using namespace std;

class TicTacToe
{
    // NB: all indexes are from 0 to SIZE
public:
    static const unsigned SIZE = 3;
    
    TicTacToe();
    TicTacToe display();
    unsigned int displayResult();
    
    TicTacToe setStep(unsigned stepInput);
    unsigned getStep();
    bool getIfComputerMove();
    void setIfComputerMove(bool input);
    
    // -------------------------
    // these functions blow are created for check if the game is end
    // lly 28th, Jan
    // initiate an array to check
    void initiateRow(unsigned row);
    void initiateCol(unsigned col);
    void initiateDiagonal(unsigned derection); // 1 for "/"; 0 for "\"
    unsigned check(); // check if isWinCache is same
    
    unsigned isEnd(); // 0 for not end yet; 1 for player; 2 for computer; 3 for tie
    // --------------------------
    
    TicTacToe move(unsigned i, unsigned j, unsigned player);
    
    // --------------------------
    // these functions are created for computer to play game
    // --------------------------
    // solution 1
    // lly 28th, Jan
    TicTacToe oneStepLeft();
    TicTacToe dangerous();
    TicTacToe prefer();
    
private:
    array<array<unsigned, SIZE>, SIZE> board;
    array<unsigned, SIZE> cache; // always clean after using
    unsigned step;
    bool ifComputerMove;
};
#endif /* card_hpp */

//
//  card.cpp
//  card
//
//  Created by 冰凌 on 2019/1/28.
//  Copyright © 2019 lly. All rights reserved.
//

#include "card.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

TicTacToe::TicTacToe()
{
    board = { 0 };
    cache = { 0 };
    setStep(2);
    ifComputerMove = false;
 /*
    cout << "Do you want to move first (yes/no) ?" << endl;
    char input[5];
    cin.get(input, 5);
    if (strcmp(input, "yes") == 0)
    {
        
    }
    else if(strcmp(input, "no") == 0)
    {
        
    }
    else
        throw invalid_argument("Enter yes or no only");
  */
}

TicTacToe TicTacToe::display() {
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            cout << (board[i][j] ? (board[i][j]==1 ? 'O' : 'X') : '_') << ' ';
        }
        cout << endl;
    }
    return *this;
}

void TicTacToe::initiateRow(unsigned int row) {
    for(int cacheIndex = 0; cacheIndex < SIZE; cacheIndex++)
            cache[cacheIndex] = board[row][cacheIndex];
}

void TicTacToe::initiateCol(unsigned int col) {
    for(int cacheIndex = 0; cacheIndex < SIZE; cacheIndex++)
            cache[cacheIndex] = board[cacheIndex][col];
}

void TicTacToe::initiateDiagonal(unsigned int derection) {
    if (!derection)
        for(int cacheIndex = 0; cacheIndex < SIZE; cacheIndex++)
            cache[cacheIndex] = board[cacheIndex][cacheIndex];
    else
        for(int cacheIndex = 0; cacheIndex < SIZE; cacheIndex++)
            cache[cacheIndex] = board[cacheIndex][SIZE - 1 - cacheIndex];

}

unsigned TicTacToe::check() {
    unsigned flag = cache[0];
    for (unsigned i = 1; i < SIZE; i++) {
        if (flag != cache[i]) {
            return 0;
        } // end if
    } // end for
    return flag;
}

unsigned int TicTacToe::isEnd() {
    // check rows and columns
    for (unsigned i = 0; i < SIZE; i++) {
        // one row
        initiateRow(i);
        unsigned checkCache1 = check();
        if(checkCache1 == 1){
            return 1;
        }
        if (checkCache1 == 2) {
            return 2;
        }
        cache = {0};
        
        // one column
        initiateCol(i);
        unsigned checkCache2 = check();
        if(checkCache2 == 1){
            return 1;
        }
        if (checkCache2 == 2) {
            return 2;
        }
        cache = {0};
    } // end for
    for (unsigned i = 0; i <= 1; i++) {
        initiateDiagonal(i);
        unsigned checkCache3 = check();
        if(checkCache3 == 1){
            return 1;
        }
        if (checkCache3 == 2) {
            return 2;
        }
        cache = {0};
    }
    
    // at last
    // check for tie
    bool flag = false;
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                flag = true;
                break;
            } // end if
        } // end j for
    } // end i for
    if (!flag) {
        return 3;
    }
    return 0;
}

TicTacToe TicTacToe::move(unsigned int i, unsigned int j, unsigned int player) {
    if(i < SIZE && i >=0 && j < SIZE && j >= 0){
        if(!board[i][j]){
            board[i][j] = player;
            if (player == 2) {
                ifComputerMove = true;
            }
        }
        else
            throw invalid_argument("This room has been occupied");
    }
    else
        throw invalid_argument("Position Out of Range");
    return *this;
}

TicTacToe TicTacToe::setStep(unsigned int stepInput) {
    step = stepInput;
    
    return *this;
}

unsigned int TicTacToe::getStep() {
    return step;
}

TicTacToe TicTacToe::oneStepLeft(){
    // rows and columns first
    for (unsigned i = 0; i < SIZE; i++)
    {
        unsigned count = 0, mark = SIZE;
        initiateRow(i);
        for(unsigned item : cache)
            if (item == 2)
                count++;
        if (count == 2){
            for (unsigned ii = 0; ii < SIZE; ii++){
                if (cache[ii] == 0){
                    mark = ii;
                    move(i, mark, 2);
//                    this->display();
                }
            }
        }
        cache = {}; // row end
        
        initiateCol(i);
        for (unsigned i = 0; i < SIZE; i++)
        {
            count = 0;
            mark = SIZE;
            initiateCol(i);
            for(unsigned item : cache)
                if (item == 2)
                    count++;
            if (count == 2) {
                for (unsigned ii = 0; ii < SIZE; ii++) {
                    if (cache[ii] == 0) {
                        mark = ii;
                        move(mark, i, 2);
//                        this->display();
                    }
                }
            }
        cache = {};
        }
    }
    
    // diagonal line
    initiateDiagonal(0);
    unsigned count = 0, mark = SIZE;
    for(unsigned item : cache){
        if (item == 2) {
            count++;
        }
    }
    if (count == 2) {
        for (unsigned temp = 0; temp < SIZE; temp++) {
            if (cache[temp] == 0) {
                mark = temp;
                move(mark, mark, 2);
            }
        }
    }

    initiateDiagonal(1);
    count = 0;
    mark = SIZE;
    for(unsigned item : cache){
        if (item == 2) {
            count++;
        }
    }
    if (count == 2) {
        for (unsigned temp = 0; temp < SIZE; temp++) {
            if (cache[temp] == 0) {
                mark = temp;
                move(mark, SIZE - 1 - mark, 2);
            }
        }
    }

    cache = {};
    
    return *this;
}

TicTacToe TicTacToe::dangerous(){
    // rows and columns first
    for (unsigned i = 0; i < SIZE; i++)
    {
        unsigned count = 0, mark = SIZE;
        initiateRow(i);
        for(unsigned item : cache)
            if (item == 1)
                count++;
        if (count == 2){
            for (unsigned ii = 0; ii < SIZE; ii++){
                if (cache[ii] == 0){
                    mark = ii;
                    move(i, mark, 2);
                }
            }
        }
        cache = {}; // row end
        
        initiateCol(i);
        for (unsigned i = 0; i < SIZE; i++)
        {
            count = 0;
            mark = SIZE;
            initiateCol(i);
            for(unsigned item : cache)
                if (item == 1)
                    count++;
            if (count == 2) {
                for (unsigned ii = 0; ii < SIZE; ii++) {
                    if (cache[ii] == 0) {
                        mark = ii;
                        move(mark, i, 2);
                    }
                }
            }
            cache = {};
        }
    }
    
    // diagonal line
    initiateDiagonal(0);
    unsigned count = 0, mark = SIZE;
    for(unsigned item : cache){
        if (item == 1) {
            count++;
        }
    }
    if (count == 2) {
        for (unsigned temp = 0; temp < SIZE; temp++) {
            if (cache[temp] == 0) {
                mark = temp;
                move(mark, mark, 2);
            }
        }
    }
    
    initiateDiagonal(1);
    count = 0;
    mark = SIZE;
    for(unsigned item : cache){
        if (item == 1) {
            count++;
        }
    }
    if (count == 2) {
        for (unsigned temp = 0; temp < SIZE; temp++) {
            if (cache[temp] == 0) {
                mark = temp;
                move(mark, SIZE - 1 - mark, 2);
            }
        }
    }
    
    cache = {};
    
    return *this;
}

TicTacToe TicTacToe::prefer() {
    unsigned max = 0;
    unsigned mark[2] = {}; // first row second one is {0,1}
    
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                mark[0] = i; mark[1] = j;
                int score = 0, scoreRow = 0, scoreCol = 0, scoreDia0 = 0, scoreDia1 = 0;
                if ((i == j) || (i + j == 2)) {
                    initiateRow(i);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreRow++;
                        }
                        if (item == 1) {
                            scoreRow = 0;
                            break;
                        }
                    } // end for
                    cache ={};
                    
                    initiateCol(i);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreCol++;
                        }
                        if (item == 1) {
                            scoreCol = 0;
                            break;
                        }
                    } // end for
                    cache = {};
                    
                    initiateDiagonal(0);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreDia0++;
                        }
                        if (item == 1) {
                            scoreDia0 = 0;
                            break;
                        }
                    } // end for
                    cache = {};
                    
                    initiateDiagonal(1);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreDia1++;
                        }
                        if (item == 1) {
                            scoreDia1 = 0;
                            break;
                        }
                    } // end for
                    cache = {};
                    
                }
                else{
                    initiateRow(i);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreRow++;
                        }
                        if (item == 1) {
                            scoreRow = 0;
                            break;
                        }
                    } // end for
                    cache ={};
                    
                    initiateCol(i);
                    for(unsigned item : cache){
                        if (item == 2) {
                            scoreCol++;
                        }
                        if (item == 1) {
                            scoreCol = 0;
                            break;
                        }
                    } // end for
                    cache = {};
                } // end else
                
                if ((score = scoreDia0+scoreCol+scoreRow+scoreCol) > max) {
                    max = score;
                    mark[0] = i;
                    mark[1] = j;
                }
            } // end outer if
        } // end inner for
    } // end outer for
    
    move(mark[0], mark[1], 2);
    return *this;
}

unsigned int TicTacToe::displayResult() {
    unsigned flag = this->isEnd();
    switch (flag) {
        case 0:
            break;
        case 1:
            cout << "You Win!" << endl;
            break;
        case 2:
            cout << "You Lose" << endl;
            break;
        case 3:
            cout << "tie" << endl;
            break;
        default:
            break;
    }
    
    return flag;
}

bool TicTacToe::getIfComputerMove() {
    return ifComputerMove;
}

void TicTacToe::setIfComputerMove(bool input){
    this->ifComputerMove = input;
}

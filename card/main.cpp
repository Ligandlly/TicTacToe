//
//  main.cpp
//  card
//
//  Created by 冰凌 on 2019/1/28.
//  Copyright © 2019 lly. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include "card.hpp"
using namespace std;

int main() {
    unsigned flag = 0;
    unsigned i, j;
    
    cout << "Welcome" << endl;
    TicTacToe game;
    cout << "you move first(enter like: 1 3):" << endl;
    scanf("%d %d", &i, &j);
    i--;
    j--;
    while ( !flag ) {
        try{
            game.move(i, j, 1);

        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            cout << "Please enter again: ";
            scanf("%d %d", &i, &j);
            i--;j--;
            continue;
        }
        game.display();
        cout << "Computer's move:" << endl;
        game.setIfComputerMove(false);
        if (!game.getIfComputerMove()) {
            flag = game.oneStepLeft().displayResult();
            if (game.getIfComputerMove())
                game.display();
            if (flag)
                break;
        }
        if (!game.getIfComputerMove()) {
            flag = game.dangerous().displayResult();
            if (game.getIfComputerMove())
                game.display();
            if (flag)
                break;
        }
        if (!game.getIfComputerMove()) {
            flag = game.prefer().displayResult();
            if (game.getIfComputerMove())
                game.display();
            if (flag)
                break;
        }
        
//        game.display();
        
        cout << "Your Turn : ";
        scanf("%d %d", &i, &j);
        i--;j--;
    }
    
    return 0;
}

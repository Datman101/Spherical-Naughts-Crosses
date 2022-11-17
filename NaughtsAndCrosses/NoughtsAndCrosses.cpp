// NoughtsAndCrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>

class Board {

public:
    std::vector<int> exes;
    std::vector<int> naughts;
    int width = 4;
    int height = 4;

    bool checkXMatch();
    bool checkNMatch();

    void addX(int pos);
    void addN(int pos);

    bool findValue(std::vector<int> vec, int in);

};

bool Board::checkXMatch() {
    
    int check1 = 0;
    int check2 = 0;
    int check3 = 0;
    int check4 = 0;


    for (int j = 1; j <= width; j++) {
        for (int i = 1; i < (height * width); i++) {
            for (int l = 0; l < 2; l++) {
                check1 = j;
                check2 = i + width + j;
                check3 = i + (2 * width) + j + (l);
                check4 = i + (3 * width) + j + (2 * l);

                

                if (check1 > (height * width)) {
                    check1 -= (height * width);
                }
                if (check2 > (height * width)) {
                    check2 -= (height * width);
                }
                if (check3 > (height * width)) {
                    check3 -= (height * width);
                }
                if (check4 > (height * width)) {
                    check4 -= (height * width);
                }

                if (findValue(exes, 16)) {
                    std::cout << "check4: " << check4;
                }

                if ( (this->findValue(exes, check1)) && (this->findValue(exes, check2)) && (this->findValue(exes, check3)) && (this->findValue(exes, check4)) ){
                    return true;
                }
            }
            for (int l = 0; l < 2; l++) {
                check1 = j;
                check2 = j + width - i;
                check3 = (2 * width) + j - i - l;
                check4 = (3 * width) + j - i - (2 * l);



                if (check1 > (height * width)) {
                    check1 -= (height * width);
                }
                if (check2 > (height * width)) {
                    check2 -= (height * width);
                }
                if (check3 > (height * width)) {
                    check3 -= (height * width);
                }
                if (check4 > (height * width)) {
                    check4 -= (height * width);
                }


                if ((this->findValue(exes, check1)) && (this->findValue(exes, check2)) && (this->findValue(exes, check3)) && (this->findValue(exes, check4))) {
                    return true;
                }
            }
        }
    }

    for (int j = 0; j < height; j++) {
        for (int i = 1; i < width; i++) {
            if ((this->findValue(exes, (width * j) + i)) && (this->findValue(exes, (width * j) + i + 1)) && (this->findValue(exes, (width * j) + i + 2))) {
                return true;
            }
        }
    }

    return false;
}
bool Board::checkNMatch() {

    int check1 = 0;
    int check2 = 0;
    int check3 = 0;
    int check4 = 0;


    for (int j = 1; j <= width; j++) {
        for (int i = 1; i < (height * width); i++) {
            for (int l = 0; l < 2; l++) {
                check1 = j;
                check2 = i + width + j;
                check3 = i + (2 * width) + j + (l);
                check4 = i + (3 * width) + j + (2 * l);



                if (check1 > (height * width)) {
                    check1 -= (height * width);
                }
                if (check2 > (height * width)) {
                    check2 -= (height * width);
                }
                if (check3 > (height * width)) {
                    check3 -= (height * width);
                }
                if (check4 > (height * width)) {
                    check4 -= (height * width);
                }


                if ((this->findValue(naughts, check1)) && (this->findValue(naughts, check2)) && (this->findValue(naughts, check3)) && (this->findValue(naughts, check4))) {
                    return true;
                }
            }
            for (int l = 0; l < 2; l++) {
                check1 = j;
                check2 = j + width - i;
                check3 = (2 * width) + j - i - l;
                check4 = (3 * width) + j - i - (2 * l);



                if (check1 > (height * width)) {
                    check1 -= (height * width);
                }
                if (check2 > (height * width)) {
                    check2 -= (height * width);
                }
                if (check3 > (height * width)) {
                    check3 -= (height * width);
                }
                if (check4 > (height * width)) {
                    check4 -= (height * width);
                }


                if ((this->findValue(naughts, check1)) && (this->findValue(naughts, check2)) && (this->findValue(naughts, check3)) && (this->findValue(naughts, check4))) {
                    return true;
                }
            }
        }
    }

    for (int j = 0; j < height; j++) {
        for (int i = 1; i < width; i++) {
            if ((this->findValue(naughts, (width * j) + i)) && (this->findValue(naughts, (width * j) + i + 1)) && (this->findValue(naughts, (width * j) + i + 2))) {
                return true;
            }
        }
    }

    return false;
}

void Board::addX(int pos) {
    exes.push_back(pos);
    return;
}
void Board::addN(int pos) {
    naughts.push_back(pos);
    return;
}

bool Board::findValue(std::vector<int> vec, int in) {
    if (vec.size() > 0) {
        for (int k = 0; k < vec.size(); k++) {
            if (vec[k] == in) {
                return true;
            }
        }
        return false;
    }
    else {
        return false;
    }

}


void format(Board board) {

    std::vector<std::string> vals;
    

    for (int count = 1; count <= (board.height * board.height); count++) {
        if (board.findValue(board.exes, count)) {
            vals.push_back("X");
        }
        else if (board.findValue(board.naughts, count)) {
            vals.push_back("O");
        }
        else {
            vals.push_back(" ");
        }
    }


    for (int i = 0; i < board.height; i++) {
        for (int j = 0; j < board.width; j++) {
            std::cout << vals[(i*board.height)+j] << "| ";
        }
        std::cout << "\n";
    }
}


int main()
{

    Board board;
    bool turn = true;
    int cur = 0;
    bool won = false;

    std::cout << "Welcome to spherical noughts & crosses: It's too complicated for me to explain, so have fun learning :)";
    std::cout << "X plays first, and turns alternate from there: enter the number corresponding to where you want to place your piece, as shown in the grid below....";
    std::cout << "\n 1  | 2  | 3  | 4   \n 5  | 6  | 7  | 8  \n 9  | 10 | 11 | 12\n 13 | 14 | 15 | 16\n";

    

    for (int l = 0; l < 15; l++) {
        std::cout << "Num: ";
        if (turn) {
            std::cin >> cur;
            board.addX(cur);
            turn = false;
        }
        else {
            std::cin >> cur;
            board.addN(cur);
            turn = true;
        }

        format(board);
        
        if (board.checkXMatch()) { std::cout << "X WON"; won = true;  break; }
        else if (board.checkNMatch()) { std::cout << "O WON"; won = true;  break; }


    }
    if (!won) {
        std::cout << "DRAWN";
    }
}
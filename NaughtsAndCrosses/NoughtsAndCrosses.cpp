// NoughtsAndCrosses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>

using namespace boost::archive;

void save(SphereBoard board)
{

    /*Saves the board (serialisation) to archive.txt*/

    std::ofstream file{ "archive.txt" };
    text_oarchive oa{ file };
    oa << board;
}

SphereBoard load()
{

    /*Loads the board (deserialises) from archive.txt*/

    SphereBoard board;
    std::ifstream file{ "archive.txt" };
    text_iarchive ia{ file };
    ia >> board;
    return board;
}

class SphereBoard {

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

    int chaos;
    int xWins = 0;
    int nWins = 0;

};

bool SphereBoard::checkXMatch() {
    
    /*Checks if Crosses have won the match*/

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
bool SphereBoard::checkNMatch() {

    /*Checks if Naughts have won the match*/

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

void SphereBoard::addX(int pos) {
    /*Adds a Cross to the board*/
    exes.push_back(pos);
    return;
}
void SphereBoard::addN(int pos) {
    /*Adds a Naught to the board*/
    naughts.push_back(pos);
    return;
}

bool SphereBoard::findValue(std::vector<int> vec, int in) {
    /*Checks if the vector contains a specified integer*/
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


void formatAndPrint(SphereBoard board) {

    /*Formats and prints the values of the board*/

    std::vector<std::string> vals;
    

    for (int count = 1; count <= (board.height * board.height); count++) {
        if (board.findValue(board.exes, count)) {
            vals.push_back("\u001b[31mX\u001b[0m");
        }
        else if (board.findValue(board.naughts, count)) {
            vals.push_back("\u001b[34mO\u001b[0m");
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

    SphereBoard board;
    bool turn = true;
    bool won = false;
    int cur;
    bool shuffle = false;
    bool shuffle2 = false;
    bool y = false;

    std::cout << "Do you have a saved game (1/0): ";
    
    std::ofstream ofs("archive.txt");
    
    std::cin >> y;

    if (y == 1) {
        board = load();
    }
    else {
        std::cout << "Welcome to linear/spherical noughts & crosses: It's too complicated for me to explain, so have fun learning :)\n";
        std::cout << "X plays first, and turns alternate from there: enter the number corresponding to where you want to place your piece, as shown in the grid below....";
        std::cout << "\n 1  | 2  | 3  | 4   \n 5  | 6  | 7  | 8  \n 9  | 10 | 11 | 12\n 13 | 14 | 15 | 16\n";
        std::cout << "On a scale of 1-3, how much chaos would you like this to be?: ";
        std::cin >> board.chaos;

        switch (board.chaos) {
            default:
                break;
            case 1:
                break;
            case 2:
                shuffle = true;
                break;
            case 3:
                shuffle = true;
                shuffle2 = true;
                break;
       }
    }

    for (int l = 0; l < 15; l++) {
        std::cout << "Num: ";
        std::cin >> cur;
        while(cur > 16 or cur < 1) {
            std::cout << "Invalid number: please enter a number between 1 & 16\n";
            std::cin >> cur;
        }
        if (turn) {
            board.addX(cur);
            turn = false;
            //if it is Xs turn, it places a cross in the grid, and alternates a bool so that the next go is Os
        }
        else {
            board.addN(cur);
            turn = true;
            //if it is Os turn, it places a cross in the grid, and alternates a bool so that the next go is Xs

        }

       

        
        if (board.checkXMatch()) { std::cout << "X WON"; won = true; board.xWins += 1; save(board); break; }
        else if (board.checkNMatch()) { std::cout << "O WON"; won = true; board.nWins += 1; save(board); break; }

        if (shuffle && (!shuffle2)) {
            for (int i = 0; i < board.exes.size(); i++) {
                if (board.exes[i] != 16) {
                    board.exes[i] += rand() % 10;;
                }
                else {
                    board.exes[i] -= 15;
                }
            }
            for (int i = 0; i < board.naughts.size(); i++) {
                if (board.naughts[i] != 16) {
                    board.naughts[i] += rand() % 10;;
                }
                else {
                    board.naughts[i] -= 15;
                }
            }
            formatAndPrint(board);

        }

        if (shuffle && shuffle2) {
            for (int i = 0; i < board.exes.size(); i++) {
                if (board.exes[i] != 16) {
                    board.exes[i] += rand() % 10;
                }
                else {
                    board.exes[i] -= 15;
                }
            }
            for (int i = 0; i < board.naughts.size(); i++) {
                if (board.naughts[i] != 16) {
                    board.naughts[i] += rand() % 10;
                }
                else {
                    board.naughts[i] -= 15;
                }
            }
        }
        
        else {
            formatAndPrint(board);
        }


    }

    if (!won) {
        std::cout << "DRAWN";
    }

}
/*Name: Sayuri Shrestha
Class: CSCI 2170
Professor: Robert Smith
Description: The new implementations in this program will allow the minecraft game to become more engaging with the user
*/

#include "Board.h"
#include <iostream>

int main() {
     int width, height, numMines;
     std::cout << "Enter Rows, Cols, and Mines: ";
     std::cin >> width >> height >> numMines;

     Board board(width, height, numMines);
     board.display();

    while (!board.gameOver() && !board.gameWon()) {
        int x, y;
        std::cout << "Enter a row and column to dig: ";
        std::cin >> x >> y;

        if (!board.tileReveal(x, y)) {
            if (board.gameOver()) {
                std::cout << "YOU LOSE!!!!!!" << std::endl;
            } else if (board.gameWon()) {
                std::cout << "YOU WIN!!!!!!!" << std::endl;
            }
            break;
        }

        board.display();
    }

    std::cout << "Final Board:\n";
    board.display();
    return 0;
}
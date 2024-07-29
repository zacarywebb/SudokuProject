
#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class Tile{
public:
    float xPos;
    float yPos;
    bool hasFlag;
    bool hasMine;
    vector<Tile*> adjacentTiles;
    int number;
    sf::Sprite sprite;
    bool isRevealed;
    int row;
    int col;
    bool mineRevealed;

    Tile(float x, float y){
        //Sets initial values for a new tile object
        hasFlag = false;
        hasMine = false;
        number = 0;
        xPos = x;
        yPos = y;
        isRevealed = false;
        mineRevealed = false;
    }

};


#endif //MINESWEEPER_TILE_H

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include <iostream>
#include <vector>
#include <fstream>
#include "tile.h"
#include "texture.h"
#include <string>
#include "timer.h"
using namespace std;



class Board{
private:
    int height;
    int width;
    int tileCount;
    int mineCount;
    int columns;
    int rows;
    int flagCount;


public:
    vector<vector<Tile>> boardVect;
    bool isPaused;
    bool leaderboardDisplayed;
    bool gameWon;
    bool gameLost;
    Board(int numCols, int numRows, int numMines){
        rows = numRows;
        columns = numCols;
        width = numCols * 32;
        height = (numRows * 32) + 100;
        tileCount = numCols * numRows;
        mineCount = numMines;
        flagCount = 0;
        isPaused = false;
        leaderboardDisplayed = false;
        gameWon = false;
        gameLost = false;

        for(int i = 0; i < numRows; i++){
            vector<Tile> rowVect;
            for(int j = 0; j < numCols; j++){
                rowVect.push_back(Tile(j * 32, i * 32));
                rowVect[j].row = i;
                rowVect[j].col = j;
            }
            boardVect.push_back(rowVect);
        }
    }


    int countMines(Tile* tilePtr){
        int count = 0;
        for(int i = 0; i < tilePtr -> adjacentTiles.size(); i++){
            if(tilePtr -> adjacentTiles[i]->hasMine){
                count += 1;
            }
        }
        return count;
    }

    void generateBoard(Tile* tilePtr){
        //Add to each tile's adjacent tiles vector
        for(int i = 0; i < boardVect.size(); i++){
            for(int j = 0; j < boardVect[i].size(); j++){
                Tile* current = &boardVect[i][j];

                //Diagonal top left tile
                if(i > 0 and j > 0){
                    current -> adjacentTiles.push_back(&boardVect[i - 1][j - 1]);
                }

                //Directly above tile
                if(i > 0){
                    current -> adjacentTiles.push_back(&boardVect[i - 1][j]);
                }

                //Diagonal top right tile
                if(i > 0 and j < columns - 1){
                    current -> adjacentTiles.push_back(&boardVect[i - 1][j + 1]);
                }

                //Tile adjacent on right
                if(j < columns - 1){
                    current -> adjacentTiles.push_back(&boardVect[i][j + 1]);
                }

                //Bottom right tile
                if(j < columns - 1 and i < rows - 1){
                    current -> adjacentTiles.push_back(&boardVect[i + 1][j + 1]);
                }

                //Tile underneath
                if(i < rows - 1){
                    current -> adjacentTiles.push_back(&boardVect[i + 1][j]);
                }

                //Bottom left tile
                if(i < rows - 1 and j > 0){
                    current -> adjacentTiles.push_back(&boardVect[i + 1][j - 1]);
                }

                //Adjacent tile on left
                if(j > 0){
                    current -> adjacentTiles.push_back(&boardVect[i][j - 1]);
                }

            }
        }

        int count = 0;
        //Add mines to random tiles
        while(count < mineCount){
            int randomCol = rand() % columns;
            int randomRow = rand() % rows;

            if(!boardVect[randomRow][randomCol].hasMine && tilePtr != &boardVect[randomRow][randomCol]){
                boardVect[randomRow][randomCol].hasMine = true;
                count += 1;
                //If the random tile is adjacent to start tile, remove mine (so start tile is a blank square)
                for(int i = 0; i < tilePtr -> adjacentTiles.size(); i++){
                    if(tilePtr -> adjacentTiles[i] -> hasMine){
                        tilePtr -> adjacentTiles[i] -> hasMine = false;
                        count -= 1;
                    }
                }
            }
        }

        //Add to each tile's number (of adjacent mines)
        for(int i = 0; i < boardVect.size(); i++){
            for(int j = 0; j < boardVect[i].size(); j++){
                //If the tile does not have a mine, change its number to the number of adjacent mines
                if(!boardVect[i][j].hasMine){
                    boardVect[i][j].number = countMines(&boardVect[i][j]);
                }
            }
        }
    }

    void recursiveRevealing(Tile* currentTile){
        //if tile is a number, reveal and return
        if(currentTile -> number != 0 && !currentTile -> hasMine && !currentTile -> hasFlag){
            currentTile -> isRevealed = true;
            return;
        }
        //if tile is mine or has flag, do not reveal and return
        else if(currentTile -> hasMine || currentTile -> hasFlag || currentTile -> isRevealed){
            return;
        }
        //Tile is blank, recursively call function for each adjacent tile
        else{
            currentTile -> isRevealed = true;
            for(int i = 0; i < currentTile -> adjacentTiles.size(); i++){
                recursiveRevealing(currentTile -> adjacentTiles[i]);
            }
        }
    }

    void drawButtons(Texture& textures, sf::RenderWindow& window){
        //Create sprites for each button and draw them to the window

        //Happy face
        sf::Sprite happy;
        happy.setTexture(textures.getTexture("files/images/face_happy.png"));
        happy.setPosition(((columns/2.0) * 32) - 32, 32 * (rows + 0.5));
        window.draw(happy);

        //Debug button
        sf::Sprite debug;
        debug.setTexture(textures.getTexture("files/images/debug.png"));
        debug.setPosition((columns * 32) - 304, 32 * (rows + 0.5));
        window.draw(debug);

        //Pause button
        sf::Sprite pause;
        pause.setTexture(textures.getTexture("files/images/pause.png"));
        pause.setPosition((columns * 32) - 240, 32 * (rows + 0.5));
        window.draw(pause);

        //Leaderboard button
        sf::Sprite leaderboard;
        leaderboard.setTexture(textures.getTexture("files/images/leaderboard.png"));
        leaderboard.setPosition((columns * 32) - 176, 32 * (rows + 0.5));
        window.draw(leaderboard);

        //Add counter digits
        int number = mineCount - flagCount;
        string counterString = to_string(number);


        int xPos = 33; // Starting x position
        int yPos = 32 * rows + 16; // y position

        //Handle negative numbers
        if (number < 0) {
            //Remove negative sign from string
            counterString = counterString.substr(1);

            //Draw negative sign sprite
            sf::Sprite minus;
            minus.setTexture(textures.getTexture("files/images/digits.png"));
            minus.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32)); // '-' sprite
            minus.setPosition(12, yPos);
            window.draw(minus);
        }
        //Add leading zeros
        while (counterString.length() < 3) {
            counterString = "0" + counterString;
        }

        for (char digit : counterString) {
            sf::Sprite digitSprite;
            digitSprite.setTexture(textures.getTexture("files/images/digits.png"));
            int digitValue = digit - '0'; // Convert char to int
            digitSprite.setTextureRect(sf::IntRect(digitValue * 21, 0, 21, 32)); // Set sprite rect for digit
            digitSprite.setPosition(xPos, yPos);
            window.draw(digitSprite);
            xPos += 21;


        }
    }


    void drawBoard(Texture& textures, sf::RenderWindow& window, Timer& timer){
        //If game is paused
        if(isPaused || leaderboardDisplayed){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    //Draw revealed tiles on board
                    sf::Sprite revealed;
                    revealed.setTexture(textures.getTexture("files/images/tile_revealed.png"));
                    revealed.setPosition(j * 32, i * 32);
                    window.draw(revealed);
                }
            }
            //Draw buttons and add play button
            drawButtons(textures, window);
            sf::Sprite play;
            play.setTexture(textures.getTexture("files/images/play.png"));
            play.setPosition((columns * 32) - 240, 32 * (rows + 0.5));
            window.draw(play);
            return;

        }



        flagCount = 0;
        for(int i = 0; i < boardVect.size(); i++){
            for(int j = 0; j < boardVect[i].size(); j++){
                //Create covered tile sprite
                if(!boardVect[i][j].isRevealed){
                    boardVect[i][j].sprite.setTexture(textures.getTexture("files/images/tile_hidden.png"));
                    boardVect[i][j].sprite.setPosition(j * 32, i * 32);
                    //Check to see if flag is placed
                    if(boardVect[i][j].hasFlag){
                        flagCount += 1;
                        sf::Sprite flag;
                        flag.setTexture(textures.getTexture("files/images/flag.png"));
                        flag.setPosition(j * 32, i * 32);
                        window.draw(boardVect[i][j].sprite);
                        window.draw(flag);
                    }
                    //Draw bomb over covered tile
                    else if(boardVect[i][j].mineRevealed){
                        sf::Sprite bomb;
                        bomb.setTexture(textures.getTexture("files/images/mine.png"));
                        bomb.setPosition(j * 32, i * 32);
                        window.draw(boardVect[i][j].sprite);
                        window.draw(bomb);
                    }
                    else{
                        window.draw(boardVect[i][j].sprite);
                    }

                }
                else{
                    //Create revealed tile sprite
                    boardVect[i][j].sprite.setTexture(textures.getTexture("files/images/tile_revealed.png"));
                    boardVect[i][j].sprite.setPosition(j * 32, i * 32);
                    if(boardVect[i][j].hasMine){
                        //Create bomb sprite and draw it on top of revealed tile sprite
                        sf::Sprite bomb;
                        bomb.setTexture(textures.getTexture("files/images/mine.png"));
                        bomb.setPosition(j * 32, i * 32);
                        window.draw(boardVect[i][j].sprite);
                        window.draw(bomb);
                    }
                    else if(boardVect[i][j].number != 0){
                        string filename = "files/images/number_";
                        for(int s = 1; s < 9; s++){
                            if(boardVect[i][j].number == s){
                                filename += to_string(s);
                            }
                        }
                        filename += ".png";
                        //Create sprite for number texture
                        sf::Sprite number;
                        number.setTexture(textures.getTexture(filename));
                        number.setPosition(j * 32, i * 32);
                        window.draw(boardVect[i][j].sprite);
                        window.draw(number);

                    }
                    else{
                        //If no bomb, draw revealed square and number or ADD RECURSIVE FUNCTION
                        window.draw(boardVect[i][j].sprite);
                    }
                }

            }
        }
        //Draw buttons
        drawButtons(textures, window);


        timer.displayTimer(window, textures, boardVect[1].size(), boardVect.size(), timer.elapsedMinutes(), timer.elapsedSecondsRemainder());



    }

    string getButton(int x, int y, Texture textures){
        //Happy face
        sf::Sprite happy;
        happy.setTexture(textures.getTexture("files/images/face_happy.png"));
        happy.setPosition(((columns/2.0) * 32) - 32, 32 * (rows + 0.5));
        sf::Vector2f buttonPosition = happy.getPosition();
        sf::Vector2f buttonSize(happy.getGlobalBounds().width, happy.getGlobalBounds().height);

        if (x >= buttonPosition.x && x <= buttonPosition.x + buttonSize.x &&
            y >= buttonPosition.y && y <= buttonPosition.y + buttonSize.y) {
            return "happy";
        }

        //Debug button
        sf::Sprite debug;
        debug.setTexture(textures.getTexture("files/images/debug.png"));
        debug.setPosition((columns * 32) - 304, 32 * (rows + 0.5));
        buttonPosition = debug.getPosition();
        buttonSize.x = debug.getGlobalBounds().width;
        buttonSize.y = debug.getGlobalBounds().height;

        if (x >= buttonPosition.x && x <= buttonPosition.x + buttonSize.x &&
            y >= buttonPosition.y && y <= buttonPosition.y + buttonSize.y) {
            return "debug";
        }

        //Pause button
        sf::Sprite pause;
        pause.setTexture(textures.getTexture("files/images/pause.png"));
        pause.setPosition((columns * 32) - 240, 32 * (rows + 0.5));
        buttonPosition = pause.getPosition();
        buttonSize.x = pause.getGlobalBounds().width;
        buttonSize.y = pause.getGlobalBounds().height;

        if (x >= buttonPosition.x && x <= buttonPosition.x + buttonSize.x &&
            y >= buttonPosition.y && y <= buttonPosition.y + buttonSize.y) {
            return "pause";
        }

        //Leaderboard button
        sf::Sprite leaderboard;
        leaderboard.setTexture(textures.getTexture("files/images/leaderboard.png"));
        leaderboard.setPosition((columns * 32) - 176, 32 * (rows + 0.5));

        buttonPosition = leaderboard.getPosition();
        buttonSize.x = leaderboard.getGlobalBounds().width;
        buttonSize.y = leaderboard.getGlobalBounds().height;

        if (x >= buttonPosition.x && x <= buttonPosition.x + buttonSize.x &&
            y >= buttonPosition.y && y <= buttonPosition.y + buttonSize.y) {
            return "leaderboard";
        }
        return "";

    }

    void debug(Texture textures){
        //Reveal all mines
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(boardVect[i][j].hasMine){
                    boardVect[i][j].mineRevealed = !boardVect[i][j].mineRevealed;
                }
            }
        }
    }

    void reset(){
        //Reset board
        for(int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                boardVect[i][j] = Tile(i * 32, j * 32);
            }
        }
    }

    bool checkWin(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                //If a tile is covered and doesn't have a mine
                if(!boardVect[i][j].isRevealed && !boardVect[i][j].hasMine){
                    return false;
                }

            }
        }
        for(int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                //Add flag to all mines not yet covered
                if(boardVect[i][j].hasMine){
                    boardVect[i][j].hasFlag = true;
                }
            }
        }
        return true;
    }

    bool checkLose(Tile& tile){
        if(tile.hasMine){
            gameLost = true;
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(boardVect[i][j].hasMine){
                        boardVect[i][j].mineRevealed = true;
                        boardVect[i][j].isRevealed = true;
                    }
                }
            }
            return true;
        }
        return false;

    }

    void displaySadorWin(sf::Sprite& sprite, sf::RenderWindow& gameWindow, Texture& textureManager, int colCount, int rowCount, string face){
        if(face == "win"){
            sprite.setTexture(textureManager.getTexture("files/images/face_win.png"));
        }
        else{
            sprite.setTexture(textureManager.getTexture("files/images/face_lose.png"));
        }
        sprite.setPosition(((colCount/2.0) * 32) - 32, 32 * (rowCount + 0.5));
        gameWindow.draw(sprite);
        gameWindow.display();
    }


};





#endif //MINESWEEPER_BOARD_H

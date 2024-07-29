#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>
#include "board.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "timer.h"
#include <algorithm>
using namespace std;

void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

vector<string> readLeaderboard(){
    ifstream file("files/leaderboard.txt");

    string line;
    vector<string> data;

    while(getline(file, line)){
        stringstream ss(line);
        while (getline(ss, line, ',')) {
            data.push_back(line);
        }
    }
    file.close();
    return data;

}

void displayLeaderboard(Texture& textures, sf::RenderWindow& gameWindow, Board& board, int width, int height, vector<string>& data, Timer& gameTimer) {
    sf::RenderWindow leaderboardWindow(sf::VideoMode(width, height), "Leaderboard");

    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(width / 2, (height / 2) - 120);

    string displayText = "Leaderboard\n\n";
    int rank = 1;
    //Iterate through the data vector storing leaderboard data and display text based on rank
    for (int i = 0; i < data.size(); i += 2) {
        string string_rank = to_string(rank);
        displayText += string_rank + ".\t" + data[i] + "\t" + data[i + 1] + "\n\n";
        rank += 1;
    }

    text.setString(displayText);
    // Center align the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f));


    while (leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                board.leaderboardDisplayed = false;
                if(!board.gameWon && !board.gameLost && !board.isPaused){
                    gameTimer.resume();
                }

                leaderboardWindow.close();
            }

        }
        leaderboardWindow.clear(sf::Color::Blue);
        leaderboardWindow.draw(text);
        leaderboardWindow.display();
    }
}

void editLeaderboard(const string& timeName) {
    ifstream file("files/leaderboard.txt");


    vector<string> data;
    string line;
    //Read data into a vector
    while (getline(file, line)) {
        data.push_back(line);
    }
    file.close();

    data.push_back(timeName);
    sort(data.begin(), data.end());
    ofstream writeFile("files/leaderboard.txt");

    for(int i = 0; i < 5; i++){
        writeFile << data[i] << endl;
    }
    writeFile.close();
}

string displayWelcomeWindow(int colCount, int rowCount){
    sf::RenderWindow window(sf::VideoMode(colCount * 32, (rowCount * 32) + 100), "Minesweeper", sf::Style::Close);
    window.clear(sf::Color::Blue); // Set background color

    // Load font
    sf::Font font;
    font.loadFromFile("files/font.ttf");


    // Create text objects
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcomeText, window.getSize().x / 2, window.getSize().y / 2 - 150);


    sf::Text enterNameText("Enter your name:", font, 20);
    enterNameText.setFillColor(sf::Color::White);
    setText(enterNameText, window.getSize().x / 2, window.getSize().y / 2 - 75);


    sf::Text nameText("", font, 18);
    nameText.setFillColor(sf::Color::Yellow);
    setText(nameText, window.getSize().x / 2, window.getSize().y / 2 - 45);


    // Step 4: Display text objects
    window.draw(welcomeText);
    window.draw(enterNameText);
    window.draw(nameText);
    window.display();

    // user input
    string userName;
    char input;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close window
                return "";
            }
            else if (event.type == sf::Event::TextEntered) {
                input = static_cast<char>(event.text.unicode);
                if (input == '\b') { // Backspace
                    if (!userName.empty()) {
                        userName.pop_back();
                    }
                }
                else if (isalpha(input) and userName.size() < 10) { // Alphabetic characters
                    userName += tolower(input); // Convert to lowercase
                    if (userName.size() == 1) {
                        userName[0] = toupper(userName[0]); // Capitalize first letter
                    }
                }
                nameText.setString(userName + "|"); // Update displayed text with cursor
                setText(nameText, window.getSize().x / 2, window.getSize().y / 2 - 45); // Center username text
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) { // Enter key
                    if (!userName.empty()) {
                        // Close window
                        window.close();
                        return userName;
                    }
                }
            }
        }

        //Redraw the window with the updated text
        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(nameText);
        window.display();
    }
}

void loadTextures(Texture& textureManager){
    textureManager.loadTexture("files/images/debug.png");
    textureManager.loadTexture("files/images/digits.png");
    textureManager.loadTexture("files/images/face_happy.png");
    textureManager.loadTexture("files/images/face_lose.png");
    textureManager.loadTexture("files/images/face_win.png");
    textureManager.loadTexture("files/images/flag.png");
    textureManager.loadTexture("files/images/leaderboard.png");
    textureManager.loadTexture("files/images/mine.png");
    textureManager.loadTexture("files/images/number_1.png");
    textureManager.loadTexture("files/images/number_2.png");
    textureManager.loadTexture("files/images/number_3.png");
    textureManager.loadTexture("files/images/number_4.png");
    textureManager.loadTexture("files/images/number_5.png");
    textureManager.loadTexture("files/images/number_6.png");
    textureManager.loadTexture("files/images/number_7.png");
    textureManager.loadTexture("files/images/number_8.png");
    textureManager.loadTexture("files/images/pause.png");
    textureManager.loadTexture("files/images/play.png");
    textureManager.loadTexture("files/images/tile_hidden.png");
    textureManager.loadTexture("files/images/tile_revealed.png");
}

int displayGameBoard(){
    // Set up Window
    ifstream configFile("files/config.cfg");
    int rowCount;
    int colCount;
    int mineCount;
    string line;

    getline(configFile, line);
    colCount = stoi(line);

    getline(configFile, line);
    rowCount = stoi(line);

    getline(configFile, line);
    mineCount = stoi(line);
    configFile.close();

    //Render and display welcome window; store user's name
    string userName = displayWelcomeWindow(colCount, rowCount);
    //If user quits window
    if(userName == ""){
        return 0;
    }

    //load all textures
    Texture textureManager;
    loadTextures(textureManager);

    int winCount = 0;



    //Render game window
    sf::RenderWindow gameWindow(sf::VideoMode(colCount * 32, (rowCount * 32) + 100), "GameWindow", sf::Style::Close);
    gameWindow.setFramerateLimit(30); // Limit to 60 frames per second

    //Create board
    Board gameBoard(colCount, rowCount, mineCount);
    bool firstClick = true;
    gameWindow.clear(sf::Color::White);

    //Initialize timer
    Timer gameTimer;
    gameTimer.start();

    //Display board
    gameBoard.drawBoard(textureManager, gameWindow, gameTimer);
    gameWindow.display();

    //Read leaderboard file
    vector<string> data = readLeaderboard();


    while (gameWindow.isOpen()) {
        sf::Event event;

        while (gameWindow.pollEvent(event) && !gameBoard.leaderboardDisplayed) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close(); // Close window if 'X' is clicked
                return 0;
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);
                // Convert window coordinates to world coordinates
                sf::Vector2f worldPosition = gameWindow.mapPixelToCoords(mousePosition);

                //If the click is on the board and the game isn't paused, won, or lost
                if(worldPosition.y <= rowCount * 32 && !gameBoard.isPaused && !gameBoard.gameWon && !gameBoard.gameLost){
                    // Calculate row and column indices of the clicked tile
                    int row = worldPosition.y / 32;
                    int col = worldPosition.x / 32;

                    //If right click, either add or remove the flag
                    if(event.mouseButton.button == sf::Mouse::Right){
                        //Either add or remove flag
                        gameBoard.boardVect[row][col].hasFlag = !gameBoard.boardVect[row][col].hasFlag;
                    }

                    //Only register left click if the tile doesn't have a flag
                    if(!gameBoard.boardVect[row][col].hasFlag){
                        //If it is left click
                        if(event.mouseButton.button == sf::Mouse::Left){

                            //Only reveal if tile doesn't have a flag
                            if(!gameBoard.boardVect[row][col].hasFlag){
                                gameBoard.boardVect[row][col].isRevealed = true;
                            }

                            if(firstClick){
                                gameBoard.generateBoard(&gameBoard.boardVect[row][col]);
                                firstClick = false;
                            }
                            //If the tile is blank, doesn't have a mine, and doesn't have a flag, call recursive function
                            if(gameBoard.boardVect[row][col].number == 0 && !gameBoard.boardVect[row][col].hasMine &&
                               !gameBoard.boardVect[row][col].hasFlag){
                                gameBoard.boardVect[row][col].isRevealed = false;
                                gameBoard.recursiveRevealing(&gameBoard.boardVect[row][col]);
                            }

                            //Check to see if they lost game
                            if(gameBoard.checkLose(gameBoard.boardVect[row][col])){
                                gameTimer.stop();
                                //If they lost, display window one last time with all mines revealed
                                gameBoard.drawBoard(textureManager, gameWindow, gameTimer);
                                sf::Sprite lose;
                                gameBoard.displaySadorWin(lose, gameWindow, textureManager, colCount, rowCount, "sad");
                                displayLeaderboard(textureManager, gameWindow, gameBoard, colCount * 16, (rowCount * 16) + 50,data, gameTimer);
                            }



                        }

                    }


                }
                    //Else, perform appropriate button operation
                else{
                    string operation = gameBoard.getButton(worldPosition.x, worldPosition.y, textureManager);
                    if(operation == "debug" && !gameBoard.isPaused && !gameBoard.gameWon && !gameBoard.gameLost){
                        //This will only work after first click because game board doesn't load until
                        //after first click (so that first click isn't on a mine)
                        gameBoard.debug(textureManager);

                    }
                    else if(operation == "happy"){
                        firstClick = true;
                        //Reset winCount and gameWon
                        winCount = 0;
                        gameBoard.gameWon = false;
                        gameBoard.gameLost = false;
                        //Reset time
                        gameTimer.start();
                        gameBoard.reset();
                    }
                    else if(operation == "pause" && !gameBoard.gameWon && !gameBoard.gameLost){
                        if(gameBoard.isPaused){
                            gameTimer.resume();
                            gameBoard.isPaused = false;
                        }
                        else{
                            gameTimer.pause();
                            gameBoard.isPaused = true;
                        }

                    }
                    else if(operation == "leaderboard"){
                        //Pause timer if it isn't already
                        if(!gameBoard.isPaused){
                            gameTimer.pause();
                        }

                        //Pause and re-draw
                        gameBoard.leaderboardDisplayed = true;
                        gameBoard.drawBoard(textureManager, gameWindow, gameTimer);
                        if(gameBoard.gameWon){
                            sf::Sprite winFace;
                            gameBoard.displaySadorWin(winFace, gameWindow, textureManager, colCount, rowCount, "win");
                        }
                        else if(gameBoard.gameLost){
                            sf::Sprite sad;
                            gameBoard.displaySadorWin(sad, gameWindow, textureManager, colCount, rowCount, "sad");
                        }
                        gameWindow.display();
                        displayLeaderboard(textureManager, gameWindow, gameBoard, colCount * 16, (rowCount * 16) + 50,data, gameTimer);
                    }
                }
            }
        }

        //Only redraw if leaderboard window isn't open
        if(!gameBoard.leaderboardDisplayed && !gameBoard.gameWon && !gameBoard.gameLost){
            gameWindow.clear(sf::Color::White);
            gameBoard.drawBoard(textureManager, gameWindow, gameTimer);
            gameTimer.displayTimer(gameWindow, textureManager, colCount, rowCount, gameTimer.elapsedMinutes(), gameTimer.elapsedSecondsRemainder());

            //If game is won, display win face
            if(gameBoard.checkWin()){
                gameTimer.stop();


                //Get time and convert to appropriate format
                string minutes = to_string(gameTimer.elapsedMinutes());
                if(minutes.size() == 1){
                    minutes = "0" + minutes;
                }
                string seconds = to_string(gameTimer.elapsedSecondsRemainder());
                if(seconds.size() == 1){
                    seconds = "0" + seconds;
                }
                string timeAndName = minutes + ":" + seconds + ", " + userName + "*";

                //Edit leaderboard if necessary
                editLeaderboard(timeAndName);

                //Create winFace sprite and displaay it
                sf::Sprite winFace;
                gameBoard.drawBoard(textureManager, gameWindow, gameTimer);
                gameBoard.displaySadorWin(winFace, gameWindow, textureManager, colCount, rowCount, "win");
            }


            //Check if the game is won, but with win count and display leaderboard
            if(gameBoard.checkWin() && winCount == 0){
                gameBoard.gameWon = true;

                gameBoard.leaderboardDisplayed = true;

                //Re-read leaderboard
                data = readLeaderboard();
                displayLeaderboard(textureManager, gameWindow, gameBoard, colCount * 16, (rowCount * 16) + 50,data, gameTimer);

                //Iterate winCount so the leaderboard window doesn't constantly open in event loop
                winCount += 1;
            }

            else{
                //If game isn't won or lost, display normally
                gameWindow.display();
            }

        }


    }
}





int main() {

    displayGameBoard();



    return 0;
}

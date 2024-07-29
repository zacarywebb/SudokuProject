#ifndef MINESWEEPER_TIMER_H
#define MINESWEEPER_TIMER_H
#include <iomanip>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "texture.h"
using namespace std;


class Timer{
private:
    chrono::time_point<chrono::steady_clock> start_time;
    chrono::steady_clock::time_point pause_time;
    chrono::time_point<chrono::steady_clock> end_time;
    bool paused;

public:
    chrono::time_point<chrono::steady_clock> pausedTime;
    Timer(){
        paused = false;

    }

    void start() {
        start_time = chrono::steady_clock::now();
        paused = false;
    }

    void pause() {
        if (!paused) {
            pause_time = chrono::steady_clock::now();
            paused = true;
        }
    }

    void resume() {
        if (paused) {
            chrono::steady_clock::time_point now = chrono::steady_clock::now();
            start_time += (now - pause_time);
            paused = false;
        }
    }


    double elapsedSeconds() {
        chrono::time_point<chrono::steady_clock> current_time;
        if (paused) {
            current_time = pause_time; // Use pause time if timer is paused
        } else {
            current_time = chrono::steady_clock::now(); // Otherwise, use current time
        }
        return chrono::duration<double>(current_time - start_time).count();
    }

    int elapsedMinutes() {
        return static_cast<int>(elapsedSeconds() / 60);
    }

    // Get the remaining seconds after elapsed minutes
    int elapsedSecondsRemainder() {
        return static_cast<int>(elapsedSeconds()) % 60;
    }



    void displayTimer(sf::RenderWindow& window, Texture textures, int cols, int rows, int minutes, int secs){
        string mins = to_string(minutes);
        string seconds = to_string(secs);
        if(mins.size() == 1){
            mins = '0' + mins;
        }
        if(seconds.size() == 1){
            seconds = '0' + seconds;
        }

        int xPos = (cols * 32) - 97; // Starting x position
        int yPos = (32 * (rows + 0.5)) + 16; // y position
        //Create sprites for each digit
        for(char digit : mins){
            sf::Sprite dig;
            dig.setTexture(textures.getTexture("files/images/digits.png"));
            int digitValue = digit - '0'; // Convert char to int
            dig.setTextureRect(sf::IntRect(digitValue * 21, 0, 21, 32)); // Set sprite rect for digit
            dig.setPosition(xPos, yPos);
            window.draw(dig);
            xPos += 21;
        }

        xPos = (cols * 32) - 54;
        for(char digit : seconds){
            sf::Sprite dig;
            dig.setTexture(textures.getTexture("files/images/digits.png"));
            int digitValue = digit - '0'; // Convert char to int
            dig.setTextureRect(sf::IntRect(digitValue * 21, 0, 21, 32)); // Set sprite rect for digit
            dig.setPosition(xPos, yPos);
            window.draw(dig);
            xPos += 21;
        }

    }

    void stop() {
        if (!paused) {
            end_time = chrono::steady_clock::now();
        } else {
            resume(); // Resume before stopping to get accurate end time
            end_time = chrono::steady_clock::now();
        }
    }



};


#endif //MINESWEEPER_TIMER_H

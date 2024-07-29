#ifndef MINESWEEPER_TEXTURE_H
#define MINESWEEPER_TEXTURE_H
#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Texture{
private:
    map<string, sf::Texture> textures;

public:
    //loads a texture based on a provided filename
    void loadTexture(const string& filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures[filename] = texture;
        }
    }

    sf::Texture& getTexture(const string& filename) {
        return textures.at(filename);
    }

};

#endif //MINESWEEPER_TEXTURE_H

#include "cpresent/types.h"
#include <cctype>
#include <iostream>
#include <include/utils.hpp>
#include <include/Button.hpp>
#include <include/FallingText.hpp>
#include <SFML/Graphics.hpp>
#include <cpresent/cpresent_wrapper.h>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT ""
#endif

int main() {
    sf::Clock deltaClock;

    // --- Init cipher ---
    cp_key_t currentKey = {0x00000000, 0x0000000000000000};
    set_key(currentKey);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "c-present Tower");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile(PROJECT_ROOT "/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    std::string inputText;
    bool changingKey = false;
    std::string newKeyInput;

    float blinkTimer = 0.0f;
    bool showKeyText = true;
    const float blinkInterval = 0.5f; // seconds

    std::vector<FallingText*> fallingTextVector;

    // UI text objects
    sf::Text title("C-PRESENT ENCRYPTION", font, 32);
    title.setPosition(50, 20);
    title.setFillColor(sf::Color::Cyan);

    sf::Text mainDisplay("", font, 28);
    mainDisplay.setPosition(50, 120);
    mainDisplay.setFillColor(sf::Color::Yellow);

    sf::Text keyDisplay("", font, 24);
    keyDisplay.setPosition(50, 420);
    keyDisplay.setFillColor(sf::Color::Green);

    // Buttons
    sf::Vector2u winSize = window.getSize();
    sf::Vector2f fSize(static_cast<float>(winSize.x), static_cast<float>(winSize.y));
    Button inputready_button(font, "Drop Input", {50, 200}, {200, 50});
    Button changekey_button(font, "Change Key", {50, 500}, {200, 50});
    Button encrypt_button(font, "<- Encrypt", {fSize.x - 250, 200}, {200, 50});
    Button decrypt_button(font, "<- Decrypt", {fSize.x - 250, 300}, {200, 50});

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        blinkTimer += dt;
        if (blinkTimer >= blinkInterval) {
            blinkTimer = 0.0f;
            showKeyText = !showKeyText; // toggle visibility
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Text input
            if (event.type == sf::Event::TextEntered) {
                blinkTimer = 0.0f;
                showKeyText = true;

                if (event.text.unicode == '\b') {  // handle backspace
                    if (changingKey) {
                        if (!newKeyInput.empty()) newKeyInput.pop_back();
                    } else if (!inputText.empty()) {
                        inputText.pop_back();
                    }
                } 
                else if (std::isalnum(event.text.unicode)) {  // allow alphanumeric
                    char c = static_cast<char>(event.text.unicode);
                    if (changingKey) {
                        newKeyInput += c;
                    } else {
                        inputText += c;
                    }
                } 
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {  // Enter
                    if (changingKey) {
                        updateKey(currentKey, newKeyInput);
                        changingKey = false;
                    }
                }
            }

            inputready_button.updateHover(window);
            encrypt_button.updateHover(window);
            decrypt_button.updateHover(window);
            changekey_button.updateHover(window);

            // Button clicks
            if(inputready_button.isBeingClicked(event, window)) {
                fallingTextVector.push_back(new FallingText(font, stringToBlock(inputText)));
            }

            if (encrypt_button.isBeingClicked(event, window)) {
                for (auto& fallingText : fallingTextVector) {
                    if(fallingText->getLevel() == 0){
                        fallingText->setValue(encrypt_block(fallingText->getValue()));
                        fallingText->setLabel(blockToString(fallingText->getValue()));
                        fallingText->nextLevel();
                    }
                }
            }

            if (decrypt_button.isBeingClicked(event, window)) {
                for (auto& fallingText : fallingTextVector) {
                    if(fallingText->getLevel() == 1){
                        fallingText->setValue(decrypt_block(fallingText->getValue()));
                        fallingText->setLabel(blockToString(fallingText->getValue()));
                        fallingText->nextLevel();
                    }
                }
            }

            if(changekey_button.isBeingClicked(event, window)) {
                changingKey = !changingKey;
                if (!changingKey) {
                    updateKey(currentKey, newKeyInput);
                }
                newKeyInput.clear();
            }
        }

        // Update displays
        mainDisplay.setString("Input: " + inputText);
        if (changingKey) {
            keyDisplay.setString("New Key: " + newKeyInput);
        } else {
            keyDisplay.setString("Current Key: " + keyToHexString(currentKey));
        }

        // --- Draw ---
        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(mainDisplay);

        if (!changingKey || (changingKey && showKeyText)) {
            window.draw(keyDisplay);
        }

        inputready_button.draw(window);
        encrypt_button.draw(window);
        decrypt_button.draw(window);
        changekey_button.draw(window);

        for (size_t i = 0; i < fallingTextVector.size(); ) {
            fallingTextVector[i]->update(dt);
            fallingTextVector[i]->draw(window);

            if (fallingTextVector[i]->getPosition().x > window.getSize().x) {
                delete fallingTextVector[i];
                fallingTextVector.erase(fallingTextVector.begin() + i);
            } else {
                ++i;
            }
        }

        window.display();
    }

    return 0;
}
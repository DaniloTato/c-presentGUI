#include <cctype>
#include <iostream>
#include <include/utils.hpp>
#include <include/Button.hpp>
#include <include/FallingText.hpp>
#include <SFML/Graphics.hpp>
#include <cpresent/cpresent_wrapper.h>
#include <iostream>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT "/"
#endif

int main() {
    sf::Clock deltaClock;

    // --- Init cipher ---
    set_key({0x00000000, 0x0000000000000000});

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "c-present Tower");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile(PROJECT_ROOT "/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Data buffers
    std::string inputText;
    std::string cipherText;
    std::string plainText;

    std::vector<FallingText*> fallingTextVector;

    // UI text objects
    sf::Text title("C-PRESENT ENCRYPTION", font, 32);
    title.setPosition(50, 20);
    title.setFillColor(sf::Color::Cyan);

    sf::Text mainDisplay("", font, 28);
    mainDisplay.setPosition(50, 120);
    mainDisplay.setFillColor(sf::Color::Yellow);

    // Simple button (rectangle)
    sf::Vector2u winSize = window.getSize();
    sf::Vector2f fSize(static_cast<float>(winSize.x), static_cast<float>(winSize.y));
    Button inputready_button(font, "Input Ready", {50, 200}, {200, 50});
    Button changekey_button(font, "Chage Key", {50, 500}, {200, 50});
    Button encrypt_button(font, "<- Encrypt", {fSize.x - 250, 200}, {200, 50});
    Button decrypt_button(font, "<- Decrypt", {fSize.x - 250, 300}, {200, 50});

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!inputText.empty())
                        inputText.pop_back();
                } else if (std::isxdigit(event.text.unicode)) {
                    inputText += static_cast<char>(std::toupper(event.text.unicode));
                }
            }

            if(inputready_button.isBeingClicked(event, window)) {
                fallingTextVector.push_back(new FallingText(font, stringToBlock(inputText)));
            }

            if (encrypt_button.isBeingClicked(event, window)) {
                for (auto& fallingText : fallingTextVector) {
                    if(fallingText -> getLevel() == 0){
                        fallingText->setValue(encrypt_block(fallingText -> getValue()));
                        fallingText->setLabel(blockToHexString(fallingText->getValue()));
                        fallingText->nextLevel();
                    }
                }
            }

            if (decrypt_button.isBeingClicked(event, window)) {
                for (auto& fallingText : fallingTextVector) {
                    if(fallingText -> getLevel() == 1){
                        fallingText->setValue(decrypt_block(fallingText -> getValue()));
                        fallingText->setLabel(blockToHexString(fallingText->getValue()));
                        fallingText->nextLevel();
                    }
                }
            }

        }

        mainDisplay.setString("Input: " + inputText);

        // --- Draw ---
        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(mainDisplay);
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
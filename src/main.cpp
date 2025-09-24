#include <iostream>
#include <sstream>
#include <include/utils.hpp>
#include <SFML/Graphics.hpp>
#include <cpresent/cpresent_wrapper.h>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT "/"
#endif

int main() {

    set_key({0x00000000, 0x0000000000000000});

    sf::RenderWindow window(sf::VideoMode(900, 600), "c-present");
    sf::Font font;
    if (!font.loadFromFile(PROJECT_ROOT "/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    bool stringMode = false;

    std::string inputText;
    sf::Text modeLabel("Mode: Block", font, 24);
    modeLabel.setPosition(50, 10);

    sf::Text inputLabel("Input:", font, 24);
    inputLabel.setPosition(50, 50);

    sf::Text inputDisplay("", font, 24);
    inputDisplay.setPosition(150, 50);
    inputDisplay.setFillColor(sf::Color::Yellow);

    std::string encryptedStr = "";
    std::string decryptedStr = "";
    sf::Text outputEncrypt("", font, 24);
    outputEncrypt.setPosition(50, 150);

    sf::Text outputDecrypt("", font, 24);
    outputDecrypt.setPosition(50, 200);

    sf::Text instructions("Type text, press Enter to encrypt/decrypt.\nPress TAB to toggle mode (Block/String).\nPress Esc to quit.", font, 20);
    instructions.setPosition(50, 500);
    instructions.setFillColor(sf::Color::Cyan);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!inputText.empty())
                        inputText.pop_back();
                } else if (((stringMode && event.text.unicode >= 32 && event.text.unicode < 128) || (!stringMode && isxdigit(event.text.unicode))) && event.text.unicode != sf::Keyboard::Tab) {
                    inputText += static_cast<char>(std::toupper(event.text.unicode));
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) { // Enter key
                    if (!inputText.empty()) {
                        if (!stringMode) {
                            // --- Block mode ---
                            block_t inputBlock = fromHex(inputText);
                            block_t enc = encrypt_block(inputBlock);
                            block_t dec = decrypt_block(enc);
                            encryptedStr = "Encrypted: 0x" + toHex(enc);
                            decryptedStr = "Decrypted: 0x" + toHex(dec);
                        } else {
                            // --- String mode ---
                            auto encBlocks = encryptString(inputText);
                            std::ostringstream oss;
                            for (auto b : encBlocks) {
                                oss << "0x" << toHex(b) << " ";
                            }
                            encryptedStr = "Encrypted: " + oss.str();
                            decryptedStr = "Decrypted: " + decryptString(encBlocks);
                        }
                        inputText.clear();
                    }
                } else if (event.key.code == sf::Keyboard::Tab) {
                    inputText.clear();
                    encryptedStr.clear();
                    decryptedStr.clear();
                    stringMode = !stringMode;
                    modeLabel.setString(stringMode ? "Mode: String" : "Mode: Block");
                }
            }
        }

        inputDisplay.setString(inputText);

        outputEncrypt.setString(encryptedStr);
        outputDecrypt.setString(decryptedStr);

        window.clear(sf::Color::Black);
        window.draw(modeLabel);
        window.draw(inputLabel);
        window.draw(inputDisplay);
        window.draw(outputEncrypt);
        window.draw(outputDecrypt);
        window.draw(instructions);
        window.display();
    }

    return 0;
}
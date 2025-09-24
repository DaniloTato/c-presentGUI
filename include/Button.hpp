#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Font& font, const std::string& text,
           sf::Vector2f position, sf::Vector2f size,
           sf::Color bgColor = sf::Color(50, 150, 50),
           unsigned int charSize = 20)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(bgColor);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(charSize);
        label.setFillColor(sf::Color::White);

        // Center text inside button
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
        label.setPosition(
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f
        );
    }

    void setLabel(const std::string& text) {
        label.setString(text);
        // Recenter after changing label
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
        label.setPosition(
            shape.getPosition().x + shape.getSize().x / 2.0f,
            shape.getPosition().y + shape.getSize().y / 2.0f
        );
    }

    void setColor(sf::Color color) {
        shape.setFillColor(color);
    }

    bool isBeingClicked(const sf::Event& event, const sf::RenderWindow& window) const {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(sf::Mouse::getPosition(window));
            return shape.getGlobalBounds().contains(mousePos);
        }
        return false;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(label);
    }

    sf::RectangleShape shape;

private:
    sf::Text label;
};
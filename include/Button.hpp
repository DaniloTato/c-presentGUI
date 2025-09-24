#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Font& font, const std::string& text,
           sf::Vector2f position, sf::Vector2f size,
           sf::Color bgColor = sf::Color(50, 150, 50),
           unsigned int charSize = 20);

    void setLabel(const std::string& text);
    void setColor(sf::Color color);
    bool isBeingClicked(const sf::Event& event, const sf::RenderWindow& window) const;
    void updateHover(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Vector2f normalSize;
    float hoverScale;

    void centerText();
};
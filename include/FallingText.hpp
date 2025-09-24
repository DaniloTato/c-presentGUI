#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cpresent/cpresent_wrapper.h>

#define GRAVITY 30.81f
#define STARTING_FLOOR_POSITION 230.0f

class FallingText {
public:
    FallingText(const sf::Font& font, block_t value);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setFloorPosition(float y) { floor_position = y; }
    int getLevel() const { return current_level; }
    void nextLevel();
    std::string getLabel() const { return text.getString(); }
    void setLabel(const std::string& label);
    void setValue(block_t new_value) { value = new_value; }
    block_t getValue() { return value; }
    sf::Vector2f getPosition() { return position; }

private:
    block_t value;
    int current_level = 0;
    float floor_position = STARTING_FLOOR_POSITION;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f velocity;
};
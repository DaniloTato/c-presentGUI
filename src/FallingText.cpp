#include "include/utils.hpp"
#include <include/FallingText.hpp>

FallingText::FallingText(const sf::Font& font, block_t value) 
: value(value)
{
    text.setFont(font);
    text.setString(blockToHexString(value));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    velocity = {0, 0};
    position = {(WINDOW_WIDTH - text.getGlobalBounds().width)*0.5f, -50};
}

void FallingText::update(float deltaTime) {
    velocity.y += GRAVITY;
    position += velocity * deltaTime;
    text.setPosition(position);

    if (position.y + text.getGlobalBounds().height > floor_position) {
        position.y -= (position.y + text.getGlobalBounds().height - floor_position);
        velocity.y = velocity.y * -0.5f;
    }

    if(current_level == 2){
        velocity.x += 2;
    }
}

void FallingText::draw(sf::RenderWindow& window) {
    window.draw(text);
}

void FallingText::nextLevel(){
    current_level++; 
    floor_position += 100.0f;
    if(current_level == 2){
        floor_position = 530.f;
    }
}

void FallingText::setLabel(const std::string& label) { 
    text.setString(label);
    position.x = (WINDOW_WIDTH - text.getGlobalBounds().width)*0.5f;
}
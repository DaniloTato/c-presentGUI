#include <include/Button.hpp>

Button::Button(const sf::Font& font, const std::string& text,
               sf::Vector2f position, sf::Vector2f size,
               sf::Color bgColor, unsigned int charSize)
    : normalSize(size), hoverScale(1.1f)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(bgColor);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(charSize);
    label.setFillColor(sf::Color::White);

    centerText();
}

void Button::setLabel(const std::string& text) {
    label.setString(text);
    centerText();
}

void Button::setColor(sf::Color color) {
    shape.setFillColor(color);
}

bool Button::isBeingClicked(const sf::Event& event, const sf::RenderWindow& window) const {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(sf::Mouse::getPosition(window));
        return shape.getGlobalBounds().contains(mousePos);
    }
    return false;
}

void Button::updateHover(const sf::RenderWindow& window) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    if (shape.getGlobalBounds().contains(mousePos)) {
        shape.setScale(hoverScale, hoverScale);
    } else {
        shape.setScale(1.f, 1.f);
    }
    centerText();
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

void Button::centerText() {
    sf::FloatRect textBounds = label.getLocalBounds();
    float scaleX = shape.getScale().x;
    float scaleY = shape.getScale().y;
    label.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
    label.setPosition(
        shape.getPosition().x + (shape.getSize().x * scaleX) / 2.0f,
        shape.getPosition().y + (shape.getSize().y * scaleY) / 2.0f
    );
}
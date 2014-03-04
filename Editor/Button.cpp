#include "Button.hpp"
#include <stdio.h>

bool intersects(unsigned x, unsigned width, unsigned int x2, unsigned int width2)
{
    if ((x + width >= x2) && (x <= x2 + width2))
        return true;

    return false;
}

Button::Button(int x, int y, unsigned int width, unsigned int height) : Widget(width, height)
{	
	this->width  = width;
    this->height = height;

    doButton(49, width, height);
}

void Button::setText(std::string text, sf::Color color)
{
    sf::Font tFont;
    tFont.loadFromFile("segoe_ui.ttf");

    sf::Text tText(text, tFont);
    tText.setCharacterSize(14);
    tText.setColor(color);
    tText.setPosition(sf::Vector2f((width / 2) - (tText.getLocalBounds().width / 2), 0));
    widgetTexture.draw(tText); 
}

void Button::doButton(unsigned char color, unsigned int width, unsigned int height)
{
    sf::Texture leftTexture;
    leftTexture.loadFromFile("Widgets\\Button\\Button.png");
    sf::Sprite leftSprite(leftTexture);
    widgetTexture.draw(leftSprite);
    widgetTexture.display();
}

void Button::update(sf::RenderWindow &window)
{

}



/*


 sf::Vertex vertices[] =
    {
        sf::Vertex(sf::Vector2f(0,          1), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(0, height - 1), sf::Color(0, 0, 0)),

        sf::Vertex(sf::Vector2f(1,         0), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(width - 1, 0), sf::Color(0, 0, 0)),

        sf::Vertex(sf::Vector2f(width - 1,          1), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(width - 1, height - 1), sf::Color(0, 0, 0)),

        sf::Vertex(sf::Vector2f(1        , height - 1), sf::Color(0, 0, 0)),
        sf::Vertex(sf::Vector2f(width - 1, height - 1), sf::Color(0, 0, 0)),

        sf::Vertex(sf::Vector2f(1,         2), sf::Color(color + (70 - color), color + (70 - color), color + (70 - color))),
        sf::Vertex(sf::Vector2f(width - 1, 1), sf::Color(color + (70 - color), color + (70 - color), color + (70 - color)))
    };

    widgetTexture.draw(vertices, 10, sf::Lines);

    int j = color;

    for (unsigned int i = 2; i <= height - 2; i++)
    {
        sf::Vertex gradiente[] =
        {
            sf::Vertex(sf::Vector2f(1,         i + 1), sf::Color(j, j, j)),
            sf::Vertex(sf::Vector2f(width - 1, i),     sf::Color(j, j, j)),
        };

        widgetTexture.draw(gradiente, 2, sf::Lines);
        j--;
    }

    int newColor = (49 - (height - 3)) - 7;

    sf::Vertex pixel[] =
    {
        sf::Vertex(sf::Vector2f(1        , 1), sf::Color(48, 48, 48)),
        sf::Vertex(sf::Vector2f(width - 2, 1), sf::Color(48, 48, 48)),

        sf::Vertex(sf::Vector2f(1        , 2), sf::Color(55, 55, 55)),
        sf::Vertex(sf::Vector2f(width - 2, 2), sf::Color(55, 55, 55)),

        sf::Vertex(sf::Vector2f(1,         height - 2), sf::Color(newColor, newColor, newColor)),
        sf::Vertex(sf::Vector2f(width - 2, height - 2), sf::Color(newColor, newColor, newColor))
    };

    widgetTexture.draw(pixel, 6, sf::Points);
*/
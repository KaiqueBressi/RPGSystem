#include "Widget.hpp"
#include <stdio.h>

Widget::Widget(unsigned int width, unsigned int height)
{
	widgetTexture.create(width, height);
	widgetTexture.clear(sf::Color(0, 0, 0, 0));
	widgetTexture.display();    
}

void Widget::draw(sf::RenderWindow &window)
{
	sf::Texture newTex = widgetTexture.getTexture();
    widgetSprite.setTexture(newTex);
	window.draw(widgetSprite);
}
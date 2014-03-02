#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics.hpp>

class Widget
{
	public:
		Widget(unsigned int width, unsigned int height);
		void draw(sf::RenderWindow &window);
		sf::RenderTexture widgetTexture;
	protected:
		sf::Sprite widgetSprite;
};

#endif
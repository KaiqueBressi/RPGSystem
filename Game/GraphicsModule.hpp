#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "ruby.h"
#include "Sprite.hpp"

class GraphicsModule
{
	public:
		GraphicsModule();
		void update();
		void getFPS();

	private:
		sf::RenderWindow window;
		sf::Event event;
};

void graphicsInit();

#endif

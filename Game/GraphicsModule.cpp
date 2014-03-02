#include "GraphicsModule.hpp"
#include "ruby.h"

GraphicsModule::GraphicsModule()
{
	window.create(sf::VideoMode(800, 600), "Window", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void GraphicsModule::update()
{
	while (window.pollEvent(event))
	{		
		if (event.type == sf::Event::Closed)
		{
			window.close();
			rb_iter_break();
		}
	}

	window.clear(sf::Color(120, 120, 120));
	
	for (unsigned int i = 0; i < spriteVector.size(); i++)
		if (spriteVector[i]->visible)
			window.draw(spriteVector[i]->tSprite);
	
	window.display();
}

void GraphicsModule::getFPS()
{
	static int fps = 0;
	static sf::Clock clock;
	fps += 1;

	int millifps = clock.getElapsedTime().asMilliseconds();


	if (millifps >= 1000)
	{
		printf("FPS - %d\n", fps);
		clock.restart();
		fps = 0;
	}
}

extern "C"
{
	GraphicsModule graphicsObj;

	static VALUE graphicsUpdate()
	{
		graphicsObj.update();
		return Qnil;
	}
}

void graphicsInit()
{
	VALUE newGraphics = rb_define_module_under(RGA, "Graphics");
	rb_define_singleton_method(newGraphics, "update", (ruby_method*)&graphicsUpdate, 0);
}
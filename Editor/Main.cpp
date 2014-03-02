#include "Main.hpp"

void GameMain::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window", sf::Style::Close | sf::Style::Titlebar);
	sf::Event event;

	while (window.isOpen()) 
	{
		while (window.pollEvent(event))
		{		
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(120, 120, 120));
		window.display();
	} 
} 

int main(int argc, char *argv[])
{
	GameMain game;
	game.run();
	
	return 0;
}

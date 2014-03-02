#include "Main.hpp"
#include <windows.h>

/*void GameMain::run()
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

		getFPS();
	} 
} */

void GameMain::run()
{
	ruby_init();
  	ruby_init_loadpath();
  	ruby_script("Game");
  	registerClasses();
  	int status;
  	rb_load_protect(rb_str_new2("./Scripts/Main.rb"), 0, &status);

  	if (status)
  	{
  		 VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
  	     rb_warn(StringValuePtr(rbError));
    }

  	ruby_finalize(); 
} 

int main(int argc, char *argv[])
{
	GameMain game;
	game.run();
	
	return 0;
}
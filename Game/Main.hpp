#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>
#include "RegisterClasses.hpp"
#include "ruby.h"

class GameMain
{
	private:
		sf::Clock clock;
	public:
		void run();
};

#endif
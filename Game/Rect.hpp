#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics.hpp>
#include "RegisterClasses.hpp"

class Rect
{
	public:
		Rect(unsigned int left, unsigned int top, unsigned int width, unsigned int height);

		unsigned int left;
		unsigned int top;
		unsigned int width;
		unsigned int height;
		static bool intersects(unsigned x, unsigned width, unsigned int x2, unsigned int width2);
};

void rectInit();

#endif
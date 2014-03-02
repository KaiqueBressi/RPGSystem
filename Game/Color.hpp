#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>
#include "RegisterClasses.hpp"

class Color
{
	public:
		Color(BYTE R, BYTE G, BYTE B, BYTE A);
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE a;
};

void colorInit();

#endif
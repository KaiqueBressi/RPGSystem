#ifndef Bitmap_HPP
#define Bitmap_HPP

#include <vector>

#include "Main.hpp"
#include "Rect.hpp"
#include "Sprite.hpp"
#include "Color.hpp"

class SpriteClass;
class Color;

class Bitmap
{
	public:
		Bitmap(unsigned int width, unsigned int height);
		Bitmap(std::string filename);

		sf::Texture getTexture();
		void drawText(std::string text, float x, float y);
		void drawImage(float x, float y, Bitmap image, unsigned int left, unsigned int top, unsigned int width, unsigned int height);
		void resize(unsigned int width, unsigned int height);
		void clear(Color color);
	private:
		sf::RenderTexture *tRenderTexture;
};

void bitmapInit();

#endif





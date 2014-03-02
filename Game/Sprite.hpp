#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "RegisterClasses.hpp"
#include "GraphicsModule.hpp"
#include "Image.hpp"
#include "Rect.hpp"
#include "Color.hpp"

class Bitmap;
class Rect;

class SpriteClass
{
	public:
		SpriteClass();
		~SpriteClass();
		void dispose();
		void loadFromFile(char * filename);
		void changeImage(Bitmap image);
		void setVisible(bool visible);
		sf::Sprite tSprite;

		bool visible;
	private:
		sf::Texture tTexture;
};

extern std::vector<SpriteClass*> spriteVector;
void spriteInit();

#endif


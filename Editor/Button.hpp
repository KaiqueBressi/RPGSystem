#include "Widget.hpp"

class Button : public Widget
{
	public:
		Button(int x, int y, unsigned int width, unsigned int height);
		
		void update(sf::RenderWindow &window);
		void doButton(unsigned char color, unsigned int width, unsigned int height);
		void setText(std::string text, sf::Color color);

		unsigned int width;
		unsigned int height;
	private:
		bool state;
};
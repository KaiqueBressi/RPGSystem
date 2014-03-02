#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFGUI/SFGUI.hpp>

class GameMain
{
	public:
		void run();
	private:
		sfg::SFGUI m_sfgui;
		sfg::Window::Ptr m_window;
		sfg::Button::Ptr m_button;
};

#endif
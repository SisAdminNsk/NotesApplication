#pragma once
#include "SFML/Graphics.hpp";
#include "SFML/Audio.hpp";
#include "DataStorage.h"

class MenuBase {
public:
	sf::RenderWindow* whereDraw;
	ProgrammState* pg;// contains info about currrent programm state

	sf::Font menuTextFont;
	sf::Text menuText;// text for info menu (not on button)
	sf::Font buttonFont;// text for draw on button's
	sf::SoundBuffer buttonClickSb;
	sf::Sound buttonClickSound;

	sf::View* camera2D;// contain's current view 
public:
	MenuBase();
};
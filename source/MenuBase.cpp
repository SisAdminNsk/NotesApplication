#include "MenuBase.h"

MenuBase::MenuBase()
{
	this->buttonFont.loadFromFile("resources/sansation.ttf");
	this->buttonClickSb.loadFromFile("resources/buttonOnSound.ogg");

	this->buttonClickSound.setBuffer(this->buttonClickSb);

}
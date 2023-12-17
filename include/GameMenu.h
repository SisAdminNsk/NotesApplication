#pragma once
#include "MenuBase.h"
#include "UIObjects.h"

const enum menuState { isOpen = 0, isClose };

class GameMenu : public MenuBase {
private:
	std::vector<std::string> messageOnButtons = { "GENERATE","SOLVE","CLOSE" };
	sf::RectangleShape background;

	std::pair<float, float> buttonSize;
public:
	menuState currentState = isClose;
	std::vector<Button*> menuBtns;

	const float separationScreenFactor = 0.85f; // this factor is needed to divide game screen when user call gameMenu
	const float FaultYpx = 100.f;
	const float FaultYpxPos = -30.f;

	GameMenu(sf::RenderWindow* whereDraw_, ProgrammState* pg_, sf::View* camera2D_);

	void Draw();
	void Update();
};

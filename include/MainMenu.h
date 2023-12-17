#pragma once
#include "MenuBase.h"
#include "UIObjects.h"

const enum MenuChapterState { DefaultState = 0, ControlsChapterState, SettingsChapterState, AuthorsChapterState };

class MainMenuWindow : public MenuBase {
private:
	std::vector<Button*> defaultStateButtons;
	std::vector<std::string> messageOnDefaultButtons = { "PLAY!","CONTROL'S","SETTING'S","AUTHOR'S" };
	std::pair<float, float> menuBtnSize;
	sf::Text menuText;
	std::string menuTextMessage = "It's Dijkstra algorithm visualization\nAt fisrt: Click PLAY\nSelect size, click GENERATE and SOLVE";

public:
	short unsigned MenuState = DefaultState;

	MainMenuWindow(sf::RenderWindow* whereDraw_, ProgrammState* p, sf::View* camera2D_);
	MainMenuWindow();

	class ControlsChapter {
	private:
		std::vector<Button*> controlsStateButtons;
		std::vector<std::string> messageOnControlsButtons;
		sf::Text conrolsChapterText;
	public:
	};

	class SettingsChapter {
	private:
		std::vector<Button*> settingsStateButtons;
		std::vector<std::string> messageOnSettingsButtons;
		sf::Text settingsChapterText;
	public:
	};

	class AboutAuthorsChapter {
	private:
		sf::Text aboutAuthorsChapterText;

	public:
	};

	void Draw();
	void Update();
};

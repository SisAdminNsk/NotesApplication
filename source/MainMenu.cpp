#include "MainMenu.h"

MainMenuWindow::MainMenuWindow(sf::RenderWindow* whereDraw_, ProgrammState* pg_, sf::View* camera2D_)
{
	this->whereDraw = whereDraw_;
	this->pg = pg_;
	this->camera2D = camera2D_;

	this->menuBtnSize = std::make_pair(this->whereDraw->getSize().x / this->messageOnDefaultButtons.size(),
		this->whereDraw->getSize().y / this->messageOnDefaultButtons.size());


	this->defaultStateButtons.push_back(new Button(0.f, 0.f, this->menuBtnSize, &this->buttonFont,
		&this->buttonClickSound, messageOnDefaultButtons[0]));
	this->defaultStateButtons.push_back(new Button(menuBtnSize.first, 0.f, this->menuBtnSize, &this->buttonFont,
		&this->buttonClickSound, messageOnDefaultButtons[1]));
	this->defaultStateButtons.push_back(new Button(2 * menuBtnSize.first, 0.f, this->menuBtnSize, &this->buttonFont,
		&this->buttonClickSound, messageOnDefaultButtons[2]));
	this->defaultStateButtons.push_back(new Button(3 * menuBtnSize.first, 0.f,
		this->menuBtnSize, &this->buttonFont, &this->buttonClickSound, messageOnDefaultButtons[3]));

	this->menuText.setFont(this->buttonFont);
	this->menuText.setString(this->menuTextMessage);
	this->menuText.setCharacterSize(35);
	this->menuText.setFillColor(sf::Color::White);
	this->menuText.setPosition(10, this->menuBtnSize.second + 100);
}

MainMenuWindow::MainMenuWindow() {

}


void MainMenuWindow::Draw() // NOT COMPLETED
{
	this->whereDraw->draw(this->menuText);

	switch (this->MenuState)
	{
	case DefaultState:
		for (const auto& button : this->defaultStateButtons) {
			button->Draw(*this->whereDraw);
		}
		break;
	default:
		break;
	}
}

void MainMenuWindow::Update() // NOT COMPLETED
{
	this->whereDraw->setView(*this->camera2D);

	for (auto& button : this->defaultStateButtons) {
		button->Update(*this->whereDraw);
	}

	switch (this->MenuState)
	{
	case DefaultState:
		if (this->defaultStateButtons[0]->isButtonPressed()) {
			this->pg->currentState = ProgrammState::gameStates::isGameLoop;
		}
		else if (this->defaultStateButtons[1]->isButtonPressed()) {
			this->MenuState = ControlsChapterState;
		}
		else if (this->defaultStateButtons[2]->isButtonPressed()) {
			this->MenuState = SettingsChapterState;
		}
		else if (this->defaultStateButtons[3]->isButtonPressed()) {
			this->MenuState = AuthorsChapterState;
		}
		break;
	case ControlsChapterState:
		// check nested states
		break;
	case AuthorsChapterState:
		// check nested states
		break;
	case SettingsChapterState:
		// check nested states
		break;
	default:
		break;
	}
}

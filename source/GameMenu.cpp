#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow* whereDraw_, ProgrammState* pg_, sf::View* camera2D_)
{
	this->whereDraw = whereDraw_;
	this->pg = pg_;
	this->camera2D = camera2D_;

	this->buttonSize = std::make_pair(this->whereDraw->getSize().x * (1 - this->separationScreenFactor), 100.0f);

	this->background.setSize(sf::Vector2f(this->whereDraw->getSize().x * (1 - this->separationScreenFactor),
		this->whereDraw->getSize().y - this->FaultYpx));
	this->background.setPosition(0.f, 0.f + this->FaultYpxPos);
	this->background.setFillColor(sf::Color::White);

	this->background.setOutlineThickness(5);
	this->background.setOutlineColor(sf::Color::Transparent);

	auto bindMap = this->pg->getControls();
	auto bindBtn1 = bindMap["generate labirint"];

	this->menuBtns.push_back(new Button(0, this->FaultYpxPos, this->buttonSize, &this->buttonFont, &this->buttonClickSound,
		this->messageOnButtons[0] + " '" + bindBtn1 + "' "));

	this->menuBtns.push_back(new Button(0, this->buttonSize.second + this->FaultYpxPos, this->buttonSize, &this->buttonFont,
		&this->buttonClickSound, this->messageOnButtons[1]));
	auto bindBtn3 = bindMap["show game menu"];

	this->menuBtns.push_back(new Button(0, 2 * this->buttonSize.second + this->FaultYpxPos, this->buttonSize, &this->buttonFont,
		&this->buttonClickSound, this->messageOnButtons[2] + " '" + bindBtn3 + "' "));

	// +, - button's and message size will be here;
}

void GameMenu::Draw()
{
	this->whereDraw->draw(this->background);

	for (const auto& button : this->menuBtns) {
		button->Draw(*this->whereDraw);
	}
}

void GameMenu::Update()
{
	for (auto& button : this->menuBtns) {
		button->Update(*this->whereDraw);
	}
}

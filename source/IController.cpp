#include "IController.h"

using namespace Ctrl;

void MenuController::Process(ProgrammState& programmState)
{
	switch (this->event->type)
	{
	case sf::Event::Closed:
		this->UI->whereDraw->close();
		break;
	case::sf::Event::KeyPressed:
		if (this->event->key.code == sf::Keyboard::Escape) {
			this->UI->whereDraw->close();
		}
		break;
	default:
		break;
	}
}

void GameController::Process(ProgrammState& programmState)// all game controller logic
{
	switch (this->event->type)// 2D camera logic here 
	{
	case sf::Event::KeyPressed:
		switch (this->event->key.code)
		{
		case sf::Keyboard::W:
			this->UI->GoUpCamera2D();
			break;
		case::sf::Keyboard::S:
			this->UI->GoDownCamera2D();
			break;
		case sf::Keyboard::D:
			this->UI->GoRightCamera2D();
			break;
		case sf::Keyboard::A:
			this->UI->GoLeftCamera2D();
			break;
		case sf::Keyboard::Space:
			this->UI->GoDefaultCamera2D();
			break;
		case sf::Keyboard::Enter:
			this->model->labirint->GenerateNewLabirint(100, 100);// first step
			this->model->graph->Update(*this->model->labirint);// second step
			this->UI->ReciveModelData();// third step
			this->UI->Update();
			break;
		case sf::Keyboard::M:// go back to menu
			programmState.currentState = ProgrammState::gameStates::isMenu;
			break;
		case sf::Keyboard::Tab:// open inlineGameMenu interface
			this->UI->gameMenu->currentState = menuState::isOpen;
			this->UI->gameCamera2D->setViewport(sf::FloatRect(0.f, 0.f, 0.85f, 1.0f));
			//this->UI->gameCamera2D->setSize(this->model->screen_size.first / 1.15, this->model->screen_size.second);
			programmState.currentInlineState = ProgrammState::inlineGameStates::isGameLoopMenu;
			break;
		case sf::Keyboard::Right:
			this->UI->solutionLabirintSpeedF -= 0.05;
			break;
		case sf::Keyboard::Left:
			this->UI->solutionLabirintSpeedF += 0.05;
			break;
		case sf::Keyboard::E:
			this->UI->Update();
			programmState.currentActionState = ProgrammState::actionGameStates::isSolveLabirintSimulation;
			break;
		default:
			break;
		}
	case sf::Event::MouseWheelMoved:
		if (this->event->mouseWheel.delta == 1) {
			this->UI->ZoomInCamera2D();
		}
		if (this->event->mouseWheel.delta == -1) {
			this->UI->ZoomOutCamera2D();
		}
		break;
	default:
		break;
	}
}

void GameMenuController::Process(ProgrammState& programmState)
{
	switch (this->event->type)
	{
	case sf::Event::KeyPressed:
		switch (this->event->key.code)
		{
		case sf::Keyboard::Tab:// close inlineGameMenu interface
			this->UI->gameCamera2D->setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));// go default
			//this->UI->gameCamera2D->setSize(this->model->screen_size.first, this->model->screen_size.second);
			this->UI->gameMenu->currentState = menuState::isClose;
			programmState.currentInlineState = ProgrammState::inlineGameStates::DefaultState;
			break;

		case sf::Keyboard::W:
			this->UI->GoUpCamera2D();
			break;
		case::sf::Keyboard::S:
			this->UI->GoDownCamera2D();
			break;
		case sf::Keyboard::D:
			this->UI->GoRightCamera2D();
			break;
		case sf::Keyboard::A:
			this->UI->GoLeftCamera2D();
			break;
		case sf::Keyboard::Space:
			this->UI->GoDefaultCamera2D();
			break;
		case sf::Keyboard::Enter:
			this->model->labirint->GenerateNewLabirint(100, 100);// first step
			this->model->graph->Update(*this->model->labirint);// second step
			this->UI->ReciveModelData();// third step
			break;

		default:
			break;
		}
		break;

	case sf::Event::MouseWheelMoved:
		if (this->event->mouseWheel.delta == 1) {
			this->UI->ZoomInCamera2D();
		}
		if (this->event->mouseWheel.delta == -1) {
			this->UI->ZoomOutCamera2D();
		}
		break;

	default:
		break;
	}
}

void BaseController::UpdateEvent(sf::Event* newEvent)
{
	this->event = newEvent;
}


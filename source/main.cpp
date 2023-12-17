////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <Windows.h>
#include "Algorithm_Interface.h"
#include "Model.h"
#include "View.h"
#include "IController.h"
#include "GameMenu.h"
#include "Application.h"

using namespace sf;

int main()
{
	const std::pair<int, int> screen_size = { GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) };
	RenderWindow window(VideoMode(screen_size.first, screen_size.second), "Maze Runner", sf::Style::Fullscreen);

	sf::View gameCamera2D;
	sf::View gameMenuCamera2D;
	sf::View menuCamera2D;

	sf::Clock gameClocks;

	gameCamera2D.reset(sf::FloatRect(0, 0, screen_size.first, screen_size.second));
	gameCamera2D.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	gameCamera2D.setSize(screen_size.first, screen_size.second);

	menuCamera2D.reset(sf::FloatRect(0, 0, screen_size.first, screen_size.second));
	menuCamera2D.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	gameMenuCamera2D.setViewport(sf::FloatRect(0.85f, 0, 0.5f, 1.0f));
	gameMenuCamera2D.setSize(screen_size.first / 2, screen_size.second);

	window.setFramerateLimit(60);

	GraphView materialsObj;

	srand(time(NULL));
	Md::Model::Labirint labirint;
	labirint.GenerateNewLabirint(5, 5);

	Md::Model::Graph graph(labirint, screen_size);

	ProgrammState::SettingsBinds settingsBind;
	ProgrammState::ControlBinds ctrlBind;
	ProgrammState pgState(&ctrlBind, &settingsBind);

	MainMenuWindow menu(&window, &pgState, &menuCamera2D);
	GameMenu gameMenu(&window, &pgState, &gameMenuCamera2D);

	Md::Model model(&labirint, &graph, screen_size);// model work's with graph && labirint;
	Vw::UserView UI(&model, &materialsObj, &window, &gameCamera2D, &gameMenuCamera2D, &menu, &gameMenu
		, &gameClocks);

	Ctrl::MenuController menuController(&model, &UI);
	Ctrl::GameController gameController(&model, &UI);
	Ctrl::GameMenuController gameMenuController(&model, &UI);

	Core app(&model, &UI, &menuController);

	model.labirint->GenerateNewLabirint(6, 6);
	model.graph->Update(*model.labirint);
	UI.ReciveModelData();

	gameClocks.restart();

	while (window.isOpen()) {
		Event event;
		app.controller->UpdateEvent(&event);

		while (window.pollEvent(event)) {
			app.controller->Process(pgState);
		}

		switch (pgState.currentState)
		{
		case ProgrammState::gameStates::isGameLoop:// this target's can be render only in gameloop

			app.controller = &gameController;
			app.UI->UpdateGameCamera();
			app.UI->DrawGraph();

			if (pgState.currentActionState == ProgrammState::actionGameStates::isSolveLabirintSimulation) {
				bool isContinue = app.UI->SimulateLabirintSolution(sf::Color::Green, 1.0f);
				if (!isContinue)
					pgState.currentActionState = ProgrammState::actionGameStates::DefaultState;// mean's stop simulation process
			}

			switch (pgState.currentInlineState)
			{
			case ProgrammState::inlineGameStates::isGameLoopMenu:

				app.controller = &gameMenuController;
				app.UI->UpdateGameMenuCamera();
				app.UI->gameMenu->Draw();
				app.UI->gameMenu->Update();

				break;

			default:
				break;
			}

			break;
		case ProgrammState::gameStates::isMenu:

			app.controller = &menuController;
			app.UI->menu->Draw();
			app.UI->menu->Update();

			break;

		default:
			break;
		}

		window.display();
		window.clear();
	}
}

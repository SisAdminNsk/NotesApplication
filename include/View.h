#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>;
#include "Model.h"
#include "UIObjects.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include <Windows.h>

// THERE ARE NO PROGRAMM LOGIC FUNCTION'S!
// ALL LOGIC ARE INCAPSULATED IN MODEL CLASS
// TO WORK WITH MODEL GO TO MODEL.H FILE.

namespace Vw {
	class UserView {
	private:
		Md::Model* model;

		std::vector <sf::Sprite*> sprites_for_graph;
		std::vector<sf::Sprite> sprites_for_draw;
		Md::Model::Graph::viewData graph_data_from_model;

		sf::RectangleShape labirintBorder;

		void initLabirintBorders();

		std::vector<int> path;
		std::vector<int> GetLabirintSolution();
	public:
		UserView(Md::Model* model_, GraphView* renderTargets, sf::RenderWindow* whereDraw_,
			sf::View* camera2D_, sf::View* gameCamera2D_, MainMenuWindow* menu_, GameMenu* gameMenu_, sf::Clock* pgClock) : model(model_),
			whereDraw(whereDraw_), gameCamera2D(camera2D_), gameMenuCamera2D(gameCamera2D_), gameMenu(gameMenu_), menu(menu_), 
			programmClock(pgClock)
		{
			std::vector<sf::Sprite*> sprites_for_draw_ = { &renderTargets->getSprite(renderTargets->EmptySprite),
			&renderTargets->getSprite(renderTargets->RightSprite),&renderTargets->getSprite(renderTargets->BottomSprite),
			&renderTargets->getSprite(renderTargets->RbSprite) };

			sprites_for_graph = sprites_for_draw_;

			for (auto& sprite : sprites_for_graph)
				sprite->setColor(sf::Color::Blue);

			initLabirintBorders();
		}
		
		UserView();

		void ReciveModelData();
		void SentDataToController();
		void Update();
		void DrawGraph() const; // draw interface based on data_for_draw

		float zoomCofficientIn = 0.99f;
		float zoomCofficientOut = 1.01f;
		float cameraSpeedF = 20.0f;

		void GoLeftCamera2D();
		void GoRightCamera2D();
		void GoUpCamera2D();
		void GoDownCamera2D();
		void GoDefaultCamera2D();
		void ZoomInCamera2D();
		void ZoomOutCamera2D();
		void UpdateGameCamera();
		void UpdateGameMenuCamera();
		
		bool SimulateLabirintSolution(sf::Color spriteColor, float speedCofficient);

		MainMenuWindow* menu;
		GameMenu* gameMenu;

		sf::RenderWindow* whereDraw;
		sf::View* gameCamera2D;// open game camera interface for optimization
		sf::View* gameMenuCamera2D;

		sf::Clock* programmClock;

		float solutionLabirintSpeedF = 0.1f;
	};
};


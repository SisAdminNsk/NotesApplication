#pragma once
#include "Model.h"
#include "View.h"
#include "DataStorage.h"

namespace Ctrl {

	class IController {
	public:
		virtual void Process(ProgrammState& programmState) = 0;
	};

	class BaseController : public IController {
	protected:
		Md::Model* model;
		Vw::UserView* UI;
		sf::Event* event;
	public:
		BaseController(Md::Model* model_, Vw::UserView* UI_) : model(model_),
			UI(UI_) {}
		void UpdateEvent(sf::Event* newEvent);
	};


	class MenuController : public BaseController { // define the action's that can be do in Menu
	public:
		void Process(ProgrammState& programmState) override;

		MenuController(Md::Model* model_, Vw::UserView* UI_) : BaseController(model_, UI_) {}
	};

	class GameController : public BaseController {// define the action's that can be do in Game cicle
	public:
		void Process(ProgrammState& programmState) override;

		GameController(Md::Model* model_, Vw::UserView* UI_) : BaseController(model_, UI_) {}
	};

	class GameMenuController : public BaseController { // define the action's that can be do when Game Menu is open
	public:
		void Process(ProgrammState& programmState) override;

		GameMenuController(Md::Model* model_, Vw::UserView* UI_) : BaseController(model_, UI_) {}
	};
}
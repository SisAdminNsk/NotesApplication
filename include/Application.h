#pragma once
#include "Model.h"
#include "View.h"
#include "IController.h"

class Core {
private:
	Md::Model* model;
public:
	Vw::UserView* UI;
	Ctrl::BaseController* controller;

	Core(Md::Model* model_, Vw::UserView* UI_, Ctrl::BaseController* controller_) : model(model_), UI(UI_), controller(controller_) {}
};
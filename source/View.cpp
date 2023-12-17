#include "View.h"

Vw::UserView::UserView() {
}

void Vw::UserView::initLabirintBorders()
{
	int borderSize = model->labirint->Cell_size * sqrt(model->graph->nodes.size());
	int cellSize = model->labirint->Cell_size;

	graph_data_from_model = model->graph->getViewData();

	labirintBorder.setSize(sf::Vector2f(borderSize + cellSize, borderSize + cellSize));
	labirintBorder.setPosition(sf::Vector2f(graph_data_from_model.nodeId_to_Coord[0].X - model->labirint->Cell_size / 2,
		graph_data_from_model.nodeId_to_Coord[0].Y - model->labirint->Cell_size / 2));
	labirintBorder.setFillColor(sf::Color::Red);
}

void Vw::UserView::ReciveModelData() {
	sprites_for_draw.clear();

	initLabirintBorders();

	graph_data_from_model = model->graph->getViewData();

	for (const auto& idPackage : graph_data_from_model.nodeId_to_nodeSpriteNumber) {
		sf::Sprite maze;
		int spriteType = idPackage.second;

		maze = *sprites_for_graph[spriteType];
		sprites_for_draw.push_back(maze);
	}

	int id = 0;
	for (const auto& coordPackage : graph_data_from_model.nodeId_to_Coord) {
		Md::Coord coord = coordPackage.second;
		sprites_for_draw[id].setPosition(sf::Vector2f(coord.X, coord.Y));
		id++;
	}
}

void Vw::UserView::Update()
{
	this->path.clear();
	this->path = this->GetLabirintSolution();
	
	for (auto sprite : path) {
		this->sprites_for_draw[sprite].setColor(sf::Color::Blue);
	}
}

void Vw::UserView::DrawGraph() const {
	this->whereDraw->draw(labirintBorder);

	for (const auto& sprite : sprites_for_draw) {
		this->whereDraw->draw(sprite);
	}
}

void Vw::UserView::UpdateGameCamera() {
	this->whereDraw->setView(*this->gameCamera2D);
}

void Vw::UserView::UpdateGameMenuCamera()
{
	this->whereDraw->setView(*this->gameMenuCamera2D);
}

std::vector<int> Vw::UserView::GetLabirintSolution()
{
	return this->model->pathFinder.find_path(*this->model->graph, 0, this->model->graph->nodes.size() - 1);
}

bool Vw::UserView::SimulateLabirintSolution(sf::Color spriteColor, float speedCofficient)
{
	for (auto spriteNumber : this->path) {
		if (this->programmClock->getElapsedTime().asMilliseconds() > this->solutionLabirintSpeedF / speedCofficient) {
			if (this->sprites_for_draw[spriteNumber].getColor() != sf::Color::Green){
				this->programmClock->restart();
				this->path.erase(this->path.begin());
				this->sprites_for_draw[spriteNumber].setColor(spriteColor);
				if (this->sprites_for_draw[this->sprites_for_draw.size() - 1].getColor() == sf::Color::Green){
					return false;
				}
			}
		}
	}
	return true;// end of simulation
}

void Vw::UserView::GoLeftCamera2D() {
	this->gameCamera2D->setCenter(this->gameCamera2D->getCenter().x - cameraSpeedF, this->gameCamera2D->getCenter().y);
}

void Vw::UserView::GoRightCamera2D() {
	this->gameCamera2D->setCenter(this->gameCamera2D->getCenter().x + cameraSpeedF, this->gameCamera2D->getCenter().y);
}

void Vw::UserView::GoUpCamera2D() {
	this->gameCamera2D->setCenter(this->gameCamera2D->getCenter().x, this->gameCamera2D->getCenter().y + cameraSpeedF);
}

void Vw::UserView::GoDownCamera2D() {
	this->gameCamera2D->setCenter(this->gameCamera2D->getCenter().x, this->gameCamera2D->getCenter().y - cameraSpeedF);
}

void Vw::UserView::GoDefaultCamera2D() {
	this->gameCamera2D->setSize(model->screen_size.first, model->screen_size.second);
	this->gameCamera2D->setCenter(this->whereDraw->getDefaultView().getCenter().x,
		this->whereDraw->getDefaultView().getCenter().y);
}

void Vw::UserView::ZoomInCamera2D() {
	this->gameCamera2D->zoom(zoomCofficientIn);
}

void Vw::UserView::ZoomOutCamera2D() {
	this->gameCamera2D->zoom(zoomCofficientOut);
}
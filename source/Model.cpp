#include "Model.h"

void Md::Model::Labirint::GenerateNewLabirint(int new_height, int new_widht)
{
	this->labirint.clear();

	for (int i = 0; i < new_height; i++) {
		this->labirint.push_back(std::vector<Cell>(new_widht));
	}
	for (auto y = 0; y < new_height; y++)
		for (auto x = 0; x < new_widht; x++) {
			this->labirint[x][y].x = x;
			this->labirint[x][y].y = y;
		}


	auto startX = rand() % new_widht;
	auto startY = rand() % new_height;

	this->labirint[startX][startY].Visited = true;

	std::stack<Cell> path;
	path.push(this->labirint[startX][startY]);

	while (!path.empty()) {
		Cell _cell = path.top();

		std::vector<Cell> nextStep;
		if (_cell.x > 0 && (this->labirint[_cell.x - 1][_cell.y].Visited == false))
			nextStep.push_back(this->labirint[_cell.x - 1][_cell.y]);
		if (_cell.x < new_widht - 1 && (labirint[_cell.x + 1][_cell.y].Visited == false))
			nextStep.push_back(this->labirint[_cell.x + 1][_cell.y]);
		if (_cell.y > 0 && (this->labirint[_cell.x][_cell.y - 1].Visited == false))
			nextStep.push_back(this->labirint[_cell.x][_cell.y - 1]);
		if (_cell.y < new_height - 1 && (this->labirint[_cell.x][_cell.y + 1].Visited == false))
			nextStep.push_back(this->labirint[_cell.x][_cell.y + 1]);

		if (!nextStep.empty())
		{
			Cell next = nextStep[rand() % nextStep.size()];
			if (next.x != _cell.x)
			{
				if (_cell.x - next.x > 0)
				{
					this->labirint[_cell.x][_cell.y].Left = Open;
					this->labirint[next.x][next.y].Right = Open;
				}
				else
				{
					this->labirint[_cell.x][_cell.y].Right = Open;
					this->labirint[next.x][next.y].Left = Open;
				}
			}
			if (next.y != _cell.y)
			{
				if (_cell.y - next.y > 0)
				{
					this->labirint[_cell.x][_cell.y].Top = Open;
					this->labirint[next.x][next.y].Bottom = Open;
				}
				else
				{
					this->labirint[_cell.x][_cell.y].Bottom = Open;
					this->labirint[next.x][next.y].Top = Open;
				}
			}
			this->labirint[next.x][next.y].Visited = true;
			path.push(next);
		}
		else
			path.pop();
	}
}

std::vector<std::vector<Md::Model::Labirint::Cell>> const Md::Model::Labirint::GetLabirint() const
{
	return this->labirint;
}

Md::Model::Model()
{

}

Md::Model::Graph::Graph(const Labirint& labirint, std::pair<int, int> screenSize_)
{
	this->screen_size = screenSize_;

	auto adjacency_list = ConvertToAdjacencyList(labirint);
	this->nodes = adjacency_list;

	MatchSprites();
	FillNodeCoord();
}

Md::Model::Graph::Graph() {
}

void Md::Model::Graph::Clear()
{
	this->nodes.clear();
}

void Md::Model::Graph::ClearEdges()
{
	for (auto& node : this->nodes) {
		node.edges.clear();
	}
}

void Md::Model::Graph::InitStartValues()
{
	for (auto& node : this->nodes) {
		node.weight = INF;
		node.prevIndex = -1;
		node.visited = false;
	}
}

void Md::Model::Graph::Update(const Labirint& new_labirint)
{
	auto updated_adjacency_list = ConvertToAdjacencyList(new_labirint);
	this->nodes = updated_adjacency_list;

	MatchSprites();
	FillNodeCoord();
}

std::vector<Md::Model::Graph::Node> Md::Model::Graph::ConvertToAdjacencyList(const Labirint& labirint)
{
	std::vector<Node> adjacency_list;
	std::vector<Node::Edge> node_edges_list;
	auto puzzle = labirint.GetLabirint();
	int node_id = 0;

	auto new_edge = []() {return Node::Edge(1); };

	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle[i].size(); j++) {
			Node node(node_id);
			auto cell = puzzle[j][i];
			if (cell.Left == Open) {
				auto edge = new_edge();
				edge.indexTo = node_id - 1;
				node_edges_list.push_back(edge);
			}
			if (cell.Right == Open) {
				auto edge = new_edge();
				edge.indexTo = node_id + 1;
				node_edges_list.push_back(edge);
			}
			if (cell.Top == Open) {
				auto edge = new_edge();
				edge.indexTo = node_id - puzzle[i].size();
				node_edges_list.push_back(edge);
			}
			if (cell.Bottom == Open) {
				auto edge = new_edge();
				edge.indexTo = node_id + puzzle[i].size();
				node_edges_list.push_back(edge);
			}
			node.edges = node_edges_list;
			node_edges_list.clear();
			adjacency_list.push_back(node);

			node_id++;
		}
	}
	return adjacency_list;
}

void Md::Model::Graph::MatchSprites()
{
	const enum nodeTextureNumbers { EmptySprite, RightSprite, BottomSprite, RbSprite };
	int srt = sqrt(this->nodes.size());

	for (const auto& node : this->nodes) {
		bool isHavingRightNeighbour = false;
		bool isHavingLeftNeighbour = false;
		bool isHavingBottomNeighbour = false;

		for (size_t i = 0; i < node.edges.size(); i++) { // seeing neighbours 
			if (node.edges[i].indexTo - node.id == 1)
				isHavingRightNeighbour = true;
			if (node.edges[i].indexTo - node.id == srt)
				isHavingBottomNeighbour = true;
			if (node.edges[i].indexTo - node.id == -1)
				isHavingLeftNeighbour = true;
		}
		// match empty sprite's
		if (isHavingBottomNeighbour && isHavingRightNeighbour) // it's EmptySprite 1.1
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::EmptySprite;

		else if (((node.id + 1) % srt == 0) && (isHavingBottomNeighbour))// it's EmprySprite 1.2Ф
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::EmptySprite;

		else if (node.id == nodes.size() - 1) // it's EmptySprite  1.3
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::EmptySprite;

		else if (node.id >= (nodes.size() - 1) - srt && isHavingRightNeighbour)// it's EmptySprite 1.4
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::EmptySprite;
		// match right sprite's 
		else if (!isHavingRightNeighbour && isHavingBottomNeighbour)// it's RightSprite 2.1
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::RightSprite;

		else if (node.id >= (nodes.size() - 1) - srt && !isHavingRightNeighbour)// it's RightSprite 2.2
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::RightSprite;
		// match bottom sprite's
		else if (!isHavingBottomNeighbour && isHavingRightNeighbour)// it's BottomSprite 3.1
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::BottomSprite;
		// match rb sprite's
		else if (!isHavingBottomNeighbour && !isHavingRightNeighbour) // it's RbSprite 4.1
			this->dataForDraw.nodeId_to_nodeSpriteNumber[node.id] = nodeTextureNumbers::RbSprite;
	}
}

void Md::Model::Graph::FillNodeCoord()
{
	auto labirint_width = sqrt(this->nodes.size());
	auto Cell_size = Labirint::Cell_size;

	const std::pair<int, int> myWindowCenter = std::make_pair(screen_size.first / 2 - (labirint_width * Cell_size) / 2,
		screen_size.second / 2 - (labirint_width * Cell_size) / 2);

	for (size_t i = 0; i < labirint_width; i++) {
		for (size_t j = 0; j < labirint_width; j++) {
			this->dataForDraw.nodeId_to_Coord[i * labirint_width + j] = Coord(Cell_size * j + myWindowCenter.first,
				Cell_size * i + myWindowCenter.second);
		}
	}
}

std::vector<int> Md::Model::Path_finders::convert_to_path(const Md::Model::Graph& graph, const int start_node_id, const int end_node_id) {
	std::vector<int> path;
	std::stack<int> tmp_path;
	int current_node = end_node_id;
	while (current_node != -1) {
		tmp_path.push(current_node);
		current_node = graph.nodes[current_node].prevIndex;
	}
	while (!tmp_path.empty()) {
		path.push_back(tmp_path.top());
		tmp_path.pop();
	}
	return path;
}

std::vector<int> Md::Model::Path_finders::find_path(Md::Model::Graph& graph, const int start_node_id, const int end_node_id) {
	graph.InitStartValues();

	std::queue<Md::Model::Graph::Node> nodes_queue;
	graph.nodes[start_node_id].weight = 0;
	nodes_queue.push(graph.nodes[start_node_id]);
	while (!nodes_queue.empty()) {
		auto current_node = nodes_queue.front();
		nodes_queue.pop();
		if (graph.nodes[current_node.id].visited) {
			continue;
		}

		graph.nodes[current_node.id].visited = true;
		for (int i = 0; i < current_node.edges.size(); i++) {// проходимся по всем соседям вершины
			int next_node_index = graph.nodes[current_node.id].edges[i].indexTo;
			int current_edge_weight = graph.nodes[current_node.id].edges[i].weight;

			if (!graph.nodes[next_node_index].visited) {
				if (current_node.weight + current_edge_weight < graph.nodes[next_node_index].weight) {
					graph.nodes[next_node_index].weight = current_node.weight + current_edge_weight;
					graph.nodes[next_node_index].prevIndex = current_node.id;
					nodes_queue.push(graph.nodes[next_node_index]);
				}
			}
		}
	}
	return convert_to_path(graph, start_node_id, end_node_id);
}






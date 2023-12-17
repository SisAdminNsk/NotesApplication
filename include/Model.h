#pragma once
#include <map>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <stack>

// LOGIC MODELS HERE!
// YOU WILL NOT FIND GRAPHICS ELEMENTS HERE
// VIEW RECIVE DATA FROM LOGIC MODEL AND PRESENT DATA FOR USER


namespace Md
{
	const int INF = 2147483647;

	const enum CellState { Close, Open };

	struct Coord {
		int X = 0;
		int Y = 0;

		bool operator >(const Coord& coord) {
			if (X + Y > coord.X + coord.Y)
				return true;
			else
				false;
		}

		Coord() {}
		Coord(int x, int y) : X(x), Y(y) {}
	};

	class Model
	{
	public:
		class Labirint
		{
		public:
			class Cell
			{
			public:
				int x = 0;
				int y = 0;

				CellState Left = Close;
				CellState Right = Close;
				CellState Top = Close;
				CellState Bottom = Close;

				bool Visited = false;

				Cell() {}
			};

			static const int Cell_size = 50;// size of cell sprite in px. (width and height)
			Labirint() {}

			void GenerateNewLabirint(int new_height, int new_widht);
			std::vector<std::vector<Cell>> const GetLabirint() const;
		private:
			std::vector<std::vector<Cell>> labirint;
		};

		struct Graph
		{
		public:
			struct Node
			{
			public:
				struct Edge
				{
				public:
					int weight;
					int indexTo;

					Edge() {}
					Edge(int Weight) : weight(Weight) {}
				};

				std::vector<Edge> edges;

				int id = 0;
				int prevIndex = -1;
				int weight = 1;
				bool visited = false;

				Node() {}
				Node(int node_id) : id(node_id) {}
			};

			void Clear();
			void ClearEdges();
			void InitStartValues();
			void Update(const Labirint& new_labirint); // use after generation of new labirint

			Graph(const Labirint& labirint, std::pair<int, int> screenSize_);
			Graph();

			std::vector<Node> nodes;

			struct viewData {
				std::map<int, int> nodeId_to_nodeSpriteNumber;// info for what draw
				std::map<int, Coord> nodeId_to_Coord;// info for where draw
			};

			const viewData& getViewData() const {
				return this->dataForDraw;
			}

			std::pair<int, int> screen_size;

		private:
			std::vector<Node> ConvertToAdjacencyList(const Labirint& labirint);
			void MatchSprites();
			void FillNodeCoord();

			viewData dataForDraw;
		};

		const std::pair<int, int> screen_size;
		Model(Labirint* labirint_, Graph* graph_, std::pair<int, int> screenSize_) : labirint(labirint_), graph(graph_),
			screen_size(screenSize_) {}
		Model();

		Graph* graph;// model work's with graph &&
		Labirint* labirint;// model work's with labirint &&

		class Path_finders {
		private:
			std::vector<int> convert_to_path(const Md::Model::Graph& graph, const int start_node_id, const int end_node_id);

		public:
			std::vector<int> find_path(Md::Model::Graph& graph, const int start_node_id, const int end_node_id);
		};

		Path_finders pathFinder;
	};
}
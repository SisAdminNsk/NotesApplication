//#include "Dijkstra.h"
//using namespace algorithms;
//
//std::vector<int> Path_finders::convert_to_path(const Md::Model::Graph& graph, const int start_node_id, const int end_node_id)
//{
//	std::vector<int> path;
//	std::stack<int> tmp_path;
//	int current_node = end_node_id;
//	while (current_node != -1) {
//		tmp_path.push(current_node);
//		current_node = graph.nodes[current_node].prevIndex;
//	}
//	while (!tmp_path.empty()) {
//		path.push_back(tmp_path.top());
//		tmp_path.pop();
//	}
//	return path;
//}
//
//std::vector<int> Path_finders::find_path(Md::Model::Graph& graph, const int start_node_id, const int end_node_id)
//{
//	graph.InitStartValues();
//
//	std::queue<Md::Model::Graph::Node> nodes_queue;
//	graph.nodes[start_node_id].weight = 0;
//	nodes_queue.push(graph.nodes[start_node_id]);
//	while (!nodes_queue.empty()) {
//		auto current_node = nodes_queue.front();
//		nodes_queue.pop();
//		if (graph.nodes[current_node.id].visited) {
//			continue;
//		}
//
//		graph.nodes[current_node.id].visited = true;
//		for (int i = 0; i < current_node.edges.size(); i++) {// проходимся по всем соседям вершины
//			int next_node_index = graph.nodes[current_node.id].edges[i].indexTo;
//			int current_edge_weight = graph.nodes[current_node.id].edges[i].weight;
//
//			if (!graph.nodes[next_node_index].visited) {
//				if (current_node.weight + current_edge_weight < graph.nodes[next_node_index].weight) {
//					graph.nodes[next_node_index].weight = current_node.weight + current_edge_weight;
//					graph.nodes[next_node_index].prevIndex = current_node.id;
//					nodes_queue.push(graph.nodes[next_node_index]);
//				}
//			}
//		}
//	}
//	return convert_to_path(graph, start_node_id, end_node_id);
//}
//

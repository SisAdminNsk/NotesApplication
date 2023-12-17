#pragma once
#include "Model.h"
//#include "Dijkstra.h"

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual std::vector<int> DoAlgorithm(Md::Model::Graph& graph, const int start_node_id, const int end_node_id) const = 0;
};

class MyContext
{
private:
    Strategy* strategy_;
public:
    MyContext(Strategy* strategy = nullptr) : strategy_(strategy) {}
    ~MyContext() { delete this->strategy_; }

    void set_strategy(Strategy* strategy)
    {
        delete this->strategy_;
        this->strategy_ = strategy;
    }

    std::vector<int> do_alghoritm(Md::Model::Graph& graph, const int start_node_id, const int end_node_id) const
    {
        std::vector<int> result = this->strategy_->DoAlgorithm(graph, start_node_id, end_node_id);
        return result;
    }
};

class Dijkstra_alghoritm : public Strategy
{
public:
    std::vector<int> DoAlgorithm(Md::Model::Graph& graph, const int start_node_id, const int end_node_id) const override
    {
        Md::Model::Path_finders path_finder;
        auto labirint_path = path_finder.find_path(graph, start_node_id, end_node_id);
        return labirint_path;
    }
};

class BFS_alghoritm : public Strategy {
    // need to be realized
};
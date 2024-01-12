#pragma once
#include "Grid.h"
#include <queue>
#include <stack>

class Priority_Node
{
public:
	Node node;
	float priority;

	Priority_Node(Node gNode, float gPriority);

public:
	bool friend operator< (const Priority_Node& node1, const Priority_Node &node2);
	bool friend operator> (const Priority_Node& node1, const Priority_Node &node2);
};

class PathFinding {

public:

private:
	struct PathData {
		Vector2D cameFrom;
		float cost;
		float heuristic;

		PathData() : cameFrom(-1, -1), cost(-1), heuristic(-1){}
		PathData(Vector2D _cameFrom, float _cost, float _heuristic) : cameFrom(_cameFrom), cost(_cost), heuristic(_heuristic){}
		PathData(PathData &pd) : cameFrom(pd.cameFrom), cost(pd.cost), heuristic(pd.heuristic){}

	};

	static bool NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes);
	static bool NodeVisited(Node currentNode, const std::vector<std::vector<PathData>> &visitedNodes);
	static bool NodeValid(Node currentNode, const std::vector<std::vector<PathData>>& visitedNodes, const float &currentCost);
	static float CalculateCost(const float &cost, Node &currentNode, Node &neighborNode);
	static float GetDist(Node &actualNode, Node &neighborNode);
	static float Octile(Vector2D start, Vector2D end);

public:
	static std::stack<Node> BFS(Grid *maze, Vector2D start, Vector2D target, int &num_n);
	static std::stack<Node> Dijkstra(Grid *maze, Vector2D start, Vector2D target, int &num_n);
	static std::stack<Node> Greedy(Grid *maze, Vector2D start, Vector2D target, int &num_n);
	static std::stack<Node> AStar(Grid *maze, Vector2D start, Vector2D target, int &num_n);

};
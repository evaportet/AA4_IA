#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(Grid *grid)
{
	for (int i = 0; i < grid->getNumCellY(); i++) {
		for (int j = 0; j < grid->getNumCellX(); j++) {
			if (grid->isValidCell(Vector2D((unsigned int)j, (unsigned int)i)))
			{
				Node* tmpNeighboursNode;
				std::vector<Node*> tmpNeighboursNodes;

				///// LEFT
				if (grid->isValidCell(Vector2D((unsigned int)j - 1, (unsigned int)i))) // LEFT
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j - 1, (unsigned int)i),
						grid->Weight(Vector2D((unsigned int)j - 1, (unsigned int)i)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				
				///// CENTER
				if (grid->isValidCell(Vector2D((unsigned int)j, (unsigned int)i - 1))) // UP
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j, (unsigned int)i - 1),
						grid->Weight(Vector2D((unsigned int)j, (unsigned int)i - 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				if (grid->isValidCell(Vector2D((unsigned int)j, (unsigned int)i + 1))) // DOWN
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j, (unsigned int)i + 1),
						grid->Weight(Vector2D((unsigned int)j, (unsigned int)i + 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				///// RIGHT
													   
				if (grid->isValidCell(Vector2D((unsigned int)j + 1, (unsigned int)i))) // RIGHT
				{											   
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j + 1, (unsigned int)i),
						grid->Weight(Vector2D((unsigned int)j + 1, (unsigned int)i)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}											   
				
				///// LEFT
				if (grid->isValidCell(Vector2D((unsigned int)j - 1, (unsigned int)i - 1))) // UP LEFT
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j - 1, (unsigned int)i - 1),
						grid->Weight(Vector2D((unsigned int)j - 1, (unsigned int)i - 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				if (grid->isValidCell(Vector2D((unsigned int)j - 1, (unsigned int)i + 1))) // DOWN LEFT
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j - 1, (unsigned int)i + 1),
						grid->Weight(Vector2D((unsigned int)j - 1, (unsigned int)i + 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				///// RIGHT
				if (grid->isValidCell(Vector2D((unsigned int)j + 1, (unsigned int)i - 1))) // UP RIGHT
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j + 1, (unsigned int)i - 1),
						grid->Weight(Vector2D((unsigned int)j + 1, (unsigned int)i - 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}
				if (grid->isValidCell(Vector2D((unsigned int)j + 1, (unsigned int)i + 1))) // DOWN RIGHT
				{
					tmpNeighboursNode = new Node(Vector2D((unsigned int)j + 1, (unsigned int)i + 1),
						grid->Weight(Vector2D((unsigned int)j + 1, (unsigned int)i + 1)));
					tmpNeighboursNodes.push_back(tmpNeighboursNode);
				}

				Node* tmpNode = new Node(Vector2D((unsigned int)j, (unsigned int)i), tmpNeighboursNodes, 
					grid->Weight(Vector2D((unsigned int)j, (unsigned int)i)), grid->Weight(Vector2D((unsigned int)j, (unsigned int)i)));
				nodes.push_back(tmpNode);
				tmpNeighboursNodes.clear();
			}
			else
			{
				if ((j != 0 && j != grid->getNumCellX() - 1) && (i != 0 && i != grid->getNumCellY() - 1))
				{
					Node* tmpNode = new Node(Vector2D((unsigned int)j, (unsigned int)i));

					nodesWall.push_back(tmpNode);
				}
				
			}
		}
	}

}

Graph::~Graph()
{
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		delete nodes[i];
	}
}

std::vector<Node*> Graph::getNodes()
{
	return nodes;
}

std::vector<Node*> Graph::getNodesWall()
{
	return nodesWall;
}

Node* Graph::getCurrentNodePosition(Vector2D target)
{
	for (Node *currentNode : nodes)
	{
		if (currentNode->pos == target) {
			return currentNode;
		}
	}

	for (Node* currentNode : nodes)
	{
		if (currentNode->pos == Vector2D(target.x, target.y - 1)) {
			return currentNode;
		}
		else if (currentNode->pos == Vector2D(target.x - 1, target.y)) {
			return currentNode;
		}
		else if (currentNode->pos == Vector2D(target.x, target.y + 1)) {
			return currentNode;
		}
		else if (currentNode->pos == Vector2D(target.x + 1, target.y)) {
			return currentNode;
		}
	}
	

}

void Graph::ChangeWeight(Vector2D target)
{
	Node* currentNode = getCurrentNodePosition(target);
	currentNode->weight = 100;

	for (Node* neighbour : currentNode->neighbours)
	{
		SetWeightFromCurrentNodePosition(getCurrentNodePosition(neighbour->pos)->pos);
	}
}

void Graph::SetWeightFromCurrentNodePosition(Vector2D target)
{
	for (Node* currentNode : nodes)
	{
		if (currentNode->pos == target) {
			currentNode->weight = 100;
		}
	}
}

void Graph::SetInitialWeight()
{
	for (Node* n : nodes)
	{
		n->weight = n->initialWeight;
	}
}

Node* Graph::getComeFromNode(Node* n)
{
	return n->comeFrom;
}

Vector2D Graph::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
}

Vector2D Graph::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

void Graph::Reset()
{
	for (Node *node : nodes)
	{
		node->comeFrom = nullptr;
		node->costSoFar = 0;
		node->heuristic = 0;
		node->priority = 0;
	}
}
#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <numeric>
#include <algorithm>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "PathFinding.h"
#include "Node.h"

class ScenePathFindingMouse :
	public Scene
{
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

	int current_it = 0;
	int max_it = 20;

	int num;
	int al = 3;

	std::vector<int> BFS_n;
	std::vector<int> Dijkstra_n;
	std::vector<int> Greedy_n;
	std::vector<int> AStar_n;

private:
	std::vector<Agent*> agents;
	Agent enemy1;
	Agent enemy2;
	Agent enemy3;

	Vector2D coinPosition;
	Vector2D targetCell;

	Grid *maze;
	bool draw_grid;
	double clamp(double x, double upper, double lower);
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	void UpdateEnemies(float dtime, SDL_Event *event);

};

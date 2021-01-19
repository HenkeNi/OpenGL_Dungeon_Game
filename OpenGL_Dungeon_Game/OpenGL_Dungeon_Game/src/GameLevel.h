#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <vector>

class GameLevel
{
public:
	GameLevel() {}

	void load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	void draw(SpriteRenderer& renderer);
	bool isCompleted();

	const std::vector<GameObject>& getTiles() const;

private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

private:
	std::vector<GameObject> m_tiles;
};


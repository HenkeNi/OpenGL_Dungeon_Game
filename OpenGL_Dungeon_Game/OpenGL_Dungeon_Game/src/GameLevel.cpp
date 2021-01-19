#include "GameLevel.h"
#include "ResourceManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>

void GameLevel::load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	m_tiles.clear(); // clear old data
	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream)
	{
		std::cout << "load";
		while (std::getline(fstream, line)) // read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
		{
			std::cout << "IS HERE";
			init(tileData, levelWidth, levelHeight);

		}
	}

}


void GameLevel::init(std::vector<std::vector<unsigned int>> tileData,
	unsigned int lvlWidth, unsigned int lvlHeight)
{
	// calculate dimensions
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unitWidth = lvlWidth / static_cast<float>(width);
	float unitHeight = lvlHeight / height;
	// initialize level tiles based on tileData
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{ 
			if (tileData[y][x] == 1) // solid
			{
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(pos, size, 
					ResourceManager::getTexture("block_solid"), 
					glm::vec3(0.8f, 0.8f, 0.7f));
				obj.setIsSolid(true);
				m_tiles.push_back(obj);
			}
			else if (tileData[y][x] > 1)
			{
				glm::vec3 color = glm::vec3(1.0f); 
				if (tileData[y][x] == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				m_tiles.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), color));
			}
		}
	}
}


void GameLevel::draw(SpriteRenderer& renderer)
{
	for (GameObject& tile : m_tiles)
		if (!tile.getIsDestroyed())
			tile.draw(renderer);
}


bool GameLevel::isCompleted()
{
	for (GameObject& tile : m_tiles)
		if (!tile.getIsSolid() && !tile.getIsDestroyed())
			return false;
	return true;
}



const std::vector<GameObject>& GameLevel::getTiles() const
{
	return m_tiles;
}
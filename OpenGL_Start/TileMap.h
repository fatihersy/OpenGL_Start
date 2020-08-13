#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void clear();
	float gridSizeF;
	int gridSizeI;
	int layers;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
	std::stack<Tile*> deferredRenderStack;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Culling
	short fromX;
	short toX;
	short fromY;
	short toY;
	short layer;

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	// ACCESSORS
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const size_t x, const size_t y, const size_t layer) const;

	// FUNCTIONS
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeferred(sf::RenderTarget& target);

};



#endif


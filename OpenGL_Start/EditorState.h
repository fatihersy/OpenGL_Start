#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

#define TEXTURESELECTOR_TEXT "TS"

#define TILE_MAP_WIDTH  30
#define TILE_MAP_HEIGHT 20

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
	public State
{
private:
	//Variables
	sf::View view;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	sf::IntRect textureRect;
	bool collision;
	short type;
	float cameraSpeed;
	int layer = 0;

	//// Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();
	//// Functions


public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif


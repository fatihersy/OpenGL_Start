#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class MainMenuState;

#define GRIDSIZE 100.f
#define DELTATIME 0.f

class Game
{
private:

	//Veriables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initVeriables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	//CONSTRUCTORS/DESTRUCTORS
	Game();
	virtual ~Game();
	
	//FUNCTIONS

	//REGULAR
	void endApplication();

	//UPDATE
	void updateDt();
	void update_SFML_Events();
	void update();
	
	//RENDER
	void render();
	
	//CORE
	void run();

};

#endif


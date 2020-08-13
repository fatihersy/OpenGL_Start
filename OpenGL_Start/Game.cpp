#include "stdafx.h"
#include "Game.h"
#include "MainMenuState.h"

//INITIALIZER FUNCTIONS
void Game::initVeriables()
{
    this->window = NULL;
    this->dt = DELTATIME;
    this->gridSize = GRIDSIZE;
}
void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}
void Game::initWindow()
{
    if (this->gfxSettings.fullscreen) 
    {
        this->window = new sf::RenderWindow
        (
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Fullscreen, 
            this->gfxSettings.contextSettings ); }
    else 
    {
        this->window = new sf::RenderWindow
        (
            this->gfxSettings.resolution, 
            this->gfxSettings.title, 
            sf::Style::Titlebar | sf::Style::Close, 
            this->gfxSettings.contextSettings ); }
	
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}
void Game::initKeys()
{

    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }

    }

    ifs.close();

    //DEBUG REMOVE LATER!
    for (auto i : this->supportedKeys) 
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}
void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}
void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
    //this->states.push(new GameState(this->window, &this->supportedKeys));
}

//CONSTRUCTOR/DESTRUCTORS
Game::Game() {
    this->initVeriables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}
Game::~Game() {
	delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}


//FUNCTIONS
void Game::endApplication()
{
    std::cout << "Ending Applications" << "\n";
}
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}
void Game::update_SFML_Events()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}
void Game::update()
{
    this->update_SFML_Events();

    if (!this->states.empty()) 
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit()) {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    //Application End
    else {
        this->endApplication();
        this->window->close();
    }
        
}
void Game::render()
{
    this->window->clear();

    // Render Items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

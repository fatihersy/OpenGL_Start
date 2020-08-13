#include "stdafx.h"
#include "EditorState.h"

//// INITIALIZER FUNCTIONS
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 200.f;
	this->layer = 0;
}
void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);
	this->view.setCenter(
		sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
		);
}
void EditorState::initBackground()
{
	
}
void EditorState::initFonts()
{
	if (
		!this->font.loadFromFile("Fonts/ComicNeue.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}
void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White); 
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
}
void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();
}
void EditorState::initPauseMenu() 
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");
	this->pmenu->addButton("SAVE", 400.f, "Save");
	this->pmenu->addButton("LOAD", 300.f, "Load");
}
void EditorState::initButtons()
{
	/*
	this->buttons["GAME_STATE"] = new Button(
		100.f, 100.f, 150.f, 50.f,
		&this->font, "New Game", 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
	*/
}
void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width*0.05),
		static_cast<float>(this->stateData->gfxSettings->resolution.height))
	);
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		sidebar.getSize().x/(7,4), 
		20.f, 
		this->stateData->gridSize*8.f,
		this->stateData->gridSize*3.f,
		this->stateData->gridSize, 
		this->tileMap->getTileSheet(),
		this->font, TEXTURESELECTOR_TEXT
		);
}
void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, TILE_MAP_WIDTH, TILE_MAP_HEIGHT, "Resources/Images/Tiles/tilesheet1.png");
}
//// INITIALIZER FUNCTIONS


//// CONSTRUCTOR / DESTRUCTOR
EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}
EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;

	delete this->textureSelector;
}
//// CONSTRUCTOR / DESTRUCTOR


//// FUNCTIONS
void EditorState::updateInput(const float& dt)
{
	//UPDATE PLAYER INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused) this->pauseState();
		else this->unpauseState();
	}

}
void EditorState::updateEditorInput(const float& dt)
{
	// MOVE VIEW
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) 
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) 
		{
			if (!this->textureSelector->getActive()) 
			{
				this->tileMap->addTile(
					static_cast<unsigned short>(this->mousePosGrid.x), 
					static_cast<unsigned short>(this->mousePosGrid.y), 
					0, 
					this->textureRect,
					this->collision,
					this->type
				);
			}
			else this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && this->getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(
					static_cast<const unsigned>(this->mousePosGrid.x),
					static_cast<const unsigned>(this->mousePosGrid.y),
					0
				);
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeyTime()) 
	{
		this->collision = !this->collision;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeyTime()) 
	{
		// CHANGE TO 
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeyTime()) 
	{
		if( type > 0 ) --this->type;
	}
}
void EditorState::updateButtons()
{
	/*UPDATE ALL THE BUTTONS IN THE STATE AND HANDLES THEIR FUNCTIONLAITY*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}
void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive()) 
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type <<
		"\n" << "Stack Size: " << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer);
	this->cursorText.setString(ss.str());
	
}
void EditorState::updatePauseMenuButtons()
{
	if(this->pmenu->isButtonPressed("QUIT")) this->endState();

	if (this->pmenu->isButtonPressed("SAVE")) this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD")) this->tileMap->loadFromFile("text.slmp");
}
void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) // UNPAUSED
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

	
}
void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
void EditorState::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive()) 
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	} 
	
	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);
}
void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) // PAUSED MENU RENDER
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}

}
//// FUNCTIONS
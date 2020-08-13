#include "stdafx.h"
#include "Gui.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														  BUTTON			  									    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


gui::Button::Button(
	float x, float y, float height, float width,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x,y));
	this->shape.setSize(sf::Vector2f(height,width));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width  / 2) - (this->text.getGlobalBounds().width / 2),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - (this->text.getGlobalBounds().height / 2)
		);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}
gui::Button::~Button()
{

}

// ACCESSORS
const bool gui::Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;
}
const std::string gui::Button::getText() const
{
	return this->text.getString();
}
const unsigned short gui::Button::getId() const
{
	return this->id;
}

// FUNCTIONS
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}
void gui::Button::setId(const unsigned short id)
{
	this->id = id;
}
void gui::Button::update(const sf::Vector2i mousePosWindow)
{
	/* Update The Booleans for hover and pressed */

	//HOVER
	this->buttonState = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{

	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break; 

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Green);
		this->shape.setOutlineColor(sf::Color::Blue);
		break;
	}
	
}
void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														  BUTTON						   							   	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									                   DROPDOWNLIST		  	    		   			   		            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui::DrowDownList::DrowDownList(
	float x, float y, float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index
	) : font(font), showList(false), keytimeMax(1.f), keytime(0.f) 
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 16,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	for (unsigned short i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(new gui::Button(
			x, y + ((i+1)*height), width, height,
			&this->font, list[i], 16,
			sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), i
			));
	}

}
gui::DrowDownList::~DrowDownList()
{
	delete this->activeElement;

	for (size_t i = 0; i < list.size(); i++) delete this->list[i];
}

// ACCESSORS
const bool gui::DrowDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax) 
	{
		this->keytime = 0.f;
		return true;
	}
	
	return false;
	
}
const unsigned short gui::DrowDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

// FUNCTIONS
void gui::DrowDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax) {
		this->keytime += 10.f * dt;
	}
}
void gui::DrowDownList::update(const sf::Vector2i mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytime()) 
	{
		this->showList = !this->showList;
	}

	if (this->showList) 
	{
		for (auto& i : this->list) 
		{ 
			i->update(mousePosWindow);

			if (i->isPressed()) 
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}
void gui::DrowDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list) { i->render(target); }
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									                   DROPDOWNLIST		  	    									        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									                 TEXTURE SELECTOR	  	    									        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, 
									  const sf::Texture* texture_sheet, sf::Font& font, std::string text)
	: keytimeMax(1.f), keytime(0.f)
{
	this->active = false;
	this->gridSize = gridSize;
	this->hidden = true;
	this->offset = 60.f;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, 
			static_cast<unsigned short>(this->bounds.getGlobalBounds().width), 
			static_cast<unsigned short>(this->sheet.getGlobalBounds().height))
		);
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, 
			static_cast<unsigned short>(this->sheet.getGlobalBounds().width), 
			static_cast<unsigned short>(this->bounds.getGlobalBounds().height))
		);
	}
	
	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_btn = new gui::Button(
		x, y, 50.f, 50.f,
		&font, text, 24,
		sf::Color(223, 230, 233, 200), sf::Color(250, 250, 250, 250), sf::Color(223, 230, 233, 200),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
		);;
}
gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

// ACCESSORS
const bool& gui::TextureSelector::getActive() const
{
	// TODO: insert return statement here
	return this->active;
}
const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}
const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;

}

// FUNCTIONS
void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax) {
		this->keytime += 10.f * dt;
	}
}
void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);

	this->hide_btn->update(mousePosWindow);

	if (this->hide_btn->isPressed() && this->getKeytime()) this->hidden = !this->hidden;

	if (!this->hidden) 
	{
		this->active = this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
	
		if (this->active) 
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			// UPDATE TEXTURE RECTANGLE
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}
void gui::TextureSelector::render(sf::RenderTarget& target)
{


	if (!this->hidden) {
		target.draw(this->bounds);
		target.draw(this->sheet);

		if(this->active) target.draw(this->selector);
	}

	this->hide_btn->render(target);

}

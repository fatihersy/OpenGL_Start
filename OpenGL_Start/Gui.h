#ifndef GUI_H
#define GUI_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(
			float x, float y, float height, float width,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		// ACCESSORS
		const bool isPressed() const;
		const std::string getText() const;
		const unsigned short getId() const;

		// MODIFIERS
		void setText(const std::string text);
		void setId(const unsigned short id);

		// FUNCTIONS
		void update(const sf::Vector2i mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	class DrowDownList {
		private:
			float keytime;
			float keytimeMax;

			sf::Font& font;
			gui::Button* activeElement;
			std::vector<gui::Button*> list;
			bool showList;

		public:
			// CONSTRUCTOR / DESTRUCTOR
			DrowDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
			~DrowDownList();

			// ACCESSORS
			const bool getKeytime();
			const unsigned short getActiveElementId() const;

			// FUNCTIONS
			void updateKeytime(const float& dt);
			void update(const sf::Vector2i mousePosWindow, const float& dt);
			void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		float offset;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, 
						const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		// ACCESSORS
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		// FUNCTIONS
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);

	};

}
#endif


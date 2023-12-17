#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

const enum ButtonStates { ButtonIdle = 0, ButtonHover, ButtonActive };

class Button {
private:
	bool isPressed;
	bool isHover;
	sf::Clock couldDown;

	short unsigned buttonState = ButtonIdle;

	sf::RectangleShape body;
	sf::Font* font;
	sf::Sound* sound;

	sf::Color idleColor = sf::Color::Blue;
	sf::Color hoverColor = sf::Color(150, 150, 150, 255);
	sf::Color activeColor = sf::Color::Red;
public:
	sf::Text text;
	int textCharacterSize = 35;

	const bool isButtonPressed() const;

	void Draw(sf::RenderWindow& whereDraw);
	void Update(const sf::RenderWindow& whereDraw);

	Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text
		, std::vector<sf::Color> activeColors);// [0] - idleColor [1] - hoverColor [2] - activeColor

	Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text
		, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text);

	Button(float xPos, float yPos, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text);

	~Button();
};

struct GraphView { // Struct needed for store files here
private:
	// for maze's
	sf::Image EmptySpriteImage;
	sf::Image RightSpriteImage;
	sf::Image BottomSpriteImage;
	sf::Image RbSpriteImage;

	sf::Texture EmptySpriteTexture;
	sf::Texture RightSpriteTexture;
	sf::Texture BottomSpriteTexture;
	sf::Texture RbSpriteTexture;

	sf::Sprite EmptySpriteBody;
	sf::Sprite RightSpriteBody;
	sf::Sprite BottomSpriteBody;
	sf::Sprite RbSpriteBody;

	sf::Image PlayerSpriteImage; // for player
	sf::Texture PlayerSpriteTexture;
	sf::Sprite PlayerSprite;

	const enum ErorMessages {
		LoadEmptyMazeFaleCode, LoadRightMazeFaleCode, LoadBottomMazeFaleCode,
		LoadRbMazeFaleCode, LoadPlayerImageFaleCode
	};

	void loadAll();

public:
	const enum SpritesNumber {
		EmptySprite, RightSprite, BottomSprite, RbSprite
	};

	GraphView();
	sf::Sprite& getSprite(SpritesNumber neededNumber);
};
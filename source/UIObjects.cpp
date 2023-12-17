#include "UIObjects.h"

const bool Button::isButtonPressed() const {
	if (this->buttonState == ButtonActive)
		return true;

	return false;
}

void Button::Draw(sf::RenderWindow& whereDraw)
{
	whereDraw.draw(this->body);
	whereDraw.draw(this->text);
}

void Button::Update(const sf::RenderWindow& whereDraw)
{
	this->buttonState = ButtonIdle;

	sf::Vector2i pixelPos = sf::Mouse::getPosition(whereDraw);
	sf::Vector2f worldPos = whereDraw.mapPixelToCoords(pixelPos);

	if (this->body.getGlobalBounds().contains(worldPos)) {
		this->buttonState = ButtonHover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = ButtonActive;

			if (couldDown.getElapsedTime() > sf::seconds(0.1f))
				this->sound->play();
		}
	}

	switch (this->buttonState)// change button color
	{
	case ButtonIdle:
		this->body.setFillColor(this->idleColor);
		break;
	case ButtonHover:
		this->body.setFillColor(this->hoverColor);
		break;
	case ButtonActive:
		this->body.setFillColor(this->activeColor);
		couldDown.restart();
		break;
	default:
		this->body.setFillColor(sf::Color::Red);
		break;
	}
}

Button::Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound,
	std::string text, std::vector<sf::Color> activeColors)
{
	this->body.setSize(sf::Vector2f(size.first, size.second));
	this->body.setPosition(sf::Vector2f(coords.first, coords.second));

	this->font = font;
	this->sound = sound;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textCharacterSize);

	this->text.setPosition(this->body.getPosition().x + (this->body.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f
		, this->body.getPosition().y + (this->body.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->idleColor = activeColors[0];
	this->hoverColor = activeColors[1];
	this->activeColor = activeColors[2];

	this->body.setFillColor(this->idleColor);
	couldDown.restart();
}

Button::Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->body.setSize(sf::Vector2f(size.first, size.second));
	this->body.setPosition(sf::Vector2f(coords.first, coords.second));

	this->font = font;
	this->sound = sound;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textCharacterSize);

	this->text.setPosition(this->body.getPosition().x + (this->body.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f
		, this->body.getPosition().y + (this->body.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->body.setFillColor(this->idleColor);
	couldDown.restart();
}

Button::Button(std::pair<float, float> coords, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text)
{
	this->body.setSize(sf::Vector2f(size.first, size.second));
	this->body.setPosition(sf::Vector2f(coords.first, coords.second));

	this->font = font;
	this->sound = sound;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textCharacterSize);

	this->text.setPosition(this->body.getPosition().x + (this->body.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f
		, this->body.getPosition().y + (this->body.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->body.setFillColor(this->idleColor);
	couldDown.restart();
}

Button::Button(float xPos, float yPos, std::pair<float, float> size, sf::Font* font, sf::Sound* sound, std::string text)
{
	this->body.setSize(sf::Vector2f(size.first, size.second));
	this->body.setPosition(sf::Vector2f(xPos, yPos));

	this->font = font;
	this->sound = sound;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textCharacterSize);

	this->text.setPosition(this->body.getPosition().x + (this->body.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f
		, this->body.getPosition().y + (this->body.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->body.setFillColor(this->idleColor);
	couldDown.restart();
}

Button::~Button()
{
}

void GraphView::loadAll() {
	//loading needed file's
	if (!this->EmptySpriteImage.loadFromFile("resources/empty_maze.jpg"))
		std::cout << "\nCan't load from the file. Err code " << this->LoadEmptyMazeFaleCode;
	if (!this->RightSpriteImage.loadFromFile("resources/right_maze.jpg"))
		std::cout << "\nCan't load from the file. Err code " << this->LoadRightMazeFaleCode;
	if (!this->BottomSpriteImage.loadFromFile("resources/bottom_maze.jpg"))
		std::cout << "\nCan't load from the file. Err code " << this->LoadBottomMazeFaleCode;
	if (!this->RbSpriteImage.loadFromFile("resources/rb_maze.jpg"))
		std::cout << "\nCan't load from the file. Err code " << this->LoadRbMazeFaleCode;

	this->EmptySpriteTexture.loadFromImage(this->EmptySpriteImage);
	this->RightSpriteTexture.loadFromImage(this->RightSpriteImage);
	this->BottomSpriteTexture.loadFromImage(this->BottomSpriteImage);
	this->RbSpriteTexture.loadFromImage(this->RbSpriteImage);

	this->EmptySpriteBody.setTexture(this->EmptySpriteTexture);
	this->RightSpriteBody.setTexture(this->RightSpriteTexture);
	this->BottomSpriteBody.setTexture(this->BottomSpriteTexture);
	this->RbSpriteBody.setTexture(this->RbSpriteTexture);
}

GraphView::GraphView()
{
	loadAll();
}

sf::Sprite& GraphView::getSprite(SpritesNumber neededNumber)
{
	switch (neededNumber)
	{
	case GraphView::EmptySprite: return this->EmptySpriteBody;
		break;
	case GraphView::RightSprite: return this->RightSpriteBody;
		break;
	case GraphView::BottomSprite: return this->BottomSpriteBody;
		break;
	case GraphView::RbSprite: return this->RbSpriteBody;
		break;
	default: return this->EmptySpriteBody;
		break;
	}

}



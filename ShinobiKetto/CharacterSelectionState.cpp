#include "CharacterSelectionState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

CharacterSelectionState::CharacterSelectionState(StateStack& stack, Context context)
	:State(stack, context)
	, mOptions()
	, mOptionIndex(0)
	, selectionCount(1)
{

	sf::Font& font = context.fonts->get(FontID::Main);

	backgroundSprite.setTexture(context.textures->get(TextureID::CharacterSelectionScreen));
	menuTitle.setFont(font);
	menuTitle.setString("Shinobi Selection");
	centerOrigin(menuTitle);
	menuTitle.setPosition(context.window->getView().getSize().x / 2, 100.f);

	//versusText.setFont(font);
	//versusText.setString("Versus");
	//versusText.setColor(sf::Color::Black);
	//centerOrigin(versusText);
	//versusText.setPosition(context.window->getView().getSize().x / 2, 150.f);

	p1Selection.setFont(font);
	p1Selection.setString("Player 1");
	centerOrigin(p1Selection);
	p1Selection.setPosition((context.window->getView().getSize().x / 2) - (context.window->getView().getSize().x / 4), 100.f);

	p2Selection.setFont(font);
	p2Selection.setString("Player 2");
	centerOrigin(p2Selection);
	p2Selection.setPosition((context.window->getView().getSize().x / 2) + (context.window->getView().getSize().x / 4), 100.f);

	sf::Text C1Option;
	c1PortraitTexture.loadFromFile("Media/Textures/Fight/hero1Avatar.png");

	c1Portrait.setTexture(c1PortraitTexture);
	c1Portrait.setPosition((context.window->getView().getSize().x / 2) - (context.window->getView().getSize().x / 4), (context.window->getView().getSize().y / 2) - 150);
	C1Option.setFont(font);
	C1Option.setString("Character 1");
	centerOrigin(C1Option);
	C1Option.setPosition(c1Portrait.getPosition().x + 65, c1Portrait.getPosition().y + 200);
	mOptions.push_back(C1Option);

	sf::Text C2Option;
	c2PortraitTexture.loadFromFile("Media/Textures/Fight/hero2Avatar.png");
	c2Portrait.setTexture(c2PortraitTexture);
	c2Portrait.setPosition(context.window->getView().getSize().x / 2, (context.window->getView().getSize().y / 2) - 150);
	C2Option.setFont(font);
	C2Option.setString("Character 2");
	centerOrigin(C2Option);
	C2Option.setPosition(c2Portrait.getPosition().x + 65, c2Portrait.getPosition().y + 200);
	mOptions.push_back(C2Option);

	sf::Text C3Option;
	c3PortraitTexture.loadFromFile("Media/Textures/Fight/hero3Avatar.png");
	c3Portrait.setTexture(c3PortraitTexture);
	c3Portrait.setPosition((context.window->getView().getSize().x / 2) + (context.window->getView().getSize().x / 4), (context.window->getView().getSize().y / 2) - 150);
	C3Option.setFont(font);
	C3Option.setString("Character 3");
	centerOrigin(C3Option);
	C3Option.setPosition(c3Portrait.getPosition().x + 65, c3Portrait.getPosition().y + 200);
	mOptions.push_back(C3Option);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Back");
	centerOrigin(exitOption);
	exitOption.setPosition((context.window->getView().getSize().x) - 150, (context.window->getView().getSize().y) - 200);
	mOptions.push_back(exitOption);

	updateOptionText();

	hudLeftFilePaths.insert(std::make_pair(OptionNames::C1, "Media/Textures/Fight/martialHero1HUDLeft.png"));
	hudLeftFilePaths.insert(std::make_pair(OptionNames::C2, "Media/Textures/Fight/martialHero2HUDLeft.png"));
	hudLeftFilePaths.insert(std::make_pair(OptionNames::C3, "Media/Textures/Fight/heroKnightHUDLeft.png"));
	hudRightFilePaths.insert(std::make_pair(OptionNames::C1, "Media/Textures/Fight/martialHero1HUDRight.png"));
	hudRightFilePaths.insert(std::make_pair(OptionNames::C2, "Media/Textures/Fight/martialHero2HUDRight.png"));
	hudRightFilePaths.insert(std::make_pair(OptionNames::C3, "Media/Textures/Fight/heroKnightHUDRight.png"));
	//context.music->play(MusicID::MenuTheme);
}

void CharacterSelectionState::draw()
{
	auto& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);
	window.draw(menuTitle);
	window.draw(c1Portrait);
	window.draw(c2Portrait);
	window.draw(c3Portrait);

	window.draw(p1Selection);
	window.draw(p2Selection);
	window.draw(p1SelectedChar);
	window.draw(p2SelectedChar);

	for (const auto& text : mOptions) {
		window.draw(text);
	}

}

bool CharacterSelectionState::update(sf::Time dt)
{
	return false;
}

bool CharacterSelectionState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == C1) {

			if (selectionCount == 1) {
				p1Char = Actor::Type::Hero1;
				*getContext().p1Char = p1Char;
				*getContext().hudLeftFilePath = hudLeftFilePaths[C1];
				p1SelectedChar = c1Portrait;
				p1SelectedChar.setPosition(p1Selection.getPosition().x + 20, p1Selection.getPosition().y + 50);

				selectionCount++;
			}
			else if (selectionCount == 2) {
				p2Char = Actor::Type::Hero1;
				*getContext().p2Char = p2Char;
				*getContext().hudRightFilePath = hudRightFilePaths[C1];
				p2SelectedChar = c1Portrait;
				p2SelectedChar.setPosition(p2Selection.getPosition().x + 20, p2Selection.getPosition().y + 50);

				selectionCount++;
			}
			else if (selectionCount >= 3) {
				if (event.type == sf::Event::KeyPressed)
				{
					requestStackPop();
					requestStackPush(StateID::MapSelection);
				}
			}



		}
		else if (mOptionIndex == C2) {

			if (selectionCount == 1) {
				p1Char = Actor::Type::Hero2;
				*getContext().p1Char = p1Char;
				*getContext().hudLeftFilePath = hudLeftFilePaths[C2];
				p1SelectedChar = c2Portrait;
				p1SelectedChar.setPosition(p1Selection.getPosition().x + 20, p1Selection.getPosition().y + 50);
				selectionCount++;
			}
			else if (selectionCount == 2) {
				p2Char = Actor::Type::Hero2;
				*getContext().p2Char = p2Char;
				*getContext().hudRightFilePath = hudRightFilePaths[C2];
				p2SelectedChar = c2Portrait;
				p2SelectedChar.setPosition(p2Selection.getPosition().x + 20, p2Selection.getPosition().y + 50);
				selectionCount++;
			}
			else if (selectionCount >= 3) {
				if (event.type == sf::Event::KeyPressed)
				{
					requestStackPop();
					requestStackPush(StateID::MapSelection);
				}
			}

		}
		else if (mOptionIndex == C3) {
			//FIND A WAY TO RETURN THE SELECTED CHARACTER FOR THE PLAYER
			if (selectionCount == 1) {
				p1Char = Actor::Type::Hero3;
				*getContext().p1Char = p1Char;
				*getContext().hudLeftFilePath = hudLeftFilePaths[C3];
				p1SelectedChar = c3Portrait;
				p1SelectedChar.setPosition(p1Selection.getPosition().x + 20, p1Selection.getPosition().y + 50);
				selectionCount++;
			}
			else if (selectionCount == 2) {
				p2Char = Actor::Type::Hero3;
				*getContext().p2Char = p2Char;
				*getContext().hudRightFilePath = hudRightFilePaths[C3];
				p2SelectedChar = c3Portrait;
				p2SelectedChar.setPosition(p2Selection.getPosition().x + 20, p2Selection.getPosition().y + 50);
				selectionCount++;
			}
			else if (selectionCount >= 3) {
				if (event.type == sf::Event::KeyPressed)
				{
					requestStackPop();
					requestStackPush(StateID::MapSelection);
				}
			}

		}
		//CHANGE FUNCTIONALITY TO GET BACK TO THE MAIN MENU
		else if (mOptionIndex == Exit) {
			requestStackPop();
			requestStackPush(StateID::Menu);
		}
	}
	else if (event.key.code == sf::Keyboard::Left) {
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Right) {
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return false;
}

void CharacterSelectionState::updateOptionText()
{
	if (mOptions.empty())
		return;
	for (auto& text : mOptions) {
		text.setFillColor(sf::Color::White);
	}
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

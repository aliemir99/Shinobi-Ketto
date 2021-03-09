#include "MapSelectionState.h"

#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
MapSelectionState::MapSelectionState(StateStack& stack, Context context)
	:State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	sf::Font& font = context.fonts->get(FontID::Main);
	backgroundSprite.setTexture(context.textures->get(TextureID::MapSelectionScreen));
	menuTitle.setFont(font);
	menuTitle.setString("Arena Selection");
	centerOrigin(menuTitle);
	menuTitle.setPosition(context.window->getView().getSize().x / 2, 100.f);

	m1PortraitTexture.loadFromFile("Media/Textures/Fight/map1Portrait.png");
	m1Portrait.setTexture(m1PortraitTexture);
	m1Portrait.setPosition((context.window->getView().getSize().x / 4) - 325, (context.window->getView().getSize().y / 2) - 150);
	sf::Text M1Option;
	M1Option.setFont(font);
	M1Option.setString("Jungle Hub");
	centerOrigin(M1Option);
	M1Option.setPosition(m1Portrait.getPosition().x + 100, m1Portrait.getPosition().y + 200);
	mOptions.push_back(M1Option);

	m2PortraitTexture.loadFromFile("Media/Textures/Fight/map2Portrait.png");
	m2Portrait.setTexture(m2PortraitTexture);
	m2Portrait.setPosition((context.window->getView().getSize().x / 4) + 100, (context.window->getView().getSize().y / 2) - 150);
	sf::Text M2Option;
	M2Option.setFont(font);
	M2Option.setString("Mystical Forest");
	centerOrigin(M2Option);
	M2Option.setPosition(m2Portrait.getPosition().x + 120, m2Portrait.getPosition().y + 200);
	mOptions.push_back(M2Option);


	m3PortraitTexture.loadFromFile("Media/Textures/Fight/map3Portrait.png");
	m3Portrait.setTexture(m3PortraitTexture);
	m3Portrait.setPosition((context.window->getView().getSize().x / 2) + 50, (context.window->getView().getSize().y / 2) - 150);
	sf::Text M3Option;
	M3Option.setFont(font);
	M3Option.setString("Dragon Lake");
	centerOrigin(M3Option);
	M3Option.setPosition(m3Portrait.getPosition().x + 100, m3Portrait.getPosition().y + 200);
	mOptions.push_back(M3Option);

	m4PortraitTexture.loadFromFile("Media/Textures/Fight/map4Portrait.png");
	m4Portrait.setTexture(m4PortraitTexture);
	m4Portrait.setPosition((context.window->getView().getSize().x / 2) + (context.window->getView().getSize().x / 4), (context.window->getView().getSize().y / 2) - 150);
	sf::Text M4Option;
	M4Option.setFont(font);
	M4Option.setString("Mushroom County");
	centerOrigin(M4Option);
	M4Option.setPosition(m4Portrait.getPosition().x + 150, m4Portrait.getPosition().y + 200);
	mOptions.push_back(M4Option);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Back");
	centerOrigin(exitOption);
	exitOption.setPosition((context.window->getView().getSize().x) - 150, (context.window->getView().getSize().y) - 200);
	mOptions.push_back(exitOption);

	backgroundFilePaths.insert(std::make_pair(OptionNames::M1, "Media/Textures/Fight/jungleBackground.png"));
	backgroundFilePaths.insert(std::make_pair(OptionNames::M2, "Media/Textures/Fight/map2Background.png"));
	backgroundFilePaths.insert(std::make_pair(OptionNames::M3, "Media/Textures/Fight/map3Background.png"));
	backgroundFilePaths.insert(std::make_pair(OptionNames::M4, "Media/Textures/Fight/map4Background.png"));

	platformFilePaths.insert(std::make_pair(OptionNames::M1, "Media/Textures/Fight/junglePlatform.png"));
	platformFilePaths.insert(std::make_pair(OptionNames::M2, "Media/Textures/Fight/forestPlatform.png"));
	platformFilePaths.insert(std::make_pair(OptionNames::M3, "Media/Textures/Fight/lakePlatform.png"));
	platformFilePaths.insert(std::make_pair(OptionNames::M4, "Media/Textures/Fight/countyPlatform.png"));

	updateOptionText();

	//context.music->play(MusicID::MenuTheme);
}

void MapSelectionState::draw()
{
	auto& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);
	window.draw(menuTitle);
	window.draw(m1Portrait);
	window.draw(m2Portrait);
	window.draw(m3Portrait);
	window.draw(m4Portrait);

	for (const auto& text : mOptions) {
		window.draw(text);
	}
}

bool MapSelectionState::update(sf::Time dt)
{
	return false;
}

bool MapSelectionState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == M1) {
			requestStackPop();
			*getContext().backGroundFilePath = backgroundFilePaths[M1];
			*getContext().platformfilePath = platformFilePaths[M1];
			getContext().music->setMusicType(MusicPlayer::MUSIC_TYPE::JUNGLE);

			requestStackPush(StateID::Game);
		}
		else if (mOptionIndex == M2) {
			*getContext().backGroundFilePath = backgroundFilePaths[M2];
			*getContext().platformfilePath = platformFilePaths[M2];
			getContext().music->setMusicType(MusicPlayer::MUSIC_TYPE::FOREST);
			requestStackPop();


			requestStackPush(StateID::Game);
		}
		else if (mOptionIndex == M3) {
			*getContext().backGroundFilePath = backgroundFilePaths[M3];
			*getContext().platformfilePath = platformFilePaths[M3];
			getContext().music->setMusicType(MusicPlayer::MUSIC_TYPE::LAKE);
			requestStackPop();
			requestStackPush(StateID::Game);
		}
		else if (mOptionIndex == M4) {
			*getContext().backGroundFilePath = backgroundFilePaths[M4];
			*getContext().platformfilePath = platformFilePaths[M4];
			getContext().music->setMusicType(MusicPlayer::MUSIC_TYPE::COUNTY);
			requestStackPop();
			requestStackPush(StateID::Game);
		}
		//CHANGE FUNCTIONALITY TO GET BACK TO THE MAIN MENU
		else if (mOptionIndex == Exit) {
			requestStackPop();
			requestStackPush(StateID::CharacterSelection);
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

void MapSelectionState::updateOptionText()
{
	if (mOptions.empty())
		return;
	for (auto& text : mOptions) {
		text.setFillColor(sf::Color::White);
	}
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

#include "Application.h"

#include "State.h"
#include "StateIdentifiers.h"

#include "GameState.h"
#include "TitleState.h"
#include "PauseState.h"
#include "MenuState.h"

#include "GameOverState.h"
#include "CharacterSelectionState.h"
#include "MapSelectionState.h"
#include "OptionsState.h"
#include "HowToPlayState.h"
#include "RoundOverState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : window(sf::VideoMode(1920, 1080), "Shinobi Ketto")
    , textures()
    , fonts()
    , player()
    , music()
    , sounds()
    , stateStack(State::Context(window, textures, fonts, player, music, sounds, p1Char, p2Char, backGroundFilePath, platformFilePath, hudLeftFilePath, hudRightFilePath))
    , statsText()
    , statsUpdateTime()
    , statsNumFrames(0)
    , skicon()

{
    window.setKeyRepeatEnabled(false);

    fonts.load(FontID::Main, "Media/GROBOLD.ttf");
    textures.load(TextureID::TitleScreen, "Media/Textures/Fight/shinobiKettoTitle.png");
    textures.load(TextureID::MenuScreen, "Media/Textures/Fight/menu.png");
    textures.load(TextureID::CharacterSelectionScreen, "Media/Textures/Fight/characterSelection.png");
    textures.load(TextureID::MapSelectionScreen, "Media/Textures/Fight/mapSelection.png");
    textures.load(TextureID::OptionsScreen, "Media/Textures/Fight/options.png");
    textures.load(TextureID::HowToPlayScreen, "Media/Textures/Fight/howtoplay.jpg");
    textures.load(TextureID::p1Controls, "Media/Textures/Fight/p1Controls.png");
    textures.load(TextureID::p2Controls, "Media/Textures/Fight/p2Controls.png");
    statsText.setFont(fonts.get(FontID::Main));
    statsText.setPosition(5.f, 5.f);
    statsText.setCharacterSize(10u);
    registerStates();
    stateStack.pushState(StateID::Title);

    skicon.loadFromFile("Media/Textures/Fight/skicon64x64.png");

    window.setIcon(64, 64, skicon.getPixelsPtr());

    music.setVolume(25.f);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {

        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

            if (stateStack.isEmpty())
                window.close();
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        stateStack.handleEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Application::update(sf::Time dt)
{
    stateStack.update(dt);
}

void Application::render()
{
    window.clear();
    stateStack.draw();

    window.setView(window.getDefaultView());

    window.draw(statsText);
    window.display();
}

void Application::updateStatistics(sf::Time et)
{
    statsUpdateTime += et;
    statsNumFrames += 1;

    if (statsUpdateTime >= sf::seconds(1.0f)) {

        statsText.setString(
            "Frames/ Second = " + std::to_string(statsNumFrames) + "\n" +
            "Time/ Update = " + std::to_string(statsUpdateTime.asMicroseconds() / statsNumFrames) + "us"
        );
        statsUpdateTime -= sf::seconds(1.0f);
        statsNumFrames = 0;
    }
}

void Application::registerStates()
{
    stateStack.registerState<TitleState>(StateID::Title);
    stateStack.registerState<MenuState>(StateID::Menu);
    stateStack.registerState<OptionsState>(StateID::Options);
    stateStack.registerState<HowToPlayState>(StateID::HowToPlay);
    stateStack.registerState<CharacterSelectionState>(StateID::CharacterSelection);
    stateStack.registerState<MapSelectionState>(StateID::MapSelection);
    stateStack.registerState<GameState>(StateID::Game);
    stateStack.registerState<PauseState>(StateID::Pause);
    stateStack.registerState<RoundOverState>(StateID::RoundOver);
    stateStack.registerState<GameOverState>(StateID::GameOver);

}

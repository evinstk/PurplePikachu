#include <TEMM/Application.hpp>
#include <TEMM/TitleState.hpp>
#include <TEMM/GameState.hpp>
#include <TEMM/LuaGameState.hpp>
#include <SFML/Window/Event.hpp>

namespace temm
{
	Application::Application(float fps)
		: mWindow(sf::VideoMode(1024, 768), "Purple Pikachu", sf::Style::Close)
		, mTextures()
		, mKeyBinding1(1)
		, mStateStack(State::Context(mWindow, mTextures, mKeyBinding1))
		, mTimePerFrame(sf::seconds(1.f / fps))
	{
		mWindow.setKeyRepeatEnabled(false);

		registerStates();
		mStateStack.pushState(States::Lua, "res/lua/test.lua");
	}

	void Application::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while (mWindow.isOpen())
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > mTimePerFrame)
			{
				timeSinceLastUpdate -= mTimePerFrame;

				processInput();
				update(mTimePerFrame);

				if (mStateStack.isEmpty())
					mWindow.close();
			}
			render();
		}
	}

	void Application::registerStates()
	{
		mStateStack.registerState<TitleState>(States::Title);
		mStateStack.registerState<GameState>(States::Game);
		mStateStack.registerState<LuaGameState>(States::Lua);
	}

	void Application::processInput()
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			mStateStack.handleEvent(event);
			if (event.type == sf::Event::Closed) mWindow.close();
		}
	}

	void Application::update(sf::Time dt)
	{
		mStateStack.update(dt);
	}

	void Application::render()
	{
		mWindow.clear();
		mStateStack.draw();
		mWindow.setView(mWindow.getDefaultView());
		mWindow.display();
	}
}

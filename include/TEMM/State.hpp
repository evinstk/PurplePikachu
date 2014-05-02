#ifndef TEMM_STATE_HPP
#define TEMM_STATE_HPP

#include <TEMM/ResourceIdentifiers.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace temm
{
	class StateStack;
	class KeyBinding;

	namespace States
	{
		enum ID
		{
			Title,
			Game,
			None,
		};
	}

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;
		struct Context
		{
			Context(sf::RenderWindow& window, TextureHolder& textures, KeyBinding& keys1);

			sf::RenderWindow* window;
			TextureHolder* textures;
			KeyBinding* keys1;
		};

		State(StateStack& stack, Context context);
		virtual ~State();

		virtual void load(const std::string& filename);
		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;
	protected:
		void requestStackPush(States::ID stateID);
		void requestStackPop();
		void requestStackClear();

		Context getContext() const;
	private:
		StateStack* mStack;
		Context mContext;
	};
}

#endif

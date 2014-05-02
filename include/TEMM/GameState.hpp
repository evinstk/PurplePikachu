#ifndef TEMM_GAME_STATE_HPP
#define TEMM_GAME_STATE_HPP

#include <TEMM/State.hpp>
#include <TEMM/Overworld.hpp>
#include <TEMM/Player.hpp>

namespace temm
{
    class GameState : public State
    {
    public:
        GameState(StateStack& stack, Context context);

        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);

	private:
		template<typename DerivedState> friend class LuaState;

		Overworld mOverworld;
		Player mPlayer;
    };
}

#endif

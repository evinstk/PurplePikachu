#ifndef TEMM_CATEGORY_HPP
#define TEMM_CATEGORY_HPP

namespace temm
{

	// Serves dual purpose of command dispatch
	// and collision masking
	namespace Category
	{
		enum Type
		{
			None = 0,
			Player = 1 << 0,
			NPC = 1 << 1,
			Ridge = 1 << 2,
			Bush = 1 << 3,
			Static = 1 << 4,

			Character = Player | NPC,
		};
	}
}

#endif
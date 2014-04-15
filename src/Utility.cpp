#include <TEMM/Utility.hpp>
#include <cmath>

namespace temm
{

	float length(sf::Vector2f vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

}
#ifndef TEMM_TYPEDEFS_HPP
#define TEMM_TYPEDEFS_HPP

#include <map>
#include <vector>

namespace temm
{

	struct NodeObject
	{
		NodeObject(const std::string& type, int x, int y, bool isPlayer)
		: type(type)
		, x(x)
		, y(y)
		, isPlayer(isPlayer)
		{
		}

		std::string type;
		int x;
		int y;
		bool isPlayer;
	};

	typedef std::map<int, std::vector<int>> TileLayers;
	typedef std::map<int, std::vector<NodeObject>> ObjectLayers;

}

#endif

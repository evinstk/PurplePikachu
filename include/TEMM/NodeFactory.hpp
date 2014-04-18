#ifndef TEMM_NODE_FACTORY_HPP
#define TEMM_NODE_FACTORY_HPP

#include <TEMM/SceneNode.hpp>
#include <map>

namespace temm
{
	struct CmpStr
	{
		bool operator()(char const* a, char const* b);
	};

	class NodeFactory
	{
	public:
		void registerNode(char* stringID, const std::function<SceneNode::Ptr()>& constructor);
		void registerNode(char* stringID, std::function<SceneNode::Ptr()>&& constructor);

		SceneNode::Ptr get(char* stringID);

	private:
		std::map<char*, std::function<SceneNode::Ptr()>, CmpStr> mFactories;
	};

}

#endif

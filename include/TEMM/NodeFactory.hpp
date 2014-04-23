#ifndef TEMM_NODE_FACTORY_HPP
#define TEMM_NODE_FACTORY_HPP

#include <TEMM/SceneNode.hpp>
#include <map>

namespace temm
{
	struct CmpStr
	{
		bool operator()(const std::string& a, const std::string& b);
	};

	class NodeFactory
	{
	public:
		void registerNode(const std::string& stringID, const std::function<SceneNode::Ptr()>& constructor);
		void registerNode(const std::string& stringID, std::function<SceneNode::Ptr()>&& constructor);

		SceneNode::Ptr get(const std::string& stringID);

	private:
		std::map<std::string, std::function<SceneNode::Ptr()>, CmpStr> mFactories;
	};

}

#endif

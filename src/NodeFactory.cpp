#include <TEMM/NodeFactory.hpp>
#include <cassert>

namespace temm
{
	bool CmpStr::operator()(const std::string& a, const std::string& b)
	{
		return std::strcmp(a.c_str(), b.c_str()) < 0;
	}

	void NodeFactory::registerNode(const std::string& stringID, const std::function<SceneNode::Ptr()>& constructor)
	{
		mFactories[stringID] = constructor;
	}

	void NodeFactory::registerNode(const std::string& stringID, std::function<SceneNode::Ptr()>&& constructor)
	{
		mFactories[stringID] = std::move(constructor);
	}

	SceneNode::Ptr NodeFactory::get(const std::string& stringID)
	{
		auto found = mFactories.find(stringID);
		assert(found != mFactories.end());

		return found->second();
	}

}

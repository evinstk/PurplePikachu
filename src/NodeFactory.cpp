#include <TEMM/NodeFactory.hpp>
#include <cassert>

namespace temm
{
	bool CmpStr::operator()(char const* a, char const* b)
	{
		return std::strcmp(a, b) < 0;
	}

	void NodeFactory::registerNode(char* stringID, const std::function<SceneNode::Ptr()>& constructor)
	{
		mFactories[stringID] = constructor;
	}

	void NodeFactory::registerNode(char* stringID, std::function<SceneNode::Ptr()>&& constructor)
	{
		mFactories[stringID] = std::move(constructor);
	}

	SceneNode::Ptr NodeFactory::get(char* stringID)
	{
		auto found = mFactories.find(stringID);
		assert(found != mFactories.end());

		return found->second();
	}

}

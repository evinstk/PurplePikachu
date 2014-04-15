#include <TEMM/SceneNode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace temm
{

	SceneNode::SceneNode(Category::Type category)
		: mDefaultCategory(category)
	{
	}

	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		RenderLists renderLists;
		draw(target, states, renderLists);

		for (unsigned i = 0; i < renderLists.size(); ++i)
		{
			for (auto& fun : renderLists[i])
			{
				fun();
			}
		}
	}

	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const
	{
		states.transform *= getTransform();

		pushCurrent(target, states, renderLists);
		pushChildren(target, states, renderLists);
	}

	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates) const
	{
		// Do nothing by default
	}

	void SceneNode::pushCurrent(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const
	{	
		renderLists[z].push_back([=, &target](void) {
			drawCurrent(target, states);
		});
	}

	void SceneNode::pushChildren(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const
	{
		for (auto& child : mChildren)
			child->draw(target, states, renderLists);
	}

}
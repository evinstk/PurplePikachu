#include <TEMM/SceneNode.hpp>
#include <TEMM/Command.hpp>
#include <TEMM/Utility.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

namespace temm
{

	SceneNode::SceneNode(unsigned z, Category::Type category)
		: z(z)
		, mDefaultCategory(category)
		, mChildren()
		, mParent(nullptr)
	{
	}

	void SceneNode::attachChild(Ptr child)
	{
		child->mParent = this;
		mChildren.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) {return p.get() == &node; });
		assert(found != mChildren.end());

		Ptr result = std::move(*found);
		result->mParent = nullptr;
		mChildren.erase(found);
		return result;
	}

	void SceneNode::onCommand(const Command& command, sf::Time dt)
	{
		if (command.category & getCategory())
			command.action(*this, dt);

		for (Ptr& child : mChildren)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return mDefaultCategory;
	}

	void SceneNode::update(sf::Time dt, CommandQueue& commands)
	{
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	void SceneNode::resolveSceneCollisions(SceneNode& sceneGraph)
	{
		resolveNodeCollisions(sceneGraph);

		for (Ptr& child : sceneGraph.mChildren)
		{
			resolveSceneCollisions(*child);
		}
	}

	void SceneNode::resolveNodeCollisions(SceneNode& node)
	{
		resolveCurrent(node);
		resolveChildren(node);
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;

		for (const SceneNode* node = this; node != nullptr; node = node->mParent)
			transform = node->getTransform() * transform;

		return transform;
	}

	sf::FloatRect SceneNode::getBoundingRect() const
	{
		return sf::FloatRect();
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// Nothing by default
	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (Ptr& child : mChildren)
			child->update(dt, commands);
	}

	void SceneNode::resolveCurrent(SceneNode& node)
	{
		// Nothing by default
	}

	void SceneNode::resolveChildren(SceneNode& node)
	{
		for (Ptr& child : mChildren)
			child->resolveNodeCollisions(node);
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
		if (renderLists.size() < z + 1)
			renderLists.resize(z + 1);

		renderLists[z].push_back([=, &target](void) {
			drawCurrent(target, states);
		});
	}

	void SceneNode::pushChildren(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const
	{
		for (auto& child : mChildren)
			child->draw(target, states, renderLists);
	}

	bool SceneNode::collides(const SceneNode& node) const
	{
		return getBoundingRect().intersects(node.getBoundingRect());
	}

	float SceneNode::distance(const SceneNode& node) const
	{
		return length(getWorldPosition() - node.getWorldPosition());
	}

}

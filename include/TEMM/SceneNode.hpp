#ifndef TEMM_SCENE_NODE_HPP
#define TEMM_SCENE_NODE_HPP

#include <TEMM/Category.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <vector>
#include <list>
#include <functional>

namespace sf
{
	class Time;
}

namespace temm
{
	struct Command;
	class CommandQueue;

	class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:

		typedef std::unique_ptr<SceneNode> Ptr;

		explicit SceneNode(unsigned z, Category::Type category = Category::None);

		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

		void onCommand(const Command& command, sf::Time dt);
		virtual unsigned int getCategory() const;
		void update(sf::Time dt, CommandQueue& commands);

		sf::Vector2f getWorldPosition() const;
		sf::Transform getWorldTransform() const;
		virtual sf::FloatRect getBoundingRect() const;

		unsigned z;

	private:
		friend class SceneNode;
		typedef std::vector<std::list<std::function<void (void)>>> RenderLists;

		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		void updateChildren(sf::Time dt, CommandQueue& commands);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates) const;
		void pushCurrent(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;
		void pushChildren(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;

		Category::Type mDefaultCategory;
		SceneNode* mParent;
		std::vector<Ptr> mChildren;
	};

	bool collision(const SceneNode& lhs, const SceneNode& rhs);
	float distance(const SceneNode& lhs, const SceneNode& rhs);
}

#endif
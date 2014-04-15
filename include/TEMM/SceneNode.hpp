#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <TEMM/Category.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <vector>
#include <list>
#include <functional>

namespace temm
{

	class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:

		typedef std::unique_ptr<SceneNode> Ptr;

		explicit SceneNode(Category::Type category = Category::None);

		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

		unsigned z;

	private:
		friend class SceneNode;
		typedef std::vector<std::list<std::function<void (void)>>> RenderLists;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates) const;
		void pushCurrent(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;
		void pushChildren(sf::RenderTarget& target, sf::RenderStates states, RenderLists& renderLists) const;

		Category::Type mDefaultCategory;
		SceneNode* mParent;
		std::vector<Ptr> mChildren;
	};

}

#endif
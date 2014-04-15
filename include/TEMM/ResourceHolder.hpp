#ifndef TEMM_RESOURCE_HOLDER_HPP
#define TEMM_RESOURCE_HOLDER_HPP

#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <cassert>

namespace temm
{

	template <typename Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		void load(Identifier id, const std::string& filename);

		template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& secondParam);

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;

	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource);

		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	};

}

#include "ResourceHolder.inl"
#endif
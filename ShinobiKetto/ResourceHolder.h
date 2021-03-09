#pragma once
#include <string>
#include <memory>
#include <map>
#include <assert.h>
#include <stdexcept> 

template <typename R, typename Id>


class ResourceHolder
{
public:
	void					load(Id id, const std::string& filename);

	template <typename P>
	void					load(Id id, const std::string& filename, const P& secondParam);

	const R& get(Id id)const;
	R& get(Id id);

private:
	void					insertResource(Id id, std::unique_ptr<R> resource);

private:
	std::map <Id, std::unique_ptr<R>> resourceMap;

};

template <typename R, typename Id>
void ResourceHolder<R, Id>::load(Id id, const std::string& filename) {
	std::unique_ptr<R> resource(new R());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}


template <typename R, typename Id>
template <typename P>
void ResourceHolder<R, Id>::load(Id id, const std::string& filename, const P& secondParam) {
	// Create and load resource
	std::unique_ptr<R> resource(new R());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}


template <typename R, typename Id>
R& ResourceHolder<R, Id>::get(Id id) {
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());
	return *found->second;
}


template <typename R, typename Id>
const R& ResourceHolder<R, Id>::get(Id id) const {
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());
	return *found->second;
}


template <typename R, typename Id>
void ResourceHolder<R, Id>::insertResource(Id id, std::unique_ptr<R> resource)
{
	// Insert and check success
	auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

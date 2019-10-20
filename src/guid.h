#pragma once
#include <vector>
#include <string>
#include <uuid.h>

/// Globally Unique Identifier
/// This is used appended to each object in the database
/// it makes each object unique even if it shares a type with other objects
/// so you can have an array of an object and modify certain elements of the same type
/// by getting a certain object by id
class Guid
{
	uuids::uuid id;

public:

	//todo could be optimized
	constexpr inline const bool isInitialized() noexcept { return id.is_nil(); }

	Guid generate();
	inline std::string text() { return uuids::to_string(id); }

	inline constexpr uuids::uuid getUUID() noexcept { return this->id; }
};

/// The book keeper of all guids loaded into a scene
/// this 
class GuidManager final {

	std::vector<Guid> guids;

	//todo : open xml file, parse every guid and add to table
	GuidManager() {}

public:

	inline static GuidManager& instance() {
		static GuidManager m;
		return m;
	}
	//implement this
	const bool hasCollision(Guid) const { return false; }


};



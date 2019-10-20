#pragma once
#include <vector>
#include <string>
#include "include/UUID/uuid.h"

/// Globally Unique Identifier
/// This is used appended to each object in the database
/// it makes each object unique even if it shares a type with other objects
/// so you can have an array of an object and modify certain elements of the same type
/// by getting a certain object by id
class Guid
{
	uuids::uuid id;

public:

	inline std::string text() { return uuids::to_string(id.value()); }

};

/// The book keeper of all guids loaded into a scene
/// this 
class GuidManager final {
	inline static GuidManager& instance() {
		static GuidManager m;
		return m;
	}

	std::vector<Guid> guids;
}



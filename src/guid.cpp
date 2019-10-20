#include "guid.h"

Guid Guid::generate() { 
	id = uuids::uuid_system_generator{}(); 
	while (GuidManager::instance().hasCollision(*this)) 
		id = uuids::uuid_system_generator{}();  
	return *this; 
}

#include "dictionary.hpp"

namespace lang {

Dictionary::Dictionary() : xml("xmlSpec/cache.xml") {
	auto map = xml.getXmlData();
	
	for (const auto& var : map) {
		this->hashMap.insert({ var.first, Blob::fromString(var.second) });
	}
}

}
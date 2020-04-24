#include "dictionary.hpp"

namespace lang {

Dictionary::Dictionary() : xml("xmlSpec/cache.xml") {
	auto map = xml.getXmlData();
	for (const auto& var : map) {
		blob::Blob b;
		b.fromString(var.second); //todo make this return a blob retard
		this->hashMap.insert({ var.first, b });
	}
}

}
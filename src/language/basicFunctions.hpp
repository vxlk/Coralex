#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <algorithm>

namespace lang {

/// the building blocks of the language
namespace basicFunctions {

	static auto add = [](const auto& lhs, const auto& rhs) { return lhs + rhs; };

	static auto subtract = [](const auto& lhs, const auto& rhs) { return lhs - rhs; };

	static auto divide = [](const auto& lhs, const auto& rhs) { return lhs / rhs; };

	static auto multiply = [](const auto& lhs, const auto& rhs) { return lhs * rhs; };


}//namespace basicFunctions
}//namespace lang

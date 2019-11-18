#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <algorithm>

namespace lang {

/// the building blocks of the language
namespace basicFunctions {

	auto add = [](const auto& lhs, const auto& rhs) { return lhs + rhs; };

	auto subtract = [](const auto& lhs, const auto& rhs) { return lhs - rhs; };

	auto divide = [](const auto& lhs, const auto& rhs) { return lhs / rhs; };

	auto multiply = [](const auto& lhs, const auto& rhs) { return lhs * rhs; };


}//namespace basicFunctions
}//namespace lang

#include <utility>
#include <array>

#include <fmt/core.h>


namespace gp {
	enum class selector {
		logo
	};

	static constexpr auto database = std::array{
		"GP"
	};

	auto gen(selector s) -> std::string
	{
		return database[std::to_underlying(s)];
	}
}

#include <string>

namespace gp {
	enum class selector {
		logo
	};

	auto gen(selector s) -> std::string;
}

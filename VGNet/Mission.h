#pragma once
#include <functional>
#include <cstdint>

struct Mission {
	bool enabled = false;
	int64_t id;
	std::function<void()> cancelCallback;
};
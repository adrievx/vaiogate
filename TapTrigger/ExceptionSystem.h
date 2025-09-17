#pragma once
#include <exception>

std::exception* TriggerException(std::exception* ex, const char* message);
void DestroyBadAlloc(std::bad_alloc* ex);
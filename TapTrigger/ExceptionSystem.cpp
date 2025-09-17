#include "ExceptionSystem.h"

std::exception* TriggerException(std::exception* ex, const char* message) {
    return new (ex) std::bad_alloc();
}

void DestroyBadAlloc(std::bad_alloc* ex) {
	if (ex != nullptr) {
		ex->~bad_alloc();
	}
}

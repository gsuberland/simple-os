#include <std/compiler.h>
#include <threading/atomic_bool.h>
#include <interrupts.h>

bool threading::atomic_bool::test_and_set() {
	bool old = 0;

	ASM_VOLATILE("bts %1, 1\n\t" // Turn on zero-based bit #Offset in Base.
		"sbb %0,%0"      // Use the CF to calculate old.
		: "=r" (old), "+rm" (_value)
		:
		: "cc");

	return old;
}

void threading::atomic_bool::clear() {
	_value = 0;
}
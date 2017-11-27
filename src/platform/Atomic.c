#include "Atomic.h"


etool_atomic* etool_atomic_create(const int count)
{
	etool_atomic *atomic = malloc(sizeof(etool_atomic));
	if (atomic == 0) { return 0; }
	atomic->count = count;
	return atomic;
}

void etool_atomic_destroy(etool_atomic *atomic)
{
	free(atomic);
}

int etool_atomic_inc(etool_atomic *atomic)
{
#if defined(_windows)
	return InterlockedIncrement(&(atomic->count));
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_add_and_fetch(&(atomic->count), 1);
#endif
}

int etool_atomic_dec(etool_atomic *atomic)
{
#if defined(_windows)
	return InterlockedDecrement(&(atomic->count));
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_sub_and_fetch(&(atomic->count), 1);
#endif
}

int etool_atomic_add(etool_atomic *atomic, const int count)
{
#if defined(_windows)
	return InterlockedExchangeAdd(&(atomic->count), count);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_add_and_fetch(&(atomic->count), count);
#endif
}

int etool_atomic_sub(etool_atomic *atomic, const int count)
{
#if defined(_windows)
	return InterlockedExchangeAdd(&(atomic->count), -count);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_sub_and_fetch(&(atomic->count), count);
#endif
}

int etool_atomic_or(etool_atomic *atomic, const int count)
{
#if defined(_windows)
	return InterlockedOr(&(atomic->count), count);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_or_and_fetch(&(atomic->count), count);
#endif
}

int etool_atomic_and(etool_atomic *atomic, const int count)
{
#if defined(_windows)
	return InterlockedAnd(&(atomic->count), count);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_and_and_fetch(&(atomic->count), count);
#endif
}

int etool_atomic_xor(etool_atomic *atomic, const int count)
{
#if defined(_windows)
	return InterlockedXor(&(atomic->count), count);
#endif

#if defined(_linux) || defined(_android) || defined(_mac) || defined(_ios)
	return __sync_xor_and_fetch(&(atomic->count), count);
#endif
}
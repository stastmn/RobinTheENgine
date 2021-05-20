#pragma once


#if ASSERTIONS_ENABLED

// определ€ем некоторую функцию ассемблера, котора€ вызывает отладчик, Ч 
// он будет различным дл€ каждого целевого процессора

#define debugBreak() asm { int 3 }

// провер€ем, ложно ли выражение 
#define ASSERT(expr) \
	if (expr) { } \
	else { \
		reportAssertionFailure(#expr, __FILE__, __LINE__); \
	debugBreak(); \
	}

#else

#define ASSERT(expr)  // ничего не вычисл€ем

#endif


#define _ASSERT_GLUE(a, b)  a ## b
#define ASSERT_GLUE(a, b)   _ASSERT_GLUE(a, b)

#define STATIC_ASSERT(expr) \
    enum \
	{ \
        ASSERT_GLUE(g_assert_fail_, __LINE__) \
            = 1 / (int)(!!(expr)) \
    }

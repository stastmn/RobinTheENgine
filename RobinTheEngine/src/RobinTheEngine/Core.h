#pragma once

#ifdef RTE_PLATFORM_WINDOWS
	#ifdef RTE_BUILD_DLL
	#define RTE_API __declspec(dllexport)
	#else 
	#define RTE_API __declspec(dllimport)
	#endif // RTE_BUILD_DLL

#else
	#error Now only Windows support!
#endif // RTE_PLATFORM_WINDOWS


#ifdef RTE_ENABLE_ASSERTS
	#define RTE_ASSERT(x, ...) { if(x){} else { RTE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RTE_CORE_ASSERT(x, ...) { if(x){} else { RTE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define _ASSERT_GLUE(a, b)  a ## b
	#define ASSERT_GLUE(a, b)   _ASSERT_GLUE(a, b)
	#define STATIC_ASSERT(expr) \
		enum \
		{ \
			ASSERT_GLUE(g_assert_fail_, __LINE__) = 1 / (int)(!!(expr)) \
		}
#else
	#define RTE_ASSERT(x, ...)
	#define RTE_CORE_ASSERT(x, ...)
	#define STATIC_ASSERT(expr)
#endif


#define BIT(x) (1 << x) 

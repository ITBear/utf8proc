#pragma once

#include "../GpCore/GpCore.hpp"

#if defined(UTF8PROC_LIBRARY)
	#define UTF8PROC_API GP_DECL_EXPORT
#else
	#define UTF8PROC_API GP_DECL_IMPORT
#endif

using namespace GPlatform;

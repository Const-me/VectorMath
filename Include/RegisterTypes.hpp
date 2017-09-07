#pragma once
#include "Config.h"

#if CVM_SSE > 20
#include <xmmintrin.h>

namespace cvm
{
	using VECTOR = __m128;
}
#define VCALL __vectorcall

#else
static_assert( false, "Unknown target" );
#endif
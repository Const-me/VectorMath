#include "BasicMath.hpp"

namespace cvm
{
	namespace impl
	{
#if CVM_SSE
		const VECTOR s_signBits = _mm_set1_ps( -0.0f );
#endif
	}
}
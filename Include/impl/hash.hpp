#pragma once
#include <stdint.h>

namespace cvm
{
	namespace impl
	{
#if CVM_SSE
		inline size_t VCALL hash3( VECTOR a )
		{
			uint32_t align( 16 ) tmp[ 4 ];
			_mm_store_ps( (float*)tmp, a );
			// simplify( (((17 * 31)+x)*31+y)*31+z );
			// 506447 + 961 * x + 31 * y + z

			return (size_t)506447 + (size_t)961 * tmp[ 0 ] + (size_t)31 * tmp[ 1 ] + tmp[ 2 ];
		}

		inline size_t VCALL hash4( VECTOR a )
		{
			uint32_t align( 16 ) tmp[ 4 ];
			_mm_store_ps( (float*)tmp, a );
			// simplify(((((17 * 31)+x)*31+y)*31+z)*31+w);
			// 15699857 + 29791 * x + 961 * y + 31 * z + w

			return (size_t)15699857 + (size_t)29791 * tmp[ 0 ] + (size_t)961 * tmp[ 1 ] + (size_t)31 * tmp[ 2 ] + tmp[ 3 ];
		}
#endif
	}
}
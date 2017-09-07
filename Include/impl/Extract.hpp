#pragma once
#include "../RegisterTypes.hpp"
#include "BasicMath.hpp"

namespace cvm
{
	namespace impl
	{
		template<int n>
		inline float VCALL extract( VECTOR a );

#if CVM_SSE
		template<>
		inline float VCALL extract<0>( VECTOR a )
		{
			return _mm_cvtss_f32( a );
		}
#if __SSE4_1__
		template<int n>
		inline float VCALL extract( VECTOR a )
		{
			float res;
			_MM_EXTRACT_FLOAT( res, a, n );
			return res;
		}
#else
		template<int n>
		inline float VCALL extract( VECTOR a )
		{
			return _mm_cvtss_f32( permute<n, n, n, n>( a ) );
		}
#endif

#elif CVM_NEON
		template<int n>
		inline float VCALL extract( VECTOR a );
		{
			return vgetq_lane_f32( a, n );
		}
#else
		static_assert( false, "Unknown target" );
#endif
	}
}
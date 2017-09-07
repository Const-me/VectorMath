#pragma once
#include "../RegisterTypes.hpp"

namespace cvm
{
	namespace impl
	{
		inline VECTOR VCALL vectorAdd( VECTOR a, VECTOR b )
		{
#if CVM_SSE
			return _mm_add_ps( a, b );
#elif CVM_NEON
			return vaddq_f32( a, b );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline VECTOR VCALL vectorSub( VECTOR a, VECTOR b )
		{
#if CVM_SSE
			return _mm_sub_ps( a, b );
#elif CVM_NEON
			return vsubq_f32( a, b );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline VECTOR VCALL vectorNeg( VECTOR a )
		{
#if CVM_SSE
			// https://stackoverflow.com/a/3528787/126995
			return _mm_xor_ps( a, _mm_set1_ps( -0.f ) )
#elif CVM_NEON
			return vneg_f32( a );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline VECTOR VCALL vectorMul( VECTOR a, VECTOR b )
		{
#if CVM_SSE
			return _mm_mul_ps( a, b );
#elif CVM_NEON
			return vmulq_f32( a, b );
#else
			static_assert( false, "Unknown target" );
#endif
		}


#ifdef CVM_SSE
		template<int imm>
		inline VECTOR VCALL permute( VECTOR a )
		{
			return _mm_shuffle_ps( a, a, imm );
		}
		template<int i1, int i2, int i3, int i4>
		inline VECTOR VCALL permute( VECTOR a )
		{
			return permute<_MM_SHUFFLE( i1, i2, i3, i4 )>( a );
		}
#endif
	}
}
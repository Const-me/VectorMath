#pragma once
#include "../RegisterTypes.hpp"
#include <stdint.h>

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
#endif
		}

		inline VECTOR VCALL vectorNeg( VECTOR a )
		{
#if CVM_SSE
			// https://stackoverflow.com/a/3528787/126995
			return _mm_xor_ps( a, _mm_set1_ps( -0.0f ) );
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

		// 3D cross-product. The result's W component will be garbage.
		inline VECTOR VCALL cross3( VECTOR a, VECTOR b )
		{
			// http://threadlocalmutex.com/?p=8
			__m128 a_yzx = permute<3, 0, 2, 1>( a );
			__m128 b_yzx = permute<3, 0, 2, 1>( b );
			__m128 c = _mm_sub_ps( _mm_mul_ps( a, b_yzx ), _mm_mul_ps( a_yzx, b ) );
			return permute<3, 0, 2, 1>( c );
		}

		// Dot product of a.xyz and b.xyz, in all 4 components of the result
		inline VECTOR VCALL dot3( VECTOR a, VECTOR b )
		{
#if __SSE4_1__
			return _mm_dp_ps( a, b, 0x7F );
#else
			__m128 result = _mm_mul_ps( a, a );	// [xyzw]^2
			const __m128 p1 = _mm_movehl_ps( result, result ); // [zwzw]^2
			const __m128 p2 = permute<3, 3, 3, 1>( result );	// [ywww]^2

			// Sum all 3 vectors
			const __m128 a1 = _mm_add_ps( result, p1 );
			result = _mm_add_ps( a1, p2 );

			// Broadcast x component
			return permute<0, 0, 0, 0>( result );
#endif // __SSE4_1__
		}

		// Divide the vector by the length of a.xyz; w component is divided as well
		inline VECTOR VCALL normalize3( VECTOR a )
		{
			__m128 result = dot3( a, a );
			result = _mm_sqrt_ps( result );
			return _mm_div_ps( a, result );
		}

		// Dot product of a and b, in all 4 components of the result.
		inline VECTOR VCALL dot4( VECTOR a, VECTOR b )
		{
#if __SSE4_1__
			return _mm_dp_ps( a, b, 0xFF );
#else
			__m128 result = _mm_mul_ps( a, a );	// [xyzw]^2
			const __m128 p1 = _mm_movehl_ps( result, result ); // [zwzw]^2
			const __m128 p2 = permute<3, 3, 3, 1>( result );	// [ywww]^2
			const __m128 p3 = _mm_movehl_ps( p2, p2 ); // [wwww]^2

			// Sum all 3 vectors
			const __m128 a1 = _mm_add_ps( result, p1 );
			const __m128 a2 = _mm_add_ps( p2, p3 );
			result = _mm_add_ps( a1, a2 );

			// Broadcast x component
			return permute<0, 0, 0, 0>( result );
#endif // __SSE4_1__
		}

		// Normalize a 4D vector
		inline VECTOR VCALL normalize4( VECTOR a )
		{
			__m128 result = dot4( a, a );
			result = _mm_sqrt_ps( result );
			return _mm_div_ps( a, result );
		}

		// Project a 4D vector onto W=1.0 space
		inline VECTOR VCALL divideByW( VECTOR a )
		{
			VECTOR wwww = permute<3, 3, 3, 3>( a );
			return _mm_div_ps( a, wwww );
		}
#endif // CVM_SSE
	}
}
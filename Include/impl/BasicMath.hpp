#pragma once
#include "../RegisterTypes.hpp"
#include "Permute.hpp"
#include <stdint.h>
#if __SSE4_0__ || __SSE4_1__
#include <smmintrin.h>
#endif

namespace cvm
{
	namespace impl
	{
#if CVM_SSE
		// The highest (=sign) bits of all 4 components are set, rest are 0. The constant is used for faster negate/abs operations on x86, bitwise operations are very fast
		extern const VECTOR s_signBits;
#endif
		inline VECTOR VCALL vectorZero()
		{
#if CVM_SSE
			return _mm_setzero_ps();
#elif CVM_NEON
			return vdupq_n_f32( 0 );
#else
			static_assert( false, "Unknown target" );
#endif
		}

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
			return _mm_xor_ps( a, s_signBits );
#elif CVM_NEON
			return vnegq_f32( a );
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
#elif CVM_NEON
		// https://pyra-handheld.com/boards/threads/fast-neon-3-term-cross-product.52091/
		inline __attribute__( ( always_inline ) ) void cross3_neon_vld3_vst3_asm_4x( float const* v1, float const* v2, float* result )
		{
			unsigned int const offset = 16; // 128-bit vectors

			asm volatile(
				"vld3.f32 {d0[0], d2[0], d4[0]}, [%[v1]], %[offset]         \n\t"
				"vld3.f32 {d0[1], d2[1], d4[1]}, [%[v1]], %[offset]         \n\t"
				"vld3.f32 {d1[0], d3[0], d5[0]}, [%[v1]], %[offset]         \n\t"
				"vld3.f32 {d1[1], d3[1], d5[1]}, [%[v1]], %[offset]         \n\t"
				"vld3.f32 {d16[0], d18[0], d20[0]}, [%[v2]], %[offset]      \n\t"
				"vld3.f32 {d16[1], d18[1], d20[1]}, [%[v2]], %[offset]      \n\t"
				"vld3.f32 {d17[0], d19[0], d21[0]}, [%[v2]], %[offset]      \n\t"
				"vld3.f32 {d17[1], d19[1], d21[1]}, [%[v2]], %[offset]      \n\t"
				"vmul.f32 q12, q1, q10                                      \n\t"
				"vmul.f32 q13, q2, q8                                       \n\t"
				"vmul.f32 q14, q0, q9                                       \n\t"
				"vmls.f32 q12, q2, q9                                       \n\t"
				"vmls.f32 q13, q0, q10                                      \n\t"
				"vmls.f32 q14, q1, q8                                       \n\t"
				"vst3.f32 {d24[0], d26[0], d28[0]}, [%[result]], %[offset]  \n\t"
				"vst3.f32 {d24[1], d26[1], d28[1]}, [%[result]], %[offset]  \n\t"
				"vst3.f32 {d25[0], d27[0], d29[0]}, [%[result]], %[offset]  \n\t"
				"vst3.f32 {d25[1], d27[1], d29[1]}, [%[result]], %[offset]"
				: [v1] "=r" ( v1 ), [ v2 ] "=r" ( v2 ), [ result ] "=r" ( result )
				: "0" ( v1 ), "1" ( v2 ), "2" ( result ), [ offset ] "r" ( offset )
				: "memory", "q0", "q1", "q2", "q8", "q9", "q10", "q12", "q13", "q14"
				);
		}
		inline VECTOR VCALL cross3( VECTOR a, VECTOR b )
		{
			VECTOR res;
			cross3_neon_vld3_vst3_asm_4x( &a, &b, &res );
			return res;
		}
#endif

		inline VECTOR VCALL abs4( VECTOR a )
		{
#if CVM_SSE
			return _mm_andnot_ps( s_signBits, a );
#elif CVM_NEON
			return vabsq_f32( a );
#else
			static_assert( false, "Unknown target" );
#endif
		}
	}
}
#pragma once

namespace cvm
{
	namespace impl
	{
		template<int i1, int i2, int i3, int i4>
		inline VECTOR VCALL permute( VECTOR a );

#ifdef CVM_SSE
		template<int imm>
		inline VECTOR VCALL permute( VECTOR a )
		{
			static_assert( imm >= 0 && imm < 256, "Argument out of range" );
			return _mm_shuffle_ps( a, a, imm );
		}
		template<int i1, int i2, int i3, int i4>
		inline VECTOR VCALL permute( VECTOR a )
		{
			static_assert( i1 >= 0 && i1 < 4, "Index out of range" );
			static_assert( i2 >= 0 && i2 < 4, "Index out of range" );
			static_assert( i3 >= 0 && i3 < 4, "Index out of range" );
			static_assert( i4 >= 0 && i4 < 4, "Index out of range" );
			return permute<_MM_SHUFFLE( i1, i2, i3, i4 )>( a );
		}
#elif CVM_NEON
		template<>
		inline float32x4_t VCALL permute<0, 0, 0, 0>( float32x4_t a )
		{
			return vdupq_lane_f32( vget_low_f32( a ), 0 );
		}
		template<>
		inline float32x4_t VCALL permute<1, 1, 1, 1>( float32x4_t a )
		{
			return vdupq_lane_f32( vget_low_f32( a ), 1 );
		}
		template<>
		inline float32x4_t VCALL permute<2, 2, 2, 2>( float32x4_t a )
		{
			return vdupq_lane_f32( vget_high_f32( a ), 0 );
		}
		template<>
		inline float32x4_t VCALL permute<3, 3, 3, 3>( float32x4_t a )
		{
			return vdupq_lane_f32( vget_high_f32( 1 ), 1 );
		}
#endif
	}
}
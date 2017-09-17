#pragma once

namespace cvm
{
	namespace impl
	{
		inline VECTOR VCALL load( const FLOAT3& src )
		{
#if CVM_SSE
			__m128 x = _mm_load_ss( &src.x );
			__m128 y = _mm_load_ss( &src.y );
			__m128 z = _mm_load_ss( &src.z );
			__m128 xy = _mm_unpacklo_ps( x, y );
			return _mm_movelh_ps( xy, z );
#elif CVM_NEON
			float32x2_t xy = vld1_f32( &src.x );
			float32x2_t zero = vdup_n_f32( 0.0f );
			float32x2_t z = vld1_lane_f32( &src.z, zero, 0 );
			return vcombine_f32( xy, z );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline void VCALL store( VECTOR vec, FLOAT3& dest )
		{
#if CVM_SSE
			__m128 y = permute<1, 1, 1, 1>( vec );
			__m128 z = permute<2, 2, 2, 2>( vec );
			_mm_store_ss( &dest.x, vec );
			_mm_store_ss( &dest.y, y );
			_mm_store_ss( &dest.z, z );
#elif CVM_NEON
			float32x2_t xy = vget_low_f32( vec );
			vst1_f32( &dest.x, xy );
			vst1q_lane_f32( &dest.z, vec, 2 );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline VECTOR VCALL load( const FLOAT4& src )
		{
#if CVM_SSE
			return _mm_loadu_ps( &src.x );
#elif CVM_NEON
			return vld1q_f32( &src.x );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline void VCALL store( VECTOR vec, FLOAT4& dest )
		{
#if CVM_SSE
			_mm_storeu_ps( &dest.x, vec );
#elif CVM_NEON
			vst1q_f32( &dest.x, vec );
#else
			static_assert( false, "Unknown target" );
#endif
		}

#if CVM_NEON
		inline uint32_t loadFloat( float x )
		{
			return *(const uint32_t *)&a );
		}
		inline float32x2_t VCALL loadTwoFloats( float a, float b )
		{
			uint64_t res = loadFloat( a );
			res |= ( (uint64_t)loadFloat( b ) << 32 );
			return vcreate_f32( res );
		}
#endif
		inline VECTOR VCALL set( float a, float b, float c, float d )
		{
#if CVM_SSE
			return _mm_setr_ps( a, b, c, d );
#elif CVM_NEON
			return vcombine_f32( loadTwoFloats( a, b ), loadTwoFloats( c, d ) );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline VECTOR VCALL load( const FLOAT2& src )
		{
#if CVM_SSE
			__m128 x = _mm_load_ss( &src.x );
			__m128 y = _mm_load_ss( &src.y );
			return _mm_unpacklo_ps( x, y );
#elif CVM_NEON
			float32x2_t xy = vld1_f32( &src.x );
			return vcombine_f32( xy, vdup_n_f32( 0 ) );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline void VCALL store( VECTOR vec, FLOAT2& dest )
		{
#if CVM_SSE
			__m128 y = permute<1, 1, 1, 1>( vec );
			_mm_store_ss( &dest.x, vec );
			_mm_store_ss( &dest.y, y );
#elif CVM_NEON
			vst1_f32( &dest.x, vget_low_f32( vec ) );
#else
			static_assert( false, "Unknown target" );
#endif
		}

	}
}
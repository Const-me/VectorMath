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
	}
}
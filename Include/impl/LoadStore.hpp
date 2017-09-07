namespace cvm
{
	namespace impl
	{
		inline VECTOR VCALL load( const FLOAT3& src )
		{
#ifdef CVM_SSE
			__m128 x = _mm_load_ss( &src.x );
			__m128 y = _mm_load_ss( &src.y );
			__m128 z = _mm_load_ss( &src.z );
			__m128 xy = _mm_unpacklo_ps( x, y );
			return _mm_movelh_ps( xy, z );
#else
			static_assert( false, "Unknown target" );
#endif
		}

		inline void VCALL store( VECTOR vec, FLOAT3& dest )
		{
#ifdef CVM_SSE
			__m128 y = permute<1, 1, 1, 1>( vec );
			__m128 z = permute<2, 2, 2, 2>( vec );
			_mm_store_ss( &dest.x, vec );
			_mm_store_ss( &dest.y, y );
			_mm_store_ss( &dest.z, z );
#else
			static_assert( false, "Unknown target" );
#endif
		}
	}
}
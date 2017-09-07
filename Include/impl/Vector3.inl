namespace cvm
{
	Vector3::Vector3( const FLOAT3& that )
	{
#ifdef CVM_SSE
		__m128 x = _mm_load_ss( &that.x );
		__m128 y = _mm_load_ss( &that.y );
		__m128 z = _mm_load_ss( &that.z );
		__m128 xy = _mm_unpacklo_ps( x, y );
		m_vec = _mm_movelh_ps( xy, z );
#else
		static_assert( false, "Unknown target" );
#endif
	}

	void Vector3::store( FLOAT3& dest ) const
	{
#ifdef CVM_SSE
		__m128 y = impl::permute<1,1,1,1>( m_vec );
		__m128 z = impl::permute<2,2,2,2>( m_vec );
		_mm_store_ss( &dest.x, m_vec );
		_mm_store_ss( &dest.y, y );
		_mm_store_ss( &dest.z, z );
#else
		static_assert( false, "Unknown target" );
#endif
	}
}
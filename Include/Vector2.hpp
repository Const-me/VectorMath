#pragma once
#include "impl/VectorBase.hpp"

namespace cvm
{
	class Vector2:
		public impl::VectorBase<Vector2, FLOAT2>
	{
		using tBase = impl::VectorBase<Vector2, FLOAT2>;
	public:
		Vector2() = default;

		Vector2( const Vector2& that ) : tBase( that ) {}

		// Load float2 from RAM
		Vector2( const FLOAT2& that ) : tBase( that ) {}

		Vector2( VECTOR that ) : tBase( that ) {}

		Vector2( float x, float y ) : tBase( impl::set( x, y, 0, 0 ) ) { }

		float getX() const { return impl::extract<0>( m_vec ); }
		float getY() const { return impl::extract<1>( m_vec ); }

		void setX( float a ) { m_vec = impl::insert<0>( m_vec, a ); }
		void setY( float a ) { m_vec = impl::insert<1>( m_vec, a ); }
	};
}
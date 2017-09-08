#pragma once
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Normal.hpp"

namespace cvm
{
	class Line
	{
		// e41, e42, e43 components of the 4D bi-vector
		Vector3 m_tangent;
		// e23, e31, e12 components of the 4D bi-vector
		Normal m_moment;

	public:
		Line() = default;
		Line( const Line& that ) = default;
		Line& operator=( const Line& that ) = default;

		// Construct a line from 2 points
		Line( const Vector3& a, const Vector3& b ) :
			m_tangent( b - a ),
			m_moment( impl::cross3( (VECTOR)a, (VECTOR)b ) ) { }

		// Construct a line from 2 points
		Line( const Vector4& a, const Vector4& b ) :
			Line( Vector3{ impl::divideByW( VECTOR( a ) ) },
				Vector3{ impl::divideByW( VECTOR( b ) ) } ) { }

		// Load
		Line( const FLOAT3x2& line ) :
			m_tangent( line.a ), m_moment( line.b ) { }
		// Store
		void store( FLOAT3x2& line ) const
		{
			m_tangent.store( line.a );
			m_moment.store( line.b );
		}

		const Vector3& tangent() const { return m_tangent; }
		const Normal& moment() const { return m_moment; }
	};
}
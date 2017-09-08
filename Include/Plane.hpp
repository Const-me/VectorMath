#pragma once
#include "Vector3.hpp"
#include "Line.hpp"

namespace cvm
{
	class Plane:
		public impl::VectorBase4<Vector4>
	{
	public:
		Plane() = default;
		Plane( const Plane& that ) = default;
		Plane( VECTOR v ) : tBase( v ) { }
		Plane( const FLOAT4& src ) : tBase( src ) { }
		Plane& operator=( const Plane& that ) = default;

		// Construct from 3 points
		Plane( const Vector3& a, const Vector3& b, const Vector3& c )
		{
			// TODO
		}

		// Construct from line + point
		Plane( const Line& line, const Vector3& p3 )
		{
			// TODO
		}
	}
}
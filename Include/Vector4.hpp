#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase4.hpp"

namespace cvm
{
	class Vector3;

	class Vector4:
		public impl::VectorBase4<Vector4>
	{
	public:
		Vector4() = default;

		Vector4( const Vector4& that ) : tBase( that ) {}

		Vector4( const FLOAT4& that ) : tBase( that ) {}

		Vector4( VECTOR that ) : tBase( that ) {}

		Vector4( float x, float y, float z, float w ) : tBase( impl::set( x, y, z, w ) ) { }

		Vector4( float x, float y, float z ) : tBase( impl::set( x, y, z, 0 ) ) { }

		inline Vector4( const Vector3& that );
	};
}
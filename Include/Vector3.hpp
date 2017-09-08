#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase3.hpp"

namespace cvm
{
	class Vector4;

	class Vector3:
		public impl::VectorBase3<Vector3>
	{
	public:
		Vector3() = default;

		Vector3( const Vector3& that ) : tBase( that ) {}

		// Load float3 from RAM, set W to 0
		Vector3( const FLOAT3& that ) : tBase( that ) {}

		Vector3( VECTOR that ) : tBase( that ) {}

		Vector3( float x, float y, float z ) : tBase( FLOAT3{ x, y, z } ) { }

		inline Vector3( const Vector4& that );
	};
}
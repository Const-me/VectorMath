#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase4.hpp"

namespace cvm
{
	class Vector4:
		public impl::VectorBase4<Vector4>
	{
	public:
		Vector4() = default;

		Vector4( const Vector4& that ) : tBase( that ) {}

		// Load float3 from RAM, set W to 0
		Vector4( const FLOAT4& that ) : tBase( that ) {}

		Vector4( VECTOR that ) : tBase( that ) {}

		Vector4( float x, float y, float z, float w ) : tBase( FLOAT4{ x, y, z, w } ) { }
	};
}
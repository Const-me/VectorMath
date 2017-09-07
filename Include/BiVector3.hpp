#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase3.hpp"

namespace cvm
{
	class BiVector3:
		public impl::VectorBase3<BiVector3>
	{
	public:
		BiVector3() = default;

		BiVector3( const BiVector3& that ) : tBase( that ) {}

		// Load float3 from RAM, set W to 0
		BiVector3( const FLOAT3& that ) : tBase( that ) {}

		BiVector3( VECTOR that ) : tBase( that ) {}

		BiVector3( float x, float y, float z ) : tBase( FLOAT3{ x, y, z } ) { }
	};
}
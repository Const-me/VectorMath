#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase3.hpp"

namespace cvm
{
	class Normal:
		public impl::VectorBase3<Normal>
	{
	public:
		Normal() = default;

		Normal( const Normal& that ) : tBase( that ) {}

		// Load float3 from RAM, set W to 0
		Normal( const FLOAT3& that ) : tBase( that ) {}

		Normal( VECTOR that ) : tBase( that ) {}

		Normal( float x, float y, float z ) : tBase( FLOAT3{ x, y, z } ) { }
	};
}
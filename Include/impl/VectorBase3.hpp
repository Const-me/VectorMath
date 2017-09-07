#pragma once
#include "VectorBase.hpp"
#include "Extract.hpp"

namespace cvm
{
	namespace impl
	{
		// Stuff that's common across all 3D vectors
		template<class tVector>
		class VectorBase3: public VectorBase<tVector, FLOAT3>
		{
		protected:
			typedef VectorBase3<tVector> tBase;

		public:
			VectorBase3() = default;

			VectorBase3( const tVector& that ) : VectorBase<tVector, FLOAT3>( that ) {}

			// Load float3 from RAM, set W to 0
			VectorBase3( const FLOAT3& that ) : VectorBase<tVector, FLOAT3>( that ) {}

			VectorBase3( VECTOR that ) : VectorBase<tVector, FLOAT3>( that ) {}

			float getX() const { return extract<0>( m_vec ); }
			float getY() const { return extract<1>( m_vec ); }
			float getZ() const { return extract<2>( m_vec ); }
		};
	}
}
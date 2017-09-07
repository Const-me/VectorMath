#pragma once
#include "StorageTypes.hpp"
#include "impl/VectorBase.hpp"

namespace cvm
{
	class Vector3:
		public impl::VectorBase<Vector3>
	{
	public:
		Vector3() = default;
		Vector3( const Vector3& that ) { m_vec = that.m_vec; }

		// Load float3 from RAM, set W to 0
		Vector3( const FLOAT3& that );

		Vector3( VECTOR that )
		{
			m_vec = that;
		}

		Vector3( float x, float y, float z ) : Vector3( FLOAT3{ x, y, z } ) { }

		operator VECTOR const( ) { return m_vec; }

		// Store float3 to RAM
		void store( FLOAT3& dest ) const;

		FLOAT3 store() const
		{
			FLOAT3 res;
			store( res );
			return res;
		}
	};
}
#include "impl/Vector3.inl"
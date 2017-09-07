#pragma once
#include "StorageTypes.hpp"
#include "RegisterTypes.hpp"
#include "impl/BasicMath.hpp"

namespace cvm
{
	class Vector3
	{
		VECTOR m_vec;

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

		Vector3 operator+( const Vector3& that ) const
		{
			return impl::vectorAdd( m_vec, that.m_vec );
		}
		void operator+=( const Vector3& that )
		{
			m_vec = impl::vectorAdd( m_vec, that.m_vec );
		}
		Vector3 operator-( const Vector3& that ) const
		{
			return impl::vectorSub( m_vec, that.m_vec );
		}
		void operator-=( const Vector3& that )
		{
			m_vec = impl::vectorSub( m_vec, that.m_vec );
		}
	};
}
#include "impl/Vector3.inl"
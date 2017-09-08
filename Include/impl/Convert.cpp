#include "../Vector3.hpp"
#include "../Vector4.hpp"

namespace cvm
{
	// This needs to be in a separate CPP to avoid circular dependency.
	inline Vector3::Vector3( const Vector4& that )
	{
		m_vec = impl::divideByW( that.operator VECTOR() );
	}
	inline Vector4::Vector4( const Vector3& that )
	{
		m_vec = impl::insert<3>( that.operator VECTOR(), 1.0f );
	}
}
#pragma once
#include "Vector3.hpp"
#include "Normal.hpp"

namespace cvm
{
	Normal operator ^( const Vector3& a, const Vector3& b )
	{
		return Normal{ impl::cross3( (VECTOR)a, (VECTOR)b ) };
	}
}
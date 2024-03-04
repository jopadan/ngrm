#pragma once
#include <whmath/math.hpp>

namespace math
{

template<typename _Tp,
         typename _Up = typename std::enable_if<std::is_signed<_Tp>::value,
                      typename std::make_unsigned<_Tp>::type>::type>
_Up ilogx(_Up i, _Up base)
{
	return ((bit_width(i) - 1) / (bit_width(base) - 1));
}

}

#pragma once

/// includes
#include <type_traits>

namespace TPGE
{
	struct NotExists {};
	template<typename T, typename Arg> NotExists operator== (const T&, const Arg&);

	template<typename T, typename Arg = T>
	struct EqualExists
	{
		enum { value = !std::is_same<decltype(*(T*)(0) == *(Arg*)(0)), NotExists>::value };
	};
}

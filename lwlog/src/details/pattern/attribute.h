#pragma once

#include <variant>

namespace lwlog::details
{
	struct flag_pair
	{
		std::string_view verbose;
		std::string_view shortened;
		bool operator==(const flag_pair& other) const
		{
			return (verbose == other.verbose) &&
				(shortened == other.shortened);
		}
	};

	struct attrib_hasher
	{
		std::size_t operator()(const flag_pair& flags) const
		{
			return std::hash<std::string_view>{}(flags.verbose) ^
				std::hash<std::string_view>{}(flags.shortened);
		}
	};

	using attrib_value = std::variant<
		std::reference_wrapper<int>,
		std::reference_wrapper<float>,
		std::reference_wrapper<double>,
		std::reference_wrapper<std::string_view>
	>;

	struct attrib_value_visitor
	{
		template<typename T>
		std::string_view operator()(T arg)
		{
			if constexpr (std::is_arithmetic_v<T::type>)
				return std::to_string(std::forward<T::type>(arg));
			else return arg;
		}
	};
}
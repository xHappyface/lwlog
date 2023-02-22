#pragma once

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(std::string&, const record&) const = 0;

		template<typename T>
		static void format_attribute(std::string& pattern, const flag_pair& flags, T value)
		{
			std::string_view str_value = [&]() {
				if constexpr (std::is_arithmetic_v<T>)
					return std::to_string(std::forward<T>(value));
				else if constexpr (std::is_same_v<T, std::string>)
					return value.data();
				else
					return value;
			}();

			const auto& [verbose, shortened] = flags;
			while (std::strstr(pattern.data(), verbose.data()))
				pattern.replace(pattern.find(verbose), verbose.length(), str_value);

			while (std::strstr(pattern.data(), shortened.data()))
				pattern.replace(pattern.find(shortened), shortened.length(), str_value);
		}

		template<typename T>
		static void format_attribute(std::string& pattern, std::string_view flag, T value)
		{
			std::string_view str_value = [&]() {
				if constexpr (std::is_arithmetic_v<T>)
					return std::to_string(std::forward<T>(value));
				else if constexpr (std::is_same_v<T, std::string>)
					return value.data();
				else
					return value;
			}();

			while (std::strstr(pattern.data(), flag.data()))
				pattern.replace(pattern.find(flag), flag.length(), str_value);
		}

		template<>
		static void format_attribute<void*>(std::string&, const flag_pair&, void*) {}

		template<>
		static void format_attribute<void*>(std::string&, std::string_view, void*) {}
	};
}
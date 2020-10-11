#pragma once

#include <string>
#include <vector>
#include <memory>

#include "interface/level_filter_interface.h"
#include "interface/pattern_interface.h"
#include "details/stream.h"
#include "fwd.h"

namespace lwlog::sinks
{
	class sink : public interface::level_filter, public interface::pattern
	{
	public:
		sink();
		virtual ~sink() = default;
		virtual void sink_it(std::string_view) = 0;

	public:
		void set_pattern(std::string_view pattern) override;
		void add_pattern_attribute(details::pattern_attribute attribute) override;
		void set_level_filter(std::initializer_list<sink_level> level_list) override;

	public:
		void disable_color();
		bool should_color() const;
		bool should_sink(sink_level t_level) const;
		std::string get_pattern() const;

	private:
		bool m_should_color{ true };
		std::string m_pattern{ "[%d, %T] [%l] [%n]: %v" };
		std::vector<sink_level> m_levels;
	};

	using sink_ptr = std::shared_ptr<sink>;
	using sink_list = std::initializer_list<sink_ptr>;
}
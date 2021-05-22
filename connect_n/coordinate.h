#pragma once

#include <cstddef>
#include <vector>
#include <sstream>
#include <string>
#include <fmt/format.h>

namespace connectn {

// WIP: API for an n-dimensional coordinate suitable for connect-N game.
// This class is NOT YET used but hopefully will be later to represent n-dimensional coordinates and
// their limits.

class Coordinate {
public:
	explicit Coordinate(size_t dim);

	void set_dimension(size_t n) noexcept;
	void set_maximum(size_t dim, size_t val) noexcept;

	Coordinate& operator++() noexcept;

	Coordinate& operator++(int) noexcept { return ++*this; }

	struct Element { size_t value; size_t maximum; };
	std::vector<Element> const& components() const noexcept { return components_; }

private:
	std::vector<Element> components_;
};

std::vector<size_t> elements(Coordinate const& _coordinae);
std::vector<size_t> max(Coordinate const& _coordinae);

}

namespace fmt
{
	template <>
	struct formatter<connectn::Coordinate>
	{
        template <typename ParseContext>
        constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }
        template <typename FormatContext>
        auto format(connectn::Coordinate const& coord, FormatContext& ctx)
        {
            std::string s;
            for (auto const& element: connectn::elements(coord))
            {
				if (!s.empty())
					s += ',';
				s += element.value;
            }
            return format_to(ctx.out(), "{}", s);
		}
	};
}

#pragma once

#include <cstddef>
#include <vector>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <stdexcept>
#include <fmt/format.h>

namespace connectn {

using Coordinate = std::tuple<size_t, size_t>;

/**
 * Checks for @p w connected vectors parallel to the first axis.
 *
 * @param t Callback function to retrieve the value in the space.
 * @param s0 Callback that increments passed vector along the first axis.
 * @param s1 Callback that increments passed vector along the second axis.
 * @param w Number of connected vectors to satisfy
 * @param l Lengths to check from 1 to @p l (including) along each axis.
 * @param n Vector representing the current check state (in range between Origin and @p l including).
 *
 * @retval true @p w connected vectors parallel to an axis found.
 * @retval false Otherwise.
 */
template <typename T, typename Next0, typename Next1>
constexpr bool check_ortho(T t,
                           Next0 s0,
                           Next1 s1,
                           size_t w,
                           Coordinate l,
                           size_t f,
                           Coordinate n)
{
    auto const tn = t(n);
    auto const l0 = std::get<0>(l);
    auto const n0 = std::get<0>(n);
    auto const l1 = std::get<1>(l);
    auto const n1 = std::get<1>(n);
    auto const nextCol = s0(n);
    auto const nextRow = s1(n);

    auto const check = [&](auto _f, auto _n) {
        return check_ortho(t, s0, s1, w, l, _f, _n);
    };

    // f == w
    if (tn && f + 1 == w)
        return true;

    // last line & not enough columns remaining to satisfy f == w.
    if (!tn && n1 == l1 && w - f > l0 - n0)
        return false;

    // last line, t(n) true and we can complete to w==f
    if (n1 == l1 && tn && w - f - 1 == l0 - n0)
        return check(f + 1, nextCol);

    // t(n) true & enough columns remaining to maybe get to f == w
    if (w - f <= l0 - n0 && tn)
        return check(f + 1, nextCol);

    // t(n) false & enough columns remaining to maybe get to f == w
    if (w - f <= l0 - n0 && !tn)
        return check(0, nextCol);

    // not enough remaining columns for f == w, but more lines available
    if (w - f > l0 - n0 && n1 < l1)
        return check(0, nextRow);

    // throw std::runtime_error("Bug. Unhandled case found.");
    return false;
}

template <typename T>
bool checkmate(T t, size_t w, Coordinate l)
{
    auto constexpr StartCoordinate = Coordinate(1, 1);

    // Increments position in the first dimension.
    auto constexpr next1 = [](Coordinate v) constexpr noexcept -> Coordinate {
        return Coordinate(std::get<0>(v) + 1, std::get<1>(v));
    };

    // Increments position in the second dimension.
    auto constexpr next2 = [](Coordinate v) constexpr noexcept -> Coordinate {
        return Coordinate(std::get<0>(v), std::get<1>(v) + 1);
    };

    // Swaps vector components (c1, c2)  to (c2, c1)
    auto constexpr flip = [](Coordinate v) constexpr noexcept -> Coordinate {
        return Coordinate(std::get<1>(v), std::get<0>(v));
    };

    // Checks parallel to the first dimension.
    if (auto const p = check_ortho(t, next1, next2, w, l, 0, StartCoordinate))
        return p;

    // Checks parallel to the second dimension.
    if (auto const p = check_ortho(t, next2, next1, w, flip(l), 0, {1, 1}))
        return p;

    // TODO: check parallel to the Nth direction.

    return false;
}

}

namespace std
{
    inline std::ostream& operator<<(std::ostream& os, connectn::Coordinate v)
    {
        os << '(' << std::get<0>(v) << ',' << std::get<1>(v) << ')';
        return os;
    }
}

#include <connect_n/connect_n.h>
#include <array>
#include <catch2/catch.hpp>
using namespace std;

template <typename Board>
auto t(Board const& board)
{
	return [board = std::ref(board)](auto n) -> bool {
        return board.get().at((get<1>(n)-1) * 4 + (get<0>(n)-1)) != 0;
	};
}

using Coord = connectn::Coordinate;
using VecSeq = std::vector<Coord>;

TEST_CASE("checkmate.1.0")
{
	auto constexpr board = array{ 1, 1, 0, 0 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 1});
    CHECK(cm);
}

TEST_CASE("checkmate.1.1")
{
	auto constexpr board = array{ 0, 1, 1, 0 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 1});
    CHECK(cm);
}

TEST_CASE("checkmate.1.2")
{
	auto constexpr board = array{ 1, 0, 1, 1 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 1});
    CHECK(cm);
}

TEST_CASE("checkmate.1.3")
{
	auto constexpr board = array{ 1, 0, 0, 1 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 1});
    CHECK(!cm);
}

TEST_CASE("checkmate.2.1")
{
	auto constexpr board = array{ 1, 0, 0, 1,
                                  1, 1, 0, 0 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 2});
    CHECK(cm);
}

TEST_CASE("checkmate.2.2")
{
	auto constexpr board = array{ 1, 0, 0, 1,
                                  1, 0, 1, 1 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 2});
    CHECK(cm);
}

TEST_CASE("checkmate.4x4")
{
	auto constexpr board = array{ 1, 0, 0, 1,
                                  1, 0, 1, 1,
                                  1, 0, 1, 0,
                                  0, 1, 1, 1 };
	auto const cm = connectn::checkmate(t(board), 2, {4, 2});
    CHECK(cm);
}

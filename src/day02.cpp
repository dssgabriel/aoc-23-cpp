#include "aoc23_utils.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <functional>
#include <nanobench.h>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

namespace rv = std::ranges::views;
using namespace std::chrono;

constexpr i32 EXPECTED_PART1 = 8;
constexpr i32 EXPECTED_PART2 = 2286;

struct Game {
    i32 m_id;
    std::vector<std::array<i32, 3>> m_rounds;

    static auto parse_games(std::string_view input) -> std::vector<Game> {
        auto lines = input | rv::split('\n');
        std::vector<Game> games;
        for (auto const& [id, line] : rv::enumerate(lines)) {
            std::string_view lv(line.begin(), line.end());
            if (lv.empty()) { break; }
            games.push_back(Game::parse_game(lv, id + 1));
        }
        return games;
    }

    ~Game() = default;

  private:
    Game(i32 id, std::vector<std::array<i32, 3>> const& rounds) : m_id(id), m_rounds(rounds) {
    }

    static auto parse_game(std::string_view game_sv, i32 lc) -> Game {
        std::vector<std::array<i32, 3>> rounds;
        auto rounds_start = game_sv.find_first_of(':');
        std::string_view rounds_sv(game_sv.substr(rounds_start, game_sv.size() - 1));
        auto rounds_split = rounds_sv | rv::split(';');
        for (auto const& round : rounds_split) {
            std::string_view rv(round.begin(), round.end());
            if (rv.empty()) { break; }
            rounds.push_back(Game::parse_round(rv));
        }
        return Game(lc, rounds);
    }

    static auto parse_round(std::string_view round_sv) -> std::array<i32, 3> {
        auto is_digit = [](char c) -> bool { return std::isdigit(static_cast<u8>(c)); };

        std::array<i32, 3> round{ { 0, 0, 0 } };
        auto colors = round_sv | rv::split(',');
        for (auto const& color : colors) {
            std::string_view cv(color.begin(), color.end());
            if (cv.empty()) { break; }
            usz idx;
            if (cv.find("red") != std::string::npos) {
                idx = 0;
            } else if (cv.find("green") != std::string::npos) {
                idx = 1;
            } else if (cv.find("blue") != std::string::npos) {
                idx = 2;
            } else {
                std::unreachable();
            }
            auto values = cv | rv::filter(is_digit);
            round[idx] = std::accumulate(values.begin(), values.end(), 0, [](i32 acc, char c) {
                return acc * 10 + (c - '0');
            });
        }
        return round;
    }
};

auto part1(std::string_view input) -> i32 {
    auto possible_configuration = [](Game const& game) {
        for (auto const& r : game.m_rounds) {
            if (r[0] > 12 || r[1] > 13 || r[2] > 14) { return false; }
        }
        return true;
    };

    std::vector<Game> games = Game::parse_games(input);
    auto ids = games | rv::filter(possible_configuration)
               | rv::transform([](Game const& game) -> i32 { return game.m_id; });
    return std::reduce(ids.begin(), ids.end(), 0, std::plus{});
}

auto part2(std::string_view input) -> i32 {
    std::vector<Game> games = Game::parse_games(input);
    return std::transform_reduce(
        games.begin(),
        games.end(),
        0,
        std::plus{},
        [](auto const& game) {
            i32 maxr = 0;
            i32 maxg = 0;
            i32 maxb = 0;
            for (auto const& r: game.m_rounds) {
                maxr = std::max(r[0], maxr);
                maxg = std::max(r[1], maxg);
                maxb = std::max(r[2], maxb);
            }
            return maxr * maxg * maxb;
        }
    );
}

auto main(i32 argc, char* argv[]) -> i32 {
    // Tests
    fs::path test_path1("sample_input/day02a.txt");
    auto test1 = aoc23_utils::read_input(test_path1);
    i32 ans1 = part1(test1);
    assert(EXPECTED_PART1 == ans1, "test part 1\n\texpected {}, got {}", EXPECTED_PART1, ans1);
    fs::path test_path2("sample_input/day02b.txt");
    auto test2 = aoc23_utils::read_input(test_path2);
    i32 ans2 = part2(test2);
    assert(EXPECTED_PART2 == ans2, "test part 2\n\texpected {}, got {}", EXPECTED_PART2, ans2);

    // Read input
    fs::path input_path("input/day02.txt");
    if (argc > 1) { input_path = argv[1]; }
    auto input = aoc23_utils::read_input(input_path);

    // Answers
    ans1 = part1(input);
    fmt::print("Part 1: {}\n", ans1);
    ans2 = part2(input);
    fmt::print("Part 2: {}\n", ans2);

    // Profiling
    ankerl::nanobench::Bench().timeUnit(1us, "µs").epochs(31).warmup(3).run("part1", [&] {
        ankerl::nanobench::doNotOptimizeAway(part1(input));
    });
    ankerl::nanobench::Bench().timeUnit(1us, "µs").epochs(31).warmup(3).run("part2", [&] {
        ankerl::nanobench::doNotOptimizeAway(part2(input));
    });

    return 0;
}

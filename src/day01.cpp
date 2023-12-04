#include "aoc23_utils.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fmt/chrono.h>
#include <iterator>
#include <nanobench.h>
#include <numeric>
#include <ranges>
#include <vector>

namespace rv = std::ranges::views;
using namespace std::chrono;

static auto to_digit(char c) -> int32_t {
    return static_cast<int32_t>(c - '0');
};

auto part1(std::string_view input) -> int32_t {
    auto is_digit = [](char c) -> bool { return std::isdigit(static_cast<uint8_t>(c)); };

    auto lines = input | rv::split('\n');
    return std::transform_reduce(lines.begin(), lines.end(), 0, std::plus{}, [&](auto const& line) {
        std::string_view lv(line.begin(), line.end());
        if (lv.empty()) { return 0; }
        auto calibration_vals = lv | rv::filter(is_digit) | rv::transform(to_digit);
        return calibration_vals.front() * 10 + calibration_vals.back();
    });
}

constexpr std::array<std::string, 9> STR_DIGITS{ "one", "two",   "three", "four", "five",
                                                 "six", "seven", "eight", "nine" };
auto part2(std::string_view input) -> int32_t {
    auto lines = input | rv::split('\n');
    return std::transform_reduce(lines.begin(), lines.end(), 0, std::plus{}, [=](auto const& line) {
        std::string_view lv(line.begin(), line.end());
        if (lv.empty()) { return 0; }
        std::vector<int32_t> digits;
        for (auto const& [i, c] : rv::enumerate(lv)) {
            if (c >= '0' && c <= '9') { digits.push_back(c - '0'); }
            for (auto const& [j, sd] : rv::enumerate(STR_DIGITS)) {
                if (lv.size() >= i + sd.size() && lv.substr(i, sd.size()) == sd) {
                    digits.push_back(j + 1);
                    break;
                }
            }
        }
        return digits.front() * 10 + digits.back();
    });
}

auto main(int32_t argc, char* argv[]) -> int32_t {
    // Tests
    fs::path test_path1("sample_input/day01a.txt");
    auto test1 = aoc23_utils::read_input(test_path1);
    int32_t ans1 = part1(test1);
    assert(ans1 == 142, "test part 1\n\texpected {}, got {}", 142, ans1);
    fs::path test_path2("sample_input/day01b.txt");
    auto test2 = aoc23_utils::read_input(test_path2);
    int32_t ans2 = part2(test2);
    assert(ans2 == 281, "test part 2\n\texpected {}, got {}", 281, ans2);

    // Read input
    fs::path input_path("input/day01.txt");
    if (argc > 1) { input_path = argv[1]; }
    auto input = aoc23_utils::read_input(input_path);

    // Answers
    ans1 = part1(input);
    fmt::print("Part 1: {}\n", ans1);
    ans2 = part2(input);
    fmt::print("Part 2: {}\n", ans2);

    // Profiling
    ankerl::nanobench::Bench()
        .timeUnit(1us, "µs")
        .epochs(31)
        .warmup(3)
        .run("part1", [&] { ankerl::nanobench::doNotOptimizeAway(part1(input)); });
    ankerl::nanobench::Bench()
        .timeUnit(1us, "µs")
        .epochs(31)
        .warmup(3)
        .run("part2", [&] { ankerl::nanobench::doNotOptimizeAway(part2(input)); });

    return 0;
}

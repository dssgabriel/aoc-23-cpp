#include <algorithm>
#include <cctype>
#include <cstdint>
#include <chrono>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fstream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;
namespace ranges = std::ranges;
namespace rv = ranges::views;
using namespace std::chrono;

#define aoc_assert(expr, msg, ...)                                                                 \
    do {                                                                                           \
        if (!(expr)) {                                                                             \
            fmt::print(stderr, "\x1b[1;31massertion failed: \x1b[0m" msg "\n", ##__VA_ARGS__);     \
            std::abort();                                                                          \
        }                                                                                          \
    } while (false)

static auto to_digit(char c) -> int32_t {
    return static_cast<int32_t>(c - '0');
};

constexpr std::array<std::string, 9> STR_DIGITS{ "one", "two",   "three", "four", "five",
                                                 "six", "seven", "eight", "nine" };

auto read_input(fs::path const& path) -> std::string {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    auto const fsz = fs::file_size(path);
    std::string content(fsz, '\0');
    fin.read(content.data(), fsz);
    return content;
}

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

auto part2(std::string_view input) -> int32_t {
    auto lines = input | rv::split('\n');
    return std::transform_reduce(lines.begin(), lines.end(), 0, std::plus{}, [](auto const& line) {
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
    // Test part 1
    fs::path test_path1("sample_input/day01a.txt");
    auto test1 = read_input(test_path1);
    int32_t ans1 = part1(test1);
    aoc_assert(ans1 == 142, "test part 1\n\texpected {}, got {}", 142, ans1);
    // Test part 2
    fs::path test_path2("sample_input/day01b.txt");
    auto test2 = read_input(test_path2);
    int32_t ans2 = part2(test2);
    aoc_assert(ans2 == 281, "test part 2\n\texpected {}, got {}", 281, ans2);

    fs::path input_path("input/day01.txt");
    if (argc > 1) { input_path = argv[1]; }
    auto input = read_input(input_path);

    auto start = high_resolution_clock::now();
    ans1 = part1(input);
    auto stop = high_resolution_clock::now();
    fmt::print("Part 1: {} (in {})\n", ans1, duration_cast<microseconds>(stop - start));

    start = high_resolution_clock::now();
    ans2 = part2(input);
    stop = high_resolution_clock::now();
    fmt::print("Part 2: {} (in {})\n", ans2, duration_cast<microseconds>(stop - start));

    return 0;
}

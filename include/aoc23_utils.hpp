#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fmt/core.h>
#include <string>
#include <string_view>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using usz = size_t;
using isz = ptrdiff_t;

namespace fs = std::filesystem;

namespace aoc23_utils {
/// Utility assert macro
#define assert(expr, msg, ...)                                                                     \
    do {                                                                                           \
        if (!(expr)) {                                                                             \
            fmt::print(stderr, "\x1b[1;31massertion failed: \x1b[0m" msg "\n", ##__VA_ARGS__);     \
            std::abort();                                                                          \
        }                                                                                          \
    } while (false)

/// Read input file into string buffer.
auto read_input(fs::path const& path) -> std::string;
} // namespace aoc23_utils

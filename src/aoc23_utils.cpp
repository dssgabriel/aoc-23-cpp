#include "aoc23_utils.hpp"

#include <fstream>

namespace aoc23_utils {
auto read_input(fs::path const& path) -> std::string {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    auto const fsz = fs::file_size(path);
    std::string content(fsz, '\0');
    fin.read(content.data(), fsz);
    return content;
}

auto to_digit(char c) -> i32 {
    return static_cast<i32>(c - '0');
};
}

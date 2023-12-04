# Advent of Code 2023

This year, I'll be trying to do AoC in "modern" C++. I am a seasoned C programmer but I'd like to have a taste of what C++17 and above can offer, especially in terms of functional-like programming. Feel free to submit issues and PRs if you have suggestions to make my solutions more idiomatic.

My primary goal is not performance, although I'd like to achieve almost-optimal solutions (can't throw away my HPC background, duh).

## Building and running the solutions

### Pre-requisites
- [CMake](https://cmake.org/) v3.24+
- [{fmt}](https://fmt.dev/latest/index.html) v10.0+
- A C++23-capable compiler, GNU g++ v13.2 being the most usable at the moment.

### Building
Build using CMake, e.g. using Ninja as generator:
```sh
cmake -S . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --target day<DAY_NUMBER>
```

### Running
Simply run the compiled binary. You can optionally pass the path to your own text input:
```sh
build/release/day<DAY_NUMBER> [path/to/input]
```

## What is AoC all about?
[Advent of Code](https://adventofcode.com/) is an Advent calendar of small programming puzzles for a variety of skill sets and skill levels that can be solved in any programming language you like. People use them as a speed contest, interview prep, company training, university coursework, practice problems, or to challenge each other.

You don't need a computer science background to participate - just a little programming knowledge and some problem solving skills will get you pretty far. Nor do you need a fancy computer; every problem has a solution that completes in at most 15 seconds on ten-year-old hardware.

If you'd like to support Advent of Code, you can do so indirectly by helping to [share](https://adventofcode.com/2023/about) it with others, or directly via PayPal or Coinbase.

## Credits
Puzzles, Code, & Design: [Eric Wastl](https://twitter.com/ericwastl)

Beta Testing:
- [Tim Giannetti](https://twitter.com/Sr_Giannetti)
- Ben Lucek
- [JP Burke](https://twitter.com/yatpay)
- [Aneurysm9](https://twitter.com/Aneurysm9)
- Andrew Skalski

Community Managers: [Danielle Lucek](https://www.reddit.com/user/daggerdragon) and [Aneurysm9](https://twitter.com/Aneurysm9)

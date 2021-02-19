# The Legend of Zelda: Breath of the Wild

This is an experimental, WIP decompilation of *The Legend of Zelda: Breath of the Wild* v1.5.0 (Switch).

File names, class or function names and the file organization come from leftover strings. Unlike some other first-party games such as *Super Mario Odyssey*, all known public versions of U-King are completely stripped, so most names are just more or less educated guesses.

**This repository does not contain game assets or RomFS content and *cannot* be used to play *Breath of the Wild*.**

This project is only about the main executable which contains all game code and statically linked libraries. The RomFS and the SDK libraries are *out of the scope* of this project.

Progress: https://botw.link/progress

Just like other decompilation projects, progress is tracked by looking at the percentage of decompiled bytes (the number of decompiled bytes divided by the total code size).

## Goal

The goal of this project is to better understand game internals, aid with glitch hunting and document existing knowledge in something less fragile than an IDA database.

Considering the large size of the executable (~40MB), it is not expected to reach 100% progress within a reasonable timeframe.

As a result, the project is unlikely to produce a working executable in the near future. It will help with understanding and reverse engineering the game even in its incomplete state, but it will NOT help with playing BotW or porting the game to other platforms, which is **explicitly a non-goal**.

### Isn't this risky?

As with other game decompilations, this project is probably in a legal gray zone. However, the authors of this project believe that it is unlikely to bother NCL for the following reasons:

* Contributing to this repository requires owning the game on a Switch console and dumping the executable.
* This project is completely useless to anybody who does not have the game.
    * It cannot be used to play the game.
    * It does not give you any useful knowledge if you do not play the game or if you do not even have it.
* This repository is only about the executable, which is less than 0.3% of the whole game (ExeFS+RomFS).
* Even if the executable were fully decompiled, it would still not be possible to play the game without dumping the RomFS from a Switch.
* This repository does not contain any original code from the executable.
    * Unlike some decompilation projects for older consoles, not even a single byte of assembly code is included from the original executable.
    * It only contains reimplemented functions that happen to match once compiled.
    * The compiler is Clang, so there are many, many, many ways to write a function and organize things while still getting the exact same code. In fact, while the source code happens to match the compiled code, it is possible and quite likely that the original codebase looks very different from this repository.
* This is a large monolithic game so there is no other way of being accurate to the original logic without doing matching decompilation.
    * Clean room decompilation (having separate teams doing reverse engineering and implementation work) is not a solution when the goal is to follow the original logic as accurately as possible.
* This project does not use any proprietary SDK or any leaked document at all.
    * The compiler is just Clang 4.0.1 which is open source and freely available on [LLVM's website](https://releases.llvm.org/). The SDK compiler is **not** used.
    * Anyone who has had access to leaked information is not allowed to contribute.

## Status

Currently, the focus is on decompiling AI classes and KingSystem framework code.

Because meaningfully splitting the code is not feasible, the built executable currently only contains functions that have been decompiled and no effort is being made to put functions and data at the correct addresses.

## Building

### Dependencies

* Clang 4.0.1
    * Download [Clang 4.0.1](https://releases.llvm.org/download.html#4.0.1) and extract the archive to a convenient location of your choice.
    * You might also need libtinfo5. For Ubuntu or Debian users, install it with `sudo apt install libtinfo5`
* Ninja
    * For Ubuntu or Debian users, install it with `sudo apt install ninja-build`
* CMake 3.13+
    * If you are on Ubuntu 18.04, you must [update CMake by using the official CMake APT repository](https://apt.kitware.com/).
* devkitA64
    * [Follow this guide to set it up.](https://switchbrew.org/wiki/Setting_up_Development_Environment#Setup)

Using Linux (or WSL) is recommended but not required. The rest of this guide assumes that you are using a Linux environment, though.

### Building for Switch

1. After cloning this repository, run: `git submodule update --init --recursive`
2. `env UKING_CLANG=$1 DEVKITA64=$2 cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../ToolchainNX64.cmake -B build`
    * Replace `$1` with the path to the extracted Clang archive, such that `$1/bin/clang` exists.
    * Replace `$2` with the path to devkitA64. On Linux, this is typically `/opt/devkitpro/devkitA64`.
3. `ninja -C build` to start the build

On subsequent builds, just run `ninja -C build` from the project root.

**THIS WILL NOT PRODUCE A PLAYABLE GAME.**

## Contributing

[Contributing guidelines are available here.](Contributing.md)

## Resources

* The [ZeldaMods](https://zeldamods.org/wiki/Main_Page) wiki
* [MrCheeze's botw-tools](https://github.com/MrCheeze/botw-tools)
* [botw-re-notes](https://github.com/leoetlino/botw-re-notes)

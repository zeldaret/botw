# The Legend of Zelda: Breath of the Wild

[![Decompilation Progress][progress-badge]][progress] [![Decompilation Progress (functions)][fn-progress-badge]][fn-progress] [![Contributors][contributors-badge]][contributors] [![Discord Channel][discord-badge]][discord]

[progress]: https://botw.link/progress
[progress-badge]: https://img.shields.io/endpoint?url=https://botw.link/badges/progress.json

[fn-progress]: https://botw.link/progress
[fn-progress-badge]: https://img.shields.io/endpoint?url=https://botw.link/badges/fn_progress.json

[contributors]: https://github.com/zeldaret/botw/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/zeldaret/botw

[discord]: https://discord.zelda64.dev
[discord-badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF

This is an experimental, WIP decompilation of *The Legend of Zelda: Breath of the Wild* v1.5.0 (Switch).

**This repository does not contain game assets or RomFS content and *cannot* be used to play *Breath of the Wild*.**

The goal of this project is to better understand game internals, aid with glitch hunting and document existing knowledge in a permanent, unambiguous form which helps further reverse engineer the game.

Considering the large size of the executable (~40MB), it is not expected to reach 100% progress within a reasonable timeframe.

As a result, the project is unlikely to produce a working executable in the near future. It will help with understanding and reverse engineering the game even in its incomplete state, but it will **not** help with playing BotW or porting the game to other platforms, which is **explicitly a non-goal**.

Progress: https://botw.link/progress

## Scope

This project only concerns the main executable which contains all the game code and statically linked libraries. The RomFS and the SDK libraries are *out of the scope* of this project.

* Main executable (main NSO)
    * *Breath of the Wild* code
        * Actual game code (`Game` / uking:: namespace)
        * Framework/engine code (`KingSystem` / ksys:: namespace)
    * Statically linked libraries
        * First-party libraries (e.g. sead, agl, EventFlow, etc.)
        * NintendoSDK inlined utilities
        * Any other statically linked library, except:
            * libcurl
            * NintendoSDK-NEX
            * Havok (physics engine)

Excluded libraries will not be fully decompiled but may be partly re-implemented or decompiled, and (reverse-engineered) headers will still be provided so that the rest of the codebase can still use those libraries.

## Frequently Asked Questions

### What is (matching) decompilation?

Decompiling is the process of turning the game's compiled code back into equivalent, readable C++ source code.

Matching decompilation goes one step further and produces original source code that **compiles to the exact same assembly**. This process makes functional correctness extremely easy to verify since the assembly can simply be compared against the original executable. Thanks to Clang, this is easier than one would expect.

#### Matching decomp in this project

Given the impossibility of automatically splitting the assembly and generating a matching binary (as is done in many other decomp projects), the sheer size of the main executable and the usage of many software libraries, this project takes a somewhat experimental approach to matching decompilation.

Because meaningfully splitting the code is not feasible, the built executable currently only contains functions that have been decompiled and no effort is being made to put functions and data at the correct addresses.

Instead of trying to match the entire executable, each function is matched individually and source code is organized in whichever way makes the most sense. Libraries are not treated as being part of the game code, but as external dependencies. The result is that the codebase looks a lot more like a regular software project than a decompilation codebase. Since C++ code makes heavy use of inline functions and zero-cost abstractions that disappear in compiled code, contributors have a lot more leeway when it comes to organizing files and adding abstractions.

### How do you name things?

File names, class or function names, and the file organization come from leftover strings. Unlike some other first-party games such as *Super Mario Odyssey*, all known public versions of U-King are completely stripped, so most names are just more or less educated guesses that try to fill in the blanks.

As more parts of the game get decompiled, it becomes easier to figure out what the rest of the game is doing and equally easier to name functions. It's a positive feedback loop.

### How easy is it to match functions?

Compared to other decomp projects for older compilers: **extremely easy**. Clang is an extremely reasonable compiler with much fewer memes than older compilers such as IDO or older versions of GCC:

* Stack reordering issues are extremely rare, given that AArch64 uses its registers a lot more efficiently. Even when the stack is used, things Just Work™ in the vast majority of cases.
* Pure register allocation (regalloc) issues are almost non-existent. If you see something that looks like a regalloc problem, it usually means your code is not semantically equivalent.
* No `if (1)` shenanigans.
* No "same line" memes (codegen being different if two statements are put on the same line).
* Whitespace doesn't matter.

In general, two equivalent constructs that *should* clearly produce the same code actually produce the exact same code. There are exceptions, of course, but many things simply do not matter at all for matching. Inline functions do often affect codegen, though.

Getting perfect matches on the first try happens pretty routinely, even for medium-sized and large functions (>1kB).

Most functions tend to call several other inline functions, notably utility functions from sead; as many core sead modules have already been reversed, decompiling a function sometimes only requires recognizing those function calls: decompilation at a higher level of abstraction!

### Doesn't this mean the end result will be quite inaccurate?

Even though Clang is generally less picky than ancient compilers, it is still able to reveal a lot of interesting information about how the original source code was written.

Granted, Clang will *not* reveal things such as whether developers put two statements on the same line, but in many cases we can still figure how they organised the source code and whether separate inline functions or classes were used.

Coupled with all the strings and all the information C++ language features leak (e.g. classes, virtual functions, hierarchy, etc.), we actually still get relevant, useful info (e.g. abstractions) that *actually* helps understand a modern codebase.

It is also important to remember that this is still a matching decompilation, which means that the code already perfectly matches the original *assembly*; matching functions are guaranteed to be fully equivalent to the original code, and thanks to Clang being picky *where it matters* most of the abstractions should match the original *source*.

### What version is being decompiled?

The Switch 1.5.0 version. Working with Clang is so much nicer than working with the Wii U's proprietary compiler (GHS). And at least an order of magnitude nicer than dealing with most compilers that are used for other matching decomp projects for that matter.

Having access to the Wii U 1.5.0 version is occasionally useful though, because GHS often optimizes and inlines differently, which can help reveal the existence of inline functions.

#### Why not decompile 1.6.0?

Because of aggressive compiler optimisations and severe code bloat, 1.6.0 would be extremely painful to reverse engineer, let alone decompile. [See here](https://gist.github.com/leoetlino/3156c286c7232c2e73b9b74b91021353) for a comparison between 1.5.0 and 1.6.0 code of the main function (called `nnMain`).

(The culprit is link time optimisation, which allows LLVM to perform extremely aggressive inlining even across translation units.)

### I only have 1.6.0. Can I still contribute?

Yes, you can! A delta patch is provided to turn a 1.6.0 executable into 1.5.0, so if you are able to dump 1.6.0 from your console you will also be able to get 1.5.0. Read on for more information...

### Do I need to be a game dev or a C++ expert to contribute?

No, of course not. You only need to be familiar with software development practices and C++, or another language with object-oriented aspects such as Java.

Unlike many other decomp projects, familiary with C or assembly helps but is not required. The reason for this is that BotW is a modern game with many layers of abstractions. Many functions can be decompiled simply by recognizing code patterns / inline functions. Our assembly comparing tool ([asm-differ](https://github.com/simonlindholm/asm-differ)) is also capable of showing what each line of assembly corresponds to in the source code, so you won't get lost in the assembly even if you're unfamiliar with AArch64.

AArch64 assembly is also nicer to deal with than x86/x86-64 and should feel familiar to you if you have already worked with e.g. ARM or MIPS.

This is pretty much an open source project, and even small contributions can make a large difference!

While you certainly do not need to be a C++ expert, you do need to be familiar with basic language features and concepts like namespaces or classes. Otherwise, you will be unable to contribute in any efficient or meaningful way.

### Isn't this risky?

Just like other game decompilations, this project is probably in a legal gray zone. However, the authors of this project believe that it is unlikely to bother NCL for the following reasons:

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

### Alright, how do I start contributing?

First, set up the build environment by following the instructions below.

## Building

Reminder: **this will not produce a playable game.** This project will not allow you to play the game if you don't already own it on a Switch.

### For Windows users

While Linux is not a hard requirement, it is strongly advised to [set up WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) to simplify the setup process. Ubuntu 20.04 is usually a good choice.

The instructions below assume that you are using Linux (native or WSL) or macOS.

### 1. Set up dependencies

* Python 3.6 or newer with [pip](https://pip.pypa.io/en/stable/installation/)
* Ninja
* CMake 3.13+
    * If you are on Ubuntu 18.04, you must first [update CMake by using the official CMake APT repository](https://apt.kitware.com/).
* ccache (to speed up builds)
* xdelta3
* Clang (not for compiling BotW code, but for compiling Rust tools)

Ubuntu users can install those dependencies by running:

```shell
sudo apt install python3 ninja-build cmake ccache xdelta3 clang libssl-dev
```

Additionally, you'll also need:

* A Rust toolchain ([follow the instructions here](https://www.rust-lang.org/tools/install))

* The following Python modules: `capstone colorama cxxfilt pyelftools ansiwrap watchdog python-Levenshtein toml` (install them with `pip install ...`)

### 2. Set up the project

1. Clone this repository. If you are using WSL, please clone the repo *inside* WSL, *not* on the Windows side (for performance reasons).

2. Run `git submodule update --init --recursive`

    Next, you'll need to acquire the **original 1.5.0 or 1.6.0 `main` NSO executable**.

    * To dump it from a Switch, follow [the instructions on the wiki](https://zeldamods.org/wiki/Help:Dumping_games#Dumping_binaries_.28executable_files.29).
    * You do not need to dump the entire game (RomFS + ExeFS + DLC). Just dumping the 1.5.0 or 1.6.0 ExeFS is sufficient.
    * The decompressed 1.5.0 NSO has the following SHA256 hash: `d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106`
        * If you have a compressed NSO or a 1.6.0 executable, don't worry about this.

3. Run `tools/setup.py [path to the NSO]`
    * This will:
        * install `tools/check` to check for differences in decompiled code
        * convert the executable if necessary
        * set up [Clang 4.0.1](https://releases.llvm.org/download.html#4.0.1) by downloading it from the official LLVM website
        * create a build directory in `build/`
    * If something goes wrong, follow the instructions given to you by the script.

### 3. Build

To start the build, just run

```shell
ninja -C build
```

By default, Ninja will perform a multithreaded build. There is no need to pass -j manually.

To check whether everything built correctly, just run `tools/check` after the build completes.

## Contributing

Follow the [contributing guidelines here](Contributing.md). Feel free to join the [Zelda Decompilation](https://discord.zelda64.dev/) Discord server if you have any questions.

## Resources

#### Breath of the Wild documentation and datamining

* The [ZeldaMods](https://zeldamods.org/wiki/Main_Page) wiki
* [MrCheeze's botw-tools](https://github.com/MrCheeze/botw-tools)
* [botw-re-notes](https://github.com/leoetlino/botw-re-notes)

#### AArch64

* AArch64 ISA overview: https://developer.arm.com/documentation/102374/0101 (read this first if you're new to AArch64)
* ARMv8 A64 Quick Reference: https://courses.cs.washington.edu/courses/cse469/18wi/Materials/arm64.pdf
* Arm ARMv8 ARM (Architecture Reference Manual): https://developer.arm.com/documentation/ddi0487/latest/ (extremely detailed)

#### Tools

* IDA Pro + Hex-Rays (7.5+ required if you want to use this project's database/IDC)
* HexRaysPyTools: https://github.com/igogo-x86/HexRaysPyTools
* How to create C++ types and vtables in IDA (7.2+): https://www.hex-rays.com/products/ida/support/idadoc/1691.shtml
* Ghidra: https://ghidra-sre.org/

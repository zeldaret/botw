# uking

This is a decompilation of U-King v1.5.0 (Switch).

File names, class or function names and the file organization come from leftover strings. Unlike some other first-party games such as *Super Mario Odyssey*, all known public versions of U-King are completely stripped, so most names are just more or less educated guesses.

**This repository only contains source code; it cannot be used to play *Breath of the Wild* and does *not* include any RomFS content.**

## Status

Currently, the focus is on decompiling AI classes and other small, mostly self-contained components (e.g. LevelSensor).

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

## Contributing

To contribute to the project, you will also need:

* A disassembler or a decompiler such as Hex-Rays or Ghidra.
* Python 3 and pip for the diff script
* These Python modules: `capstone colorama cxxfilt pyelftools` (install them with `pip install ...`)
* The original 1.5.0 `main` NSO executable, converted to ELF format with [nx2elf](https://github.com/shuffle2/nx2elf).
    * Copy it to data/main.elf -- it is used for the diff script and other tools.

Experience with reverse engineering optimized C++ code is very useful but not necessary if you already know how to decompile C code.

Using a decompiler is strongly recommended for efficiency reasons. If you have IDA 7.0+, ping @leoetlino to get a copy of the IDC which will make decompilation easier and help with understanding the code more generally.

Feel free to join the [Zelda Decompilation](https://discord.zelda64.dev/) Discord server if you have any questions.

*Note to contributors:* *Breath of the Wild* heavily relies on software libraries like [sead](https://github.com/open-ead/sead) which are statically linked. Given that most of BotW's dependencies have not been fully decompiled yet, decompiling any non-trivial part of the game might require working on those libraries first.

### How to decompile

0. Open the executable in the disassembler of your choice.

1. **Pick a function that you want to decompile.**
    * Prefer choosing a function that you understand or that is already named in your IDA/Ghidra database.
    * You do not need to fully understand the function, but you should at least have a rough idea of what it does.
    * If you are feeling more ambitious, pick an entire C++ class! This usually allows understanding the code better.

2. **Decompile it** using Hex-Rays or Ghidra.
    * Rename variables, add structures, do everything you can to make the output as clean as possible.
    * Again, understanding the function is very important.
    * C++ code tends to make heavy use of inline functions. For example, inlined string comparisons or copies are very common and tend to obscure what the function does. Focus on the outline of the function.

3. **Implement the function in C++.**
    * Stay close to the original code, but not too close: your code should mostly look like normal, clean C++ code. If it does not, chances are that you won't get a good match at all.
    * Keep in mind that decompilers can only produce C pseudocode. Some function calls may be member function calls.
    * Identify inlined functions and *uninline* them. For example, if you see a string copy, do **not** write the copy loop manually! Instead, call the inline function and let the compiler inline the function for you.
    * Identify duplicate pieces of code: those are usually a sign that functions have been inlined.

4. **Build**.
5. **Get the mangled name** of your function. For example, if you are decompiling BaseProcMgr::createInstance:

      ```
      $ tools/print_decomp_symbols.py -a | grep BaseProcMgr::createInstance
      UNLISTED  ksys::act::BaseProcMgr::createInstance(sead::Heap*) (_ZN4ksys3act11BaseProcMgr14createInstanceEPN4sead4HeapE)
      ```

6. **Add the mangled function name to the list of decompiled functions.**
    * To do so, open data/uking_functions.csv and search for the name or the address of function you have decompiled, and add the mangled function name to the last column.
    * Example: `0x00000071010c0d60,sub_71010C0D60,136,_ZN4ksys4util13TaskQueueBaseD1Ev`

7. **Compare the assembly** with `./diff.py --source <mangled function name>`
    * This will bring up a two-column diff. The code on the left is the original code; the code on the right is your version of the function.
    * You may ignore address differences (which often show up in adrp+ldr pairs or bl or b).

8. **Tweak the code to get a perfectly matching function**.
    * Clang is usually quite reasonable so it is very common for functions -- even complicated code -- to match on the first try.
    * If you have large differences (e.g. entire sections of code being at the wrong location), focus on getting rid of them first and ignore small differences like regalloc or trivial reorderings.
    * This is usually the most difficult part of matching decomp. Please ask on Discord if you need help!

9. **Update the list of decompiled functions**.
    * If you have a function that matches perfectly, great!
    * If there are still minor differences left, add a `// NON_MATCHING: ` comment to explain what is wrong and add a `?` at the end of the mangled function name in the CSV.
    * For major differences (lots of entirely red/green/blue lines in the diff), add a `!` at the end of the function name.

10. Before opening a PR, reformat the code with clang-format and run `tools/check.py`.

### Non-inlined functions

When **implementing non-inlined functions**, please compare the assembly output against the original function and make it match the original code. At this scale, that is pretty much the only reliable way to ensure accuracy and functional equivalency.

However, given the large number of functions, certain kinds of small differences can be ignored when a function would otherwise be equivalent:

* Regalloc differences.
    * Warning: ensure that the return type of the function is correct. Differences that involve the X0-X7, W0-W7 or S0-S3 registers at the end of a function are suspicious.

* Instruction reorderings when it is obvious the function is still semantically equivalent (e.g. two add/mov instructions that operate on entirely different registers being reordered)

### Header utilities or inlined functions

For **header-only utilities** (like container classes), use pilot/debug builds, assertion messages and common sense to try to undo function inlining. For example, if you see the same assertion appear in many functions and the file name is a header file, or if you see identical snippets of code in many different places, chances are that you are dealing with an inlined function. In that case, you should refactor the inlined code into its own function.

Also note that introducing inlined functions is sometimes necessary to get the desired codegen.

If a function is inlined, you should try as hard as possible to make it match perfectly. For inlined functions, it is better to use weird code or small hacks to force a match as differences would otherwise appear in every single function that inlines the non-matching code, which drastically complicates matching other functions. If a hack is used, wrap it inside a `#ifdef MATCHING_HACK_{PLATFORM}` (see below for a list of defines).

### Matching hacks

This project sometimes uses small hacks to force particular code to be generated by the compiler. Those have no semantic effects but can help with matching assembly code especially when the hacks are used for functions that are inlined.

* `MATCHING_HACK_NX_CLANG`: Hacks for Switch, when compiling with Clang.

### For people who are familiar with C or other decomp projects

Given the impossibility of automatically splitting the assembly and generating a matching binary, the sheer size of the main executable and the usage of many software libraries, this project takes a different and somewhat experimental approach to matching decompilation.

Instead of trying to match the entire executable, each function is matched individually and source code is organized in whichever way makes the most sense. Libraries are not treated as being part of the game code, but as external dependencies. The result is that the codebase looks a lot more like a regular software project than a decompilation codebase. Since C++ code makes heavy use of inline functions and zero-cost abstractions that disappear in compiled code, contributors have a lot more leeway when it comes to organizing files and adding abstractions.

Unlike most other decompilation projects, this one targets a large modern game that is written in C++. While C and C++ have similar syntax, C++ is somewhat more complex than C and has many more language features. To avoid getting lost in C++ code, please familiarize yourself with the following, preferably *before* decompiling:

* [namespaces](https://en.cppreference.com/w/cpp/language/namespace)
    * Instead of using prefixes such as `z_` to avoid name conflicts, C++ code instead relies on namespaces.
* [classes](https://en.cppreference.com/w/cpp/language/class), including inheritance, polymorphism, virtual functions
    * C++ classes/structs are basically C structs on steroids. Notably, C++ classes can contain member functions.
    * Member functions get an implicit `this` argument, which is passed as if it were the first argument.
    * [Virtual member functions](https://en.cppreference.com/w/cpp/language/virtual) are member functions that can be overridden in derived classes.
    * Virtual member functions are usually implemented with a virtual function table or "vtable", which is a table of function pointers.
* [const correctness](https://isocpp.org/wiki/faq/const-correctness) for member functions
* iterators
* range-based for loops
* using nullptr instead of NULL
* C++11 / C++14 / C++17 features more generally

### Project tools

* Check all decompiled functions for issues: `tools/check.py`
* To compare assembly: `./diff.py <mangled function name>`
    * The function **must be listed in data/uking_functions.csv first**.
        * To do so, search for the name or the address of function you have decompiled, and add the mangled function name to the last column.
    * Pass the `--source` flag to show source code interleaved with assembly code.
    * Add the `--inlines` flag to show inline function calls. This is not enabled by default because it usually produces too much output to be useful.
    * For more options, see [asm-differ](https://github.com/simonlindholm/asm-differ).
* To print progress: `tools/progress.py`
    * Note that progress is only approximate because of inline functions, templating and compiler-generated functions.
* To dump symbols: `tools/print_decomp_symbols.py`
    * `-u` for undefined symbols (default)
    * `-a` for all symbols
    * Useful for getting the mangled name of a function. For example:

        ```
        $ tools/print_decomp_symbols.py -a | grep BaseProcMgr::createInstance
      UNLISTED  ksys::act::BaseProcMgr::createInstance(sead::Heap*) (_ZN4ksys3act11BaseProcMgr14createInstanceEPN4sead4HeapE)
        ```

### Resources

* The [ZeldaMods](https://zeldamods.org/wiki/Main_Page) wiki
* [MrCheeze's botw-tools](https://github.com/MrCheeze/botw-tools)
* [botw-re-notes](https://github.com/leoetlino/botw-re-notes)

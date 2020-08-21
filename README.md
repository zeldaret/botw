# uking

This is a decompilation of U-King v1.5.0 (Switch).

File names, class or function names and the file organization come from leftover strings. Unlike some other first-party games such as *Super Mario Odyssey*, all known public versions of U-King are completely stripped, so most names are just more or less educated guesses.

Currently, the focus is on decompiling AI classes and other small, mostly self-contained components (e.g. LevelSensor).

## Building

Building this project requires:

- A C++17 capable compiler (or >= Clang 4.0)
- Ninja (Ubuntu/Debian package: `ninja-build`)
- CMake 3.13+

If you are on Ubuntu 18.04, you can [update CMake by using the official CMake APT repository](https://apt.kitware.com/).

### Building a matching version for Switch

1. Download [Clang 4.0.1](https://releases.llvm.org/download.html#4.0.1) and extract the archive.
2. Set the UKING_CLANG environment variable to point to the extracted archive, such that `$UKING_CLANG/bin/clang` exists.
3. You'll also need devkitA64. Set the DEVKITA64 environment variable. For Linux, $DEVKITA64 is typically `/opt/devkitpro/devkitA64`.
    * Also add devkitA64 to your PATH: `export PATH=${DEVKITPRO}/devkitA64/bin:$PATH`
4. In the root of this repository, run: `mkdir build`
5. `cd build`
6. `cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../ToolchainNX64.cmake ..`
7. `ninja` to start the build

On subsequent builds, just run `ninja -C build` from the project root.

If you are using Visual Studio Code, installing the CMake Tools extension is recommended to make includes, compiler flags, etc. work automatically.

## Contributing

Using a decompiler such as Hex-Rays or Ghidra is strongly recommended.

### Resources

* The [ZeldaMods](https://zeldamods.org/wiki/Main_Page) wiki
* [MrCheeze's botw-tools](https://github.com/MrCheeze/botw-tools)
* [botw-re-notes](https://github.com/leoetlino/botw-re-notes)

### Project tools

* To compare assembly: `./diff.py <mangled function name>`
    * The function must be listed in data/uking_functions.csv first.
    * [asm-differ](https://github.com/simonlindholm/asm-differ) must be in your $PATH, such that running `asm-differ` works.
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

### Non-inlined functions
When **implementing non-inlined functions**, please compare the assembly output against the original function and make it match the original code. At this scale, that is pretty much the only reliable way to ensure accuracy and functional equivalency.

However, given the large number of functions, certain kinds of small differences can be ignored when a function would otherwise be equivalent:

* Regalloc differences.

* Instruction reorderings when it is obvious the function is still semantically equivalent (e.g. two add/mov instructions that operate on entirely different registers being reordered)

When ignoring minor differences, add a `// NOT_MATCHING: explanation` comment and explain what does not match.

Finally, add the mangled name of each function you have decompiled to data/uking_functions.csv to make it easier to track progress.

### Header utilities or inlined functions
For **header-only utilities** (like container classes), use pilot/debug builds, assertion messages and common sense to try to undo function inlining. For example, if you see the same assertion appear in many functions and the file name is a header file, or if you see identical snippets of code in many different places, chances are that you are dealing with an inlined function. In that case, you should refactor the inlined code into its own function.

Also note that introducing inlined functions is sometimes necessary to get the desired codegen.

If a function is inlined, you should try as hard as possible to make it match perfectly. For inlined functions, it is better to use weird code or small hacks to force a match as differences would otherwise appear in every single function that inlines the non-matching code, which drastically complicates matching other functions. If a hack is used, wrap it inside a `#ifdef MATCHING_HACK_{PLATFORM}` (see below for a list of defines).

### Matching hacks

This project sometimes uses small hacks to force particular code to be generated by the compiler. Those have no semantic effects but can help with matching assembly code especially when the hacks are used for functions that are inlined.

* `MATCHING_HACK_NX_CLANG`: Hacks for Switch, when compiling with Clang.

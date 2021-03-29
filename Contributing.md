# Contributing

To contribute to the project, you will need:

* A disassembler or a decompiler such as Hex-Rays or Ghidra.
* Python 3 and pip for the diff script
* These Python modules: `capstone colorama cxxfilt pyelftools` (install them with `pip install ...`)
* The original 1.5.0 `main` NSO executable, converted to ELF format with [nx2elf](https://github.com/shuffle2/nx2elf).
    * To dump it, follow [the instructions on the wiki](https://zeldamods.org/wiki/Help:Dumping_games#Dumping_binaries_.28executable_files.29). If you only have 1.6.0 on your console, you should still dump it.
    * Decompress the `main` NSO with [hactool](https://github.com/SciresM/hactool).
    * If you have a 1.6.0 dump, use xdelta3 on the decompressed NSO to turn it into a 1.5.0 NSO. [The patch is available here.](https://s.botw.link/v150_downgrade/v160_to_v150.patch)
    * The uncompressed NSO has the following SHA256 hash: `d9fa308d0ee7c0ab081c66d987523385e1afe06f66731bbfa32628438521c106`
    * Copy it to data/main.elf -- it is used for the diff script and other tools.

Experience with reverse engineering optimized C++ code is very useful but not necessary if you already know how to decompile C code.

Using a decompiler is strongly recommended for efficiency reasons. If you have IDA 7.0+, ping @leoetlino to get a copy of the IDC which will make decompilation easier and help with understanding the code more generally.

Feel free to join the [Zelda Decompilation](https://discord.zelda64.dev/) Discord server if you have any questions.

## Language

This project is written in C++17. (Technically, in a subset of C++17, since Clang 4.0.1 supports most of C++17 but not all of it.)

Unlike the vast majority of games that are being decompiled in 2021, *Breath of the Wild* is a large modern game that is written in C++. While C and C++ have a similar syntax, C++ is somewhat more complex than C. To avoid getting lost in C++ code, please familiarize yourself with the following basic language concepts *before* decompiling:

* [namespaces](https://en.cppreference.com/w/cpp/language/namespace)
    * Instead of using prefixes such as `z_` to avoid name conflicts, C++ code instead relies on namespaces.
* [classes](https://en.cppreference.com/w/cpp/language/class), including inheritance, polymorphism, virtual functions
    * C++ classes/structs are basically C structs on steroids. Notably, C++ classes can contain member functions.
    * Member functions get an implicit `this` argument, which is passed as if it were the first argument.
    * [Virtual member functions](https://en.cppreference.com/w/cpp/language/virtual) are member functions that can be overridden in derived classes.
    * Virtual member functions are usually implemented with a virtual function table or "vtable", which is a table of function pointers.
* [const correctness](https://isocpp.org/wiki/faq/const-correctness) for member functions
* iterators and range-based for loops (e.g. `for (int i : my_list_of_ints) {}`)

## Code style

This project uses clang-format to enforce a consistent coding style. Before opening a PR, please format your code with clang-format and ensure the following guidelines are followed.

This will allow your contributions to be reviewed more quickly.

### General

* Lines should not be longer than 100 characters.
* Use 4 spaces to indent.
* Use `nullptr`, not `NULL` or `0`.
* Only use `auto` if the variable type is obvious, too long to type or if it doesn't matter.
* To compare a value against zero, write `if (value == 0)`, not `if (!value)`.
* To compare a value against nullptr, either `if (pointer != nullptr)` or `if (pointer)` is fine.

### Header files

* Use `#pragma once` for header guards.
* Avoid unnecessary includes. Forward declare types when possible to reduce compilation times.

### Includes

* Use `#include "..."` when including U-King (BotW) header files. KingSystem (ksys) is treated as being part of BotW.
    * Include paths should be relative to src/.
        * OK: `#include "KingSystem/ActorSystem/actActor.h"`
        * Not OK: `#include "actActor.h"`

* Use `#include <...>` for system or library includes. Examples:
    * Standard C++ library headers (e.g. `<optional>`, `<type_traits>`, `<limits>`, ...)
    * sead (e.g. `<prim/seadSafeString.h>`)
    * Other Nintendo libraries like agl, evfl, eui, ...

### Naming

* Type names (classes/structs, enums, typedefs/alias declarations) and compile-time constants should be in UpperCamelCase.
    * `class ActorInfoData`
    * `using Manager = ksys::gdt::Manager;`
    * `constexpr int NumActors = 42;`

* Function names should be in camelCase.
    * `void doStuff()`
    * `void SomeClass::doThis()` (for a member function)

* Variables should be in lowercase_snake_case, except for class member variables, which should be prefixed with 'm' and writtenLikeThis.
    * `int a_dummy_variable = 42;`
    * `void test(int first_argument, bool second_argument) { ... }`
    * `class SomeClass { int mMemberVariable; };` (m prefix + camelCase)
    * `struct SomeStruct { int member_variable; };` (regular snake_case)

* Static variables should be prefixed with 's' and globals with 'g'.
    * `s_static_variable`
    * `sStaticVariable` if it's a static member variable

### Classes

* Put access specifiers in this order: `public`, `protected`, `private`.
* Declare member functions in this order: constructor, destructor, operators, other member functions.
    * Virtual functions need to match the original order in the executable, though, so ignore this rule if following it would require reordering virtual functions.
* Declare static member variables before non-static variables.
* If a class uses a macro like `SEAD_SINGLETON_DISPOSER` or one of the SEAD_RTTI macros, put the macro right after the opening brace, before `public:`.
* Use `= default;` instead of constructors/destructors with an empty body.
* Use the `override` keyword instead of `virtual` when overriding virtual functions from a parent class.
* Mark member functions as const if they do not modify any non-static member variables.
* Do not use `this->` to refer to member variables or member functions unless it is necessary. (It is usually unnecessary.)

```cpp
class Test {
    SEAD_RTTI_BASE(Test)

public:
    Test();
    virtual ~Test() = default;
    virtual bool isTest() const { return true; }
    void doStuff() {}

private:
    static bool sFoo = false;
    bool mMemberVariable = true;
};

class TestDerived : public Test {
public:
    bool isTest() const override { return false; }
};
```

## How to decompile

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
    * **Focus on large differences.** If you have large differences (e.g. entire sections of code being at the wrong location), focus on getting rid of them first and ignore small differences like regalloc or trivial reorderings.
    * **Regalloc:** If you only have regalloc differences left in a function that *looks* semantically equivalent, double-check whether it is truly equivalent: such differences are typically caused by using the wrong variable. It is rare for LLVM to use a different set of registers if the code is equivalent.
    * This is usually the most difficult part of matching decomp. Please ask on Discord if you need help!

9. **Update the list of decompiled functions**.
    * If you have a function that matches perfectly, great!
    * If there are still minor differences left, add a `// NON_MATCHING: ` comment to explain what is wrong and add a `?` at the end of the mangled function name in the CSV.
    * For major differences (lots of entirely red/green/blue lines in the diff), add a `!` at the end of the function name.

10. Before opening a PR, reformat the code with clang-format and run `tools/check.py`.

## Non-inlined functions

When **implementing non-inlined functions**, please compare the assembly output against the original function and make it match the original code. At this scale, that is pretty much the only reliable way to ensure accuracy and functional equivalency.

However, given the large number of functions, certain kinds of small differences can be ignored when a function would otherwise be equivalent:

* Regalloc differences.
    * Warning: ensure that the return type of the function is correct. Differences that involve the X0-X7, W0-W7 or S0-S3 registers at the end of a function are suspicious.

* Instruction reorderings when it is obvious the function is still semantically equivalent (e.g. two add/mov instructions that operate on entirely different registers being reordered)

## Header utilities or inlined functions

For **header-only utilities** (like container classes), use pilot/debug builds, assertion messages and common sense to try to undo function inlining. For example, if you see the same assertion appear in many functions and the file name is a header file, or if you see identical snippets of code in many different places, chances are that you are dealing with an inlined function. In that case, you should refactor the inlined code into its own function.

Also note that introducing inlined functions is sometimes necessary to get the desired codegen.

If a function is inlined, you should try as hard as possible to make it match perfectly. For inlined functions, it is better to use weird code or small hacks to force a match as differences would otherwise appear in every single function that inlines the non-matching code, which drastically complicates matching other functions. If a hack is used, wrap it inside a `#ifdef MATCHING_HACK_{PLATFORM}` (see below for a list of defines).

### Matching hacks

This project sometimes uses small hacks to force particular code to be generated by the compiler. Those have no semantic effects but can help with matching assembly code especially when the hacks are used for functions that are inlined.

* `MATCHING_HACK_NX_CLANG`: Hacks for Switch, when compiling with Clang.

## Project tools

* Check all decompiled functions for issues: `tools/check.py`
* To compare assembly: `./diff.py <mangled function name>`
    * The function **must be listed in data/uking_functions.csv first**.
        * To do so, search for the name or the address of function you have decompiled, and add the mangled function name to the last column.
    * Pass the `--source` flag to show source code interleaved with assembly code.
    * Add the `--inlines` flag to show inline function calls. This is not enabled by default because it usually produces too much output to be useful.
    * For more options, see [asm-differ](https://github.com/simonlindholm/asm-differ).
* To print progress: `tools/progress.py`
    * Note that progress is only approximate because of inline functions, templating and compiler-generated functions.
* To print AI class decompilation status: `tools/ai_progress.py`
    * Use this to figure out which AI classes have not been decompiled yet.
* To dump symbols: `tools/print_decomp_symbols.py`
    * Pass `-a` to list all symbols
    * Useful for getting the mangled name of a function. For example:

        ```
        $ tools/print_decomp_symbols.py -a | grep BaseProcMgr::createInstance
      UNLISTED  ksys::act::BaseProcMgr::createInstance(sead::Heap*) (_ZN4ksys3act11BaseProcMgr14createInstanceEPN4sead4HeapE)
        ```

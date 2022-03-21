# Contributing

To contribute to the project, you will need a disassembler or a decompiler such as Hex-Rays or Ghidra.

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

## Editor/IDE setup

BotW is mostly set up like a normal C++ project using standard build tools and compilers like Clang, CMake, Ninja, etc. so autocomplete and "IntelliSense" style features should work almost out-of-the-box.

### VSCode

Make sure you have the C++ and the CMake Tools extensions installed and enabled. And then just answer "yes" when you're asked whether you would like CMake Tools to configure IntelliSense for you.

### CLion

CLion interacts with CMake directly, so you need to make sure CLion's build profile is configured correctly.

1. Open the Settings window and go to the Build > CMake pane.
2. Remove all existing build profiles, and add a new build profile (call it whatever you want):
    * Build type: RelWithDebInfo
    * CMake options: `-DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -GNinja`
    * Build directory: `build`
3. Press OK; CLion will automatically reload the CMake project.

## How to decompile

0. Open the NSO executable in the disassembler of your choice.
   * If you are using IDA, make sure you have the [NSO loader](https://github.com/reswitched/loaders) set up first!

1. **Pick a function that you want to decompile.**
    * Prefer choosing a function that you understand or that is already named in your IDA/Ghidra database.
    * Use our [Trello project board](https://botw.link/trello) to figure out what needs to be decompiled. Make sure it's not already being worked on by somebody else!
        * The "Blocked" label means that the task cannot be easily done at the moment because it requires something else to be decompiled or stubbed first.
        * "Easy" tasks are recommended to familiarize yourself with the process. They can typically be done pretty quickly.
        * "Requires library integration" tasks require decompiling an external library (e.g. agl, sead, ...) and integrating it into the project.
        * "Manager/singleton" means that the task is about a manager or a singleton (a class with only a single instance).
        * If you want to work on libraries rather than on BotW code, take a look at [this board](https://botw.link/trello-libs)!
        * Search for the card's label in IDA to locate relevant functions to decomp. If you can't find any good match, feel free to ask somebody to clarify the task on the help channel on Discord.
    * You do not need to fully understand the function, but you should at least have a rough idea of what it does.
    * If you are feeling more ambitious, pick an entire C++ class! This usually allows understanding the code better.

2. **Try to understand** what the function does using Hex-Rays or Ghidra.
    * Understanding the function is very important.
    * Rename variables, add structures, do everything you can to make the output as clean as possible.
    * C++ code tends to make heavy use of inline functions. For example, inlined string comparisons or copies are very common and tend to obscure what the function does. Focus on the outline of the function.
    * The [cheatsheet](Cheatsheet.md) might help you recognize inline functions.

3. **Implement the function in C++.**
    * Stay close to the original code, but not too close: your code should mostly look like normal, clean C++ code. If it does not, chances are that you won't get a good match at all.
    * Do **NOT** copy and paste any pseudocode. **Reimplement it**. While we cannot go for a fully "clean room" approach, you should be reimplementing code, not copy/pasting anything from the original executable.
        * PRs that violate this rule will be rejected.
    * Keep in mind that decompilers can only produce C pseudocode. Some function calls may be member function calls.
    * Identify inlined functions and *uninline* them. For example, if you see a string copy, do **not** write the copy loop manually! Instead, call the inline function and let the compiler inline the function for you.
    * Identify duplicate pieces of code: those are usually a sign that functions have been inlined.
    * Non-inline function calls can just be stubbed if you don't feel like decompiling them at the moment. To "stub" a function, just declare the function (and the enclosing class/namespace/etc. if needed) without implementing/defining it.
    * Follow the [coding style guidelines](#code-style) where applicable.

4. **Build**.

5. **Add the function name to the list of decompiled functions.**
    * To do so, open `data/uking_functions.csv`, search for the name or the address of function you have decompiled, and add the function name to the last column.
    * Example: `0x00000071010c0d60,U,136,BaseProcMgr::createInstance`

6. **Compare the assembly** with `tools/check -mw <function name>`
    * This will bring up a two-column diff. The code on the left is the original code; the code on the right is your version of the function.
    * You may ignore address differences (which often show up in adrp+ldr pairs or bl or b).
    * If you modify a source file while the diff is visible, it will be automatically rebuilt and the diff will update to match the new assembly code.
      * Remove `-mw` from the command if you do not want automatic rebuilds.
    * Other useful flags:
      * To show C++ source code interleaved with the assembly in the diff, pass `-c` or `--source`.
      * To get a three-column diff (original, decomp, diff with last decomp attempt), pass `-3` (do not use with `-c`).

7. **Tweak the code to get a perfectly matching function**.
    * Clang is usually quite reasonable so it is very common for functions -- even complicated code -- to match on the first try.
    * **Focus on large differences.** If you have large differences (e.g. entire sections of code being at the wrong location), focus on getting rid of them first and ignore small differences like regalloc or trivial reorderings.
    * **Regalloc:** If you only have regalloc differences left in a function that *looks* semantically equivalent, double-check whether it is truly equivalent: such differences are typically caused by using the wrong variable. It is rare for LLVM to use a different set of registers if the code is equivalent.
    * This is usually the most difficult part of matching decomp. Please ask on Discord if you need help!
    * The [cheatsheet](Cheatsheet.md) might help you recognize code patterns and contains a checklist for common matching issues.

8. **Update the list of decompiled functions**.
    * If you have a function that matches perfectly, great!
    * If there are still minor differences left, write a comment to explain what is wrong (if you think that is necessary), and change the status (the second column) to `m` (minor difference) in the CSV.
    * For major differences (lots of entirely red/green/blue lines in the diff), use a capital `M` (major difference) in place of `m`.

9. Before opening a PR, reformat the code with clang-format and run `tools/check`.
    * You can use clang-format via your editor – VSCode and CLion have built-in clang-format support — or by calling `git clang-format` (for files you have `git add`ed and not yet committed).
    * If your editor does not have built-in support for clang-format, or if you need to invoke clang-format in a terminal, you'll need to install it manually.
      * If your Linux distro or system (e.g. macOS) does not package clang-format 12, you can download it from [the LLVM project website here](https://releases.llvm.org/download.html)

## Code style

BotW has 40MB of code and contributors *need* to read and modify existing parts of the codebase very often: inconsistencies lead to a loss of efficiency, and we literally cannot afford that considering our small number of contributors. To avoid wasting time on formatting issues, we use clang-format to automatically enforce a consistent coding style.

Before opening a PR, please format your code with clang-format 12 and ensure the following guidelines are followed. This will allow your contributions to be reviewed more quickly.

### General

* Lines should not be longer than 100 characters.
* Use 4 spaces to indent.
* Use `nullptr`, not `NULL` or `0`.
* Only use `auto` if the variable type is obvious, too long to type or if it doesn't matter.
* To compare an integer against zero, write `if (value == 0)`, not `if (!value)`. (This rule doesn't apply to booleans.)
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
* Ordering
   * Put access specifiers in this order: `public`, `protected`, `private`.
   * Declare member functions in this order: constructor, destructor, operators, other member functions.
   * Declare non-static member variables after function declarations.
   * Declare static member variables before non-static variables.
   * Virtual functions need to match the original order in the executable, though, so ignore this rule if following it would require reordering virtual functions.
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

## Modifying library code

Changes to the following libraries must be PR'd/submitted to their own repository:

* sead: https://github.com/open-ead/sead
* NintendoSDK: https://github.com/open-ead/nnheaders
* agl: https://github.com/open-ead/agl
* EventFlow: https://github.com/open-ead/EventFlow

The recommended workflow is to commit your changes as usual in the BotW repo, and then do a "subrepo push" to
your fork of the library repo once you are ready to open a pull request.

Example:

```
echo test > lib/sead/test_file
git add -A
git commit -m "test"
git subrepo push lib/sead -r <your fork> -b <new branch name in your fork>
```

You can then open one PR in the BotW repo and another one in the library repo.

Once the library repo PR has been merged, a maintainer will let you know what you should do
to update the library subrepo in the BotW repo.

Follow the [instructions here](https://github.com/ingydotnet/git-subrepo#installation) to install the git-subrepo command
if you do not already have it.

### Updating the library repos

Library subrepos can be updated with e.g. `git subrepo pull lib/sead`. This will pull the latest changes from the
library repository and git-subrepo will automatically create a commit in the BotW repo to reflect the changes.
Do not attempt to amend  the commit message -- doing so could break the subrepo.

## Project tools

* Check all decompiled functions for issues: `tools/check`
* To compare assembly: `tools/check <mangled function name>`
    * The function **must be listed in data/uking_functions.csv first**.
        * To do so, search for the name or the address of function you have decompiled, and add the mangled function name to the last column.
    * Pass the `--source` flag to show source code interleaved with assembly code.
    * Add the `--inlines` flag to show inline function calls. This is not enabled by default because it usually produces too much output to be useful.
    * Pass `-mw3` for automatic rebuilds whenever a source file is modified.
    * For more options, see [asm-differ](https://github.com/simonlindholm/asm-differ).
* To print progress: `tools/common/progress.py`
    * Note that progress is only approximate because of inline functions, templating and compiler-generated functions.
* To print AI class decompilation status: `tools/ai_progress.py`
    * Use this to figure out which AI classes have not been decompiled yet.
* To list symbols: `tools/listsym` (pass --help to see available options)

#pragma once

#include <type_traits>

namespace sead
{
/// For storing an enum with a particular storage size when specifying the underlying type of the
/// enum is not an option.
template <typename Enum, typename Storage>
struct SizedEnum
{
    static_assert(std::is_enum<Enum>());
    static_assert(!std::is_enum<Storage>());

    constexpr SizedEnum() = default;
    constexpr SizedEnum(Enum value) { *this = value; }
    constexpr operator Enum() const { return static_cast<Enum>(mValue); }
    constexpr SizedEnum& operator=(Enum value)
    {
        mValue = static_cast<Storage>(value);
        return *this;
    }

    Storage mValue;
};
}  // namespace sead

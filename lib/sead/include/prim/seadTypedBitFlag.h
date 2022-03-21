#pragma once

#include <initializer_list>
#include <type_traits>

#include "prim/seadBitFlag.h"

namespace sead
{
template <typename Enum, typename Storage = std::underlying_type_t<Enum>>
class TypedBitFlag
{
public:
    static_assert(std::is_enum<Enum>(), "Enum must be an enum");
    using UnderlyingType = std::underlying_type_t<Enum>;

    TypedBitFlag() : mBits(0) {}
    explicit TypedBitFlag(UnderlyingType bits) : mBits(bits) {}
    TypedBitFlag(Enum bits) : mBits(UnderlyingType(bits)) {}
    template <typename T>
    explicit TypedBitFlag(const TypedBitFlag<Enum, T>& other)
    {
        *this = other;
    }

    template <typename T>
    TypedBitFlag& operator=(const TypedBitFlag<Enum, T>& other)
    {
        mBits = other.getDirect();
        return *this;
    }

    TypedBitFlag& operator=(Enum value)
    {
        setDirect(value);
        return *this;
    }

    void makeAllZero() { mBits = 0; }
    void makeAllOne() { mBits = ~UnderlyingType(0); }

    void setDirect(UnderlyingType bits) { mBits = bits; }
    void setDirect(Enum bits) { mBits = UnderlyingType(bits); }
    UnderlyingType getDirect() const { return mBits; }
    Storage& getStorage() { return mBits; }

    bool set(Enum val)
    {
        const auto mask = UnderlyingType(val);
        return ((mBits |= mask) & mask) == 0;
    }

    bool reset(Enum val)
    {
        const auto mask = UnderlyingType(val);
        return ((mBits &= ~mask) & mask) != 0;
    }

    UnderlyingType toggle(Enum val) { mBits ^= UnderlyingType(val); }
    bool change(Enum val, bool on) { return on ? set(val) : reset(val); }
    bool isZero() const { return mBits == 0; }
    /// Checks if (at least) one of the bits are set.
    bool isOn(Enum val) const { return (mBits & UnderlyingType(val)) != 0; }
    bool isAnyOn(std::initializer_list<Enum> list) const { return (mBits & orEnums_(list)) != 0; }
    /// Checks if all of the bits are set.
    bool isOnAll(Enum val) const { return (mBits & UnderlyingType(val)) == UnderlyingType(val); }
    bool isOff(Enum val) const { return !isOn(val); }

    bool testAndClear(Enum val)
    {
        if (!isOn(val))
            return false;
        reset(val);
        return true;
    }

    /// Popcount.
    int countOnBit() const
    {
        if constexpr (sizeof(UnderlyingType) <= 4)
            return BitFlagUtil::countOnBit(mBits);
        else
            return BitFlagUtil::countOnBit64(mBits);
    }
    /// Count trailing zeroes.
    int countContinuousOffBitFromRight() const
    {
        if constexpr (sizeof(UnderlyingType) <= 4)
            return BitFlagUtil::countContinuousOffBitFromRight(mBits);
        else
            return BitFlagUtil::countContinuousOffBitFromRight64(mBits);
    }
    int countRightOnBit(int bit) const
    {
        if constexpr (sizeof(UnderlyingType) <= 4)
            return BitFlagUtil::countRightOnBit(mBits, bit);
        else
            return BitFlagUtil::countRightOnBit64(mBits, bit);
    }
    int findOnBitFromRight(int num) const
    {
        if constexpr (sizeof(UnderlyingType) <= 4)
            return BitFlagUtil::findOnBitFromRight(mBits, num);
        else
            return BitFlagUtil::findOnBitFromRight64(mBits, num);
    }

protected:
    static constexpr UnderlyingType orEnums_(std::initializer_list<Enum> list)
    {
        UnderlyingType value{};
        for (auto x : list)
            value |= static_cast<UnderlyingType>(x);
        return value;
    }

    Storage mBits;
};
}  // namespace sead

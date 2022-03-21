#pragma once

#include <array>
#include <type_traits>

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>

namespace sead
{
template <s32 N, typename Enum, typename Storage = std::underlying_type_t<Enum>>
class TypedLongBitFlag
{
public:
    using Word = Storage;
    using RawWord = std::conditional_t<(sizeof(Storage) > 4), u64, u32>;

    void makeAllZero() { mStorage.fill(0); }
    void makeAllOne() { mStorage.fill(~Word(0)); }

    Word& getWord(Enum bit);
    const Word& getWord(Enum bit) const;

    bool isZero() const;

    void setBit(Enum bit);
    void resetBit(Enum bit);
    void changeBit(Enum bit, bool on);
    void toggleBit(Enum bit);
    bool isOnBit(Enum bit) const;
    bool isOffBit(Enum bit) const;

    /// Popcount.
    int countOnBit() const;

protected:
    template <typename T>
    auto getWord(Enum bit, const T& fn)
    {
        return fn(getWord(bit), RawWord(bit) % BitsPerWord);
    }

    template <typename T>
    auto getWord(Enum bit, const T& fn) const
    {
        return fn(getWord(bit), RawWord(bit) % BitsPerWord);
    }

    static constexpr s32 BitsPerWord = 8 * sizeof(Word);
    static constexpr s32 Shift = log2(BitsPerWord);

    static_assert(N % BitsPerWord == 0, "N must be a multiple of the number of bits per word");
    std::array<Word, N / BitsPerWord> mStorage{};
};

template <s32 N, typename Enum, typename Storage>
inline typename TypedLongBitFlag<N, Enum, Storage>::Word&
TypedLongBitFlag<N, Enum, Storage>::getWord(Enum bit)
{
    SEAD_ASSERT_MSG(u32(bit) < u32(N), "range over [0,%d) : %d", N, s32(bit));
    return mStorage[s32(bit) >> Shift];
}

template <s32 N, typename Enum, typename Storage>
inline const typename TypedLongBitFlag<N, Enum, Storage>::Word&
TypedLongBitFlag<N, Enum, Storage>::getWord(Enum bit) const
{
    SEAD_ASSERT_MSG(u32(bit) < u32(N), "range over [0,%d) : %d", N, s32(bit));
    return mStorage[s32(bit) >> Shift];
}

template <s32 N, typename Enum, typename Storage>
inline void TypedLongBitFlag<N, Enum, Storage>::setBit(Enum bit)
{
    getWord(bit, [](auto& word, auto b) { word |= 1 << b; });
}

template <s32 N, typename Enum, typename Storage>
inline void TypedLongBitFlag<N, Enum, Storage>::resetBit(Enum bit)
{
    getWord(bit, [](auto& word, auto b) { word &= ~(1 << b); });
}

template <s32 N, typename Enum, typename Storage>
inline void TypedLongBitFlag<N, Enum, Storage>::changeBit(Enum bit, bool on)
{
    if (on)
        setBit(bit);
    else
        resetBit(bit);
}

template <s32 N, typename Enum, typename Storage>
inline void TypedLongBitFlag<N, Enum, Storage>::toggleBit(Enum bit)
{
    getWord(bit, [](auto& word, auto b) { word ^= 1 << b; });
}

template <s32 N, typename Enum, typename Storage>
inline bool TypedLongBitFlag<N, Enum, Storage>::isOnBit(Enum bit) const
{
    return getWord(bit, [](const auto& word, auto b) { return word & (1 << b); });
}

template <s32 N, typename Enum, typename Storage>
inline bool TypedLongBitFlag<N, Enum, Storage>::isOffBit(Enum bit) const
{
    return !isOnBit(bit);
}

template <s32 N, typename Enum, typename Storage>
inline bool TypedLongBitFlag<N, Enum, Storage>::isZero() const
{
    for (const auto& word : mStorage)
    {
        if (word != 0)
            return false;
    }
    return true;
}

template <s32 N, typename Enum, typename Storage>
inline int TypedLongBitFlag<N, Enum, Storage>::countOnBit() const
{
    // This is pretty inefficient, but it appears to be how popcount is implemented
    // in Lunchpack's Lp::Sys::ActorSystem::countActiveChildNum.
    s32 count = 0;
    for (s32 i = 0; i < N; ++i)
    {
        if (isOnBit(i))
            ++count;
    }
    return count;
}

}  // namespace sead

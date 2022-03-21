#pragma once

#include <array>

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>

namespace sead
{
template <s32 N>
class LongBitFlag
{
public:
    using Word = u32;

    void makeAllZero() { mStorage.fill(0); }
    void makeAllOne() { mStorage.fill(~Word(0)); }

    Word& getWord(int bit);
    const Word& getWord(int bit) const;

    bool isZero() const;

    void setBit(int bit);
    void resetBit(int bit);
    void changeBit(int bit, bool on);
    void toggleBit(int bit);
    bool isOnBit(int bit) const;
    bool isOffBit(int bit) const;

    /// Popcount.
    int countOnBit() const;

    static Word makeMask(int bit) { return 1u << (bit % BitsPerWord); }

protected:
    static constexpr s32 BitsPerWord = 8 * sizeof(Word);
    static constexpr s32 Shift = log2(BitsPerWord);

    static_assert(N % BitsPerWord == 0, "N must be a multiple of the number of bits per word");
    std::array<Word, N / BitsPerWord> mStorage{};
};

template <s32 N>
inline typename LongBitFlag<N>::Word& LongBitFlag<N>::getWord(int bit)
{
    SEAD_ASSERT_MSG(u32(bit) < u32(N), "range over [0,%d) : %d", N, bit);
    return mStorage[bit >> Shift];
}

template <s32 N>
inline const typename LongBitFlag<N>::Word& LongBitFlag<N>::getWord(int bit) const
{
    SEAD_ASSERT_MSG(u32(bit) < u32(N), "range over [0,%d) : %d", N, bit);
    return mStorage[bit >> Shift];
}

template <s32 N>
inline void LongBitFlag<N>::setBit(int bit)
{
    getWord(bit) |= makeMask(bit);
}

template <s32 N>
inline void LongBitFlag<N>::resetBit(int bit)
{
    getWord(bit) &= ~makeMask(bit);
}

template <s32 N>
inline void LongBitFlag<N>::changeBit(int bit, bool on)
{
    if (on)
        setBit(bit);
    else
        resetBit(bit);
}

template <s32 N>
inline void LongBitFlag<N>::toggleBit(int bit)
{
    getWord(bit) ^= makeMask(bit);
}

template <s32 N>
inline bool LongBitFlag<N>::isOnBit(int bit) const
{
    return (getWord(bit) & makeMask(bit)) != 0;
}

template <s32 N>
inline bool LongBitFlag<N>::isOffBit(int bit) const
{
    return !isOnBit(bit);
}

template <s32 N>
inline bool LongBitFlag<N>::isZero() const
{
    for (const u32 word : mStorage)
    {
        if (word != 0)
            return false;
    }
    return true;
}

template <s32 N>
inline int LongBitFlag<N>::countOnBit() const
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

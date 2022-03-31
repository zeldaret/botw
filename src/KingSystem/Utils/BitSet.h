#pragma once

#include <array>
#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>

namespace ksys::util {

template <int N>
class BitSet {
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
    int countRightOnBit(int bit) const;

    static Word makeMask(int bit) { return 1u << (bit % BitsPerWord); }

protected:
    static constexpr u32 BitsPerWord = 8 * sizeof(Word);

    static_assert(N % BitsPerWord == 0, "N must be a multiple of the number of bits per word");
    std::array<Word, N / BitsPerWord> mStorage{};
};

template <int N>
inline typename BitSet<N>::Word& BitSet<N>::getWord(int bit) {
    return mStorage[bit / BitsPerWord];
}

template <int N>
inline const typename BitSet<N>::Word& BitSet<N>::getWord(int bit) const {
    return mStorage[bit / BitsPerWord];
}

template <int N>
inline void BitSet<N>::setBit(int bit) {
    getWord(bit) |= makeMask(bit);
}

template <int N>
inline void BitSet<N>::resetBit(int bit) {
    getWord(bit) &= ~makeMask(bit);
}

template <int N>
inline void BitSet<N>::changeBit(int bit, bool on) {
    if (on)
        setBit(bit);
    else
        resetBit(bit);
}

template <int N>
inline void BitSet<N>::toggleBit(int bit) {
    getWord(bit) ^= makeMask(bit);
}

template <int N>
inline bool BitSet<N>::isOnBit(int bit) const {
    return (getWord(bit) & makeMask(bit)) != 0;
}

template <int N>
inline bool BitSet<N>::isOffBit(int bit) const {
    return !isOnBit(bit);
}

template <int N>
inline bool BitSet<N>::isZero() const {
    for (const Word word : mStorage) {
        if (word != 0)
            return false;
    }
    return true;
}

template <int N>
inline int BitSet<N>::countOnBit() const {
    int count = 0;
    for (const Word word : mStorage) {
        count += sead::BitFlagUtil::countOnBit(word);
    }
    return count;
}

template <int N>
inline int BitSet<N>::countRightOnBit(int bit) const {
    int count = 0;
    const auto last_word_index = u32(bit / BitsPerWord);
    for (u32 i = 0; i < last_word_index; ++i) {
        count += sead::BitFlagUtil::countOnBit(mStorage[i]);
    }
    count += sead::BitFlagUtil::countRightOnBit(mStorage[last_word_index], bit % BitsPerWord);
    return count;
}

}  // namespace ksys::util

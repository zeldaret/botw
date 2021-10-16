#pragma once

#include <array>
#include <type_traits>

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadMathCalcCommon.h>
#include <thread/seadAtomic.h>

namespace ksys::util {

template <s32 N, typename Enum>
class AtomicLongBitFlag {
public:
    using Word = sead::Atomic<u32>;

    void makeAllZero() { mStorage.fill(0); }
    void makeAllOne() { mStorage.fill(~Word(0)); }

    Word& getWord(Enum bit);
    const Word& getWord(Enum bit) const;

    bool isZero() const;

    bool setBit(Enum bit);
    bool resetBit(Enum bit);
    bool changeBit(Enum bit, bool on);
    bool isOnBit(Enum bit) const;
    bool isOffBit(Enum bit) const;

protected:
    static constexpr s32 BitsPerWord = 8 * sizeof(Word);

    static_assert(N % BitsPerWord == 0, "N must be a multiple of the number of bits per word");
    sead::SafeArray<Word, N / BitsPerWord> mStorage{};
};

template <s32 N, typename Enum>
inline typename AtomicLongBitFlag<N, Enum>::Word& AtomicLongBitFlag<N, Enum>::getWord(Enum bit) {
    return mStorage[s32(bit) / BitsPerWord];
}

template <s32 N, typename Enum>
inline const typename AtomicLongBitFlag<N, Enum>::Word&
AtomicLongBitFlag<N, Enum>::getWord(Enum bit) const {
    return mStorage[s32(bit) / BitsPerWord];
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::setBit(Enum bit) {
    return getWord(bit).setBitOn(s32(bit) % BitsPerWord);
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::resetBit(Enum bit) {
    return getWord(bit).setBitOff(s32(bit) % BitsPerWord);
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::changeBit(Enum bit, bool on) {
    if (on)
        return setBit(bit);
    else
        return resetBit(bit);
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::isOnBit(Enum bit) const {
    return getWord(bit).isBitOn(s32(bit) % BitsPerWord);
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::isOffBit(Enum bit) const {
    return !isOnBit(bit);
}

template <s32 N, typename Enum>
inline bool AtomicLongBitFlag<N, Enum>::isZero() const {
    for (const auto& word : mStorage) {
        if (word != 0)
            return false;
    }
    return true;
}

}  // namespace ksys::util

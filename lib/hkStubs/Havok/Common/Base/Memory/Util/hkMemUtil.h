#pragma once

#include <Havok/Common/Base/hkBase.h>

namespace hkMemUtil {

template <unsigned int NBYTES>
struct TypeFromAlign;

template <>
struct TypeFromAlign<1> {
    using type = char;
};

template <>
struct TypeFromAlign<2> {
    using type = hkInt16;
};

template <>
struct TypeFromAlign<4> {
    using type = hkInt32;
};

template <>
struct TypeFromAlign<8> {
    using type = hkInt64;
};

template <unsigned int NBYTES>
struct TypeFromAlign : public TypeFromAlign<NBYTES / 2> {};

template <unsigned int ELEMENTSIZE, unsigned int ELEMENTALIGN>
HK_FORCE_INLINE void memCpyOneAligned(void* dst, const void* src);

template <unsigned int ELEMENTALIGN>
HK_FORCE_INLINE void memCpy(void* dst, const void* src, int nbytes);

void memCpy(void* dst, const void* src, int nbytes);
void memCpyBackwards(void* dst, const void* src, int nbytes);
void memMove(void* dst, const void* src, int nbytes);
void memSet(void* dst, int c, int n);

template <unsigned int ELEMENTSIZE, unsigned int ELEMENTALIGN>
inline void memCpyOneAligned(void* dst, const void* src) {
    using CopyType = typename TypeFromAlign<ELEMENTALIGN>::type;
    unsigned int i = 0;
    do {
        static_cast<CopyType*>(dst)[i] = static_cast<const CopyType*>(src)[i];
    } while (++i < ELEMENTSIZE / sizeof(CopyType));
}

template <unsigned int ELEMENTALIGN>
inline void memCpy(void* dst, const void* src, int nbytes) {
    using CopyType = typename TypeFromAlign<ELEMENTALIGN>::type;
    for (int i = 0, j = 0; i < nbytes; i += sizeof(CopyType), ++j) {
        static_cast<CopyType*>(dst)[j] = static_cast<const CopyType*>(src)[j];
    }
}

}  // namespace hkMemUtil

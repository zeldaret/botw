#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_VECTOR4F_AARCH64_NEON
#endif

using hkVector4fComparisonParameter = const class hkVector4fComparison&;

class hkVector4fComparison {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkVector4fComparison)

    enum Mask {
        INDEX_W = 3,
        INDEX_Z = 2,
        INDEX_Y = 1,
        INDEX_X = 0,

        MASK_NONE = 0x0,              // 0000
        MASK_W = (1 << INDEX_W),      // 0001
        MASK_Z = (1 << INDEX_Z),      // 0010
        MASK_ZW = (MASK_Z | MASK_W),  // 0011

        MASK_Y = (1 << INDEX_Y),        // 0100
        MASK_YW = (MASK_Y | MASK_W),    // 0101
        MASK_YZ = (MASK_Y | MASK_Z),    // 0110
        MASK_YZW = (MASK_YZ | MASK_W),  // 0111

        MASK_X = (1 << INDEX_X),        // 1000
        MASK_XW = (MASK_X | MASK_W),    // 1001
        MASK_XZ = (MASK_X | MASK_Z),    // 1010
        MASK_XZW = (MASK_XZ | MASK_W),  // 1011

        MASK_XY = (MASK_X | MASK_Y),     // 1100
        MASK_XYW = (MASK_XY | MASK_W),   // 1101
        MASK_XYZ = (MASK_XY | MASK_Z),   // 1110
        MASK_XYZW = (MASK_XY | MASK_ZW)  // 1111
    };

    HK_FORCE_INLINE static hkVector4fComparison convert(const m128& x) { return {x}; }

    HK_FORCE_INLINE void setAnd(hkVector4fComparisonParameter a, hkVector4fComparisonParameter b);
    HK_FORCE_INLINE void setAndNot(hkVector4fComparisonParameter a,
                                   hkVector4fComparisonParameter b);
    HK_FORCE_INLINE void setXor(hkVector4fComparisonParameter a, hkVector4fComparisonParameter b);
    HK_FORCE_INLINE void setOr(hkVector4fComparisonParameter a, hkVector4fComparisonParameter b);
    HK_FORCE_INLINE void setNot(hkVector4fComparisonParameter a);

    HK_FORCE_INLINE void setSelect(hkVector4fComparisonParameter comp,
                                   hkVector4fComparisonParameter trueValue,
                                   hkVector4fComparisonParameter falseValue);

    template <Mask m = Mask::MASK_XYZW>
    HK_FORCE_INLINE hkBool32 allAreSet() const;
    HK_FORCE_INLINE hkBool32 allAreSet(Mask m) const;

    template <Mask M = Mask::MASK_XYZW>
    HK_FORCE_INLINE hkBool32 anyIsSet() const;
    HK_FORCE_INLINE hkBool32 anyIsSet(Mask m) const;

    m128u m_mask;
};

inline void hkVector4fComparison::setAnd(hkVector4fComparisonParameter a,
                                         hkVector4fComparisonParameter b) {
    m_mask = a.m_mask & b.m_mask;
}

inline void hkVector4fComparison::setAndNot(hkVector4fComparisonParameter a,
                                            hkVector4fComparisonParameter b) {
    m_mask = a.m_mask & ~b.m_mask;
}

inline void hkVector4fComparison::setXor(hkVector4fComparisonParameter a,
                                         hkVector4fComparisonParameter b) {
    m_mask = a.m_mask ^ b.m_mask;
}

inline void hkVector4fComparison::setOr(hkVector4fComparisonParameter a,
                                        hkVector4fComparisonParameter b) {
    m_mask = a.m_mask | b.m_mask;
}

inline void hkVector4fComparison::setNot(hkVector4fComparisonParameter a) {
    m_mask = ~a.m_mask;
}

inline void hkVector4fComparison::setSelect(hkVector4fComparisonParameter comp,
                                            hkVector4fComparisonParameter trueValue,
                                            hkVector4fComparisonParameter falseValue) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    m_mask = vbslq_u32(comp.m_mask, trueValue.m_mask, falseValue.m_mask);
#else
    m_mask = (comp.m_mask & trueValue.m_mask) | (comp.m_mask & ~falseValue.m_mask);
#endif
}

template <hkVector4fComparison::Mask m>
inline hkBool32 hkVector4fComparison::allAreSet() const {
    return ((m & MASK_X) == 0 || m_mask[0] != 0) && ((m & MASK_Y) == 0 || m_mask[1] != 0) &&
           ((m & MASK_Z) == 0 || m_mask[2] != 0) && ((m & MASK_W) == 0 || m_mask[3] != 0);
}

inline hkBool32 hkVector4fComparison::allAreSet(hkVector4fComparison::Mask m) const {
    return ((m & MASK_X) == 0 || m_mask[0] != 0) && ((m & MASK_Y) == 0 || m_mask[1] != 0) &&
           ((m & MASK_Z) == 0 || m_mask[2] != 0) && ((m & MASK_W) == 0 || m_mask[3] != 0);
}

template <hkVector4fComparison::Mask m>
inline hkBool32 hkVector4fComparison::anyIsSet() const {
    return ((m & MASK_X) != 0 && m_mask[0] != 0) || ((m & MASK_Y) != 0 && m_mask[1] != 0) ||
           ((m & MASK_Z) != 0 && m_mask[2] != 0) || ((m & MASK_W) != 0 && m_mask[3] != 0);
}

inline hkBool32 hkVector4fComparison::anyIsSet(Mask m) const {
    return ((m & MASK_X) != 0 && m_mask[0] != 0) || ((m & MASK_Y) != 0 && m_mask[1] != 0) ||
           ((m & MASK_Z) != 0 && m_mask[2] != 0) || ((m & MASK_W) != 0 && m_mask[3] != 0);
}

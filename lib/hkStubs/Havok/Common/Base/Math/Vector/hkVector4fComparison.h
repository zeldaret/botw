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

#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkFourTransposedPointsf {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkFourTransposedPointsf)
    HK_DECLARE_REFLECTION()

    hkFourTransposedPointsf() {
        for (auto& vertex : m_vertices)
            vertex.setZero();
    }

    hkVector4f m_vertices[3];
};

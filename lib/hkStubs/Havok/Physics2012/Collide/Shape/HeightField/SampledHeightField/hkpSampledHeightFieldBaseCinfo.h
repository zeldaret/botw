#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpSampledHeightFieldBaseCinfo {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSampledHeightFieldBaseCinfo)

    hkpSampledHeightFieldBaseCinfo() {
        m_scale.set(1.0f, 1.0f, 1.0f);
        m_xRes = 2;
        m_zRes = 2;
        m_minHeight = 0.0f;
        m_maxHeight = -1.0f;
        m_useProjectionBasedHeight = false;
    }

    hkVector4 m_scale;
    hkInt32 m_xRes;
    hkInt32 m_zRes;
    hkReal m_minHeight;
    hkReal m_maxHeight;
    hkBool m_useProjectionBasedHeight;
};

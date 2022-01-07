#pragma once

#include <Havok/Common/Base/Math/Matrix/hkRotationf.h>
#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkTransformf {
public:
    hkRotationf m_rotation;
    hkVector4f m_translation;
};

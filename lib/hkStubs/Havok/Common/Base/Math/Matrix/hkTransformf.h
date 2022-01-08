#pragma once

#include <Havok/Common/Base/Math/Matrix/hkRotationf.h>
#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkTransformf {
public:
    hkRotationf& getRotation() { return m_rotation; }
    const hkRotationf& getRotation() const { return m_rotation; }

    hkVector4f& getTranslation() { return m_translation; }
    const hkVector4f& getTranslation() const { return m_translation; }

    hkRotationf m_rotation;
    hkVector4f m_translation;
};

#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkSweptTransformf {
public:
    hkSweptTransformf() {}

    hkVector4f m_centerOfMass0;
    hkVector4f m_centerOfMass1;
    hkQuaternionf m_rotation0;
    hkQuaternionf m_rotation1;
    hkVector4f m_centerOfMassLocal;
};

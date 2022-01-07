#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkMatrix3f {
public:
    hkMatrix3f() {}  // NOLINT(modernize-use-equals-default)

    hkVector4f m_col0;
    hkVector4f m_col1;
    hkVector4f m_col2;
};

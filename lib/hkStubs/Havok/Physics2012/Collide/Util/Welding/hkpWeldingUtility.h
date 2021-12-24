#pragma once

#include <Havok/Common/Base/hkBase.h>

// FIXME: incomplete
class hkpWeldingUtility {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWeldingUtility)

    enum WeldingType {
        WELDING_TYPE_ANTICLOCKWISE = 0,
        WELDING_TYPE_CLOCKWISE = 4,
        WELDING_TYPE_TWO_SIDED = 5,
        WELDING_TYPE_NONE = 6,
    };

    enum SectorType {
        ACCEPT_0 = 1,
        SNAP_0 = 0,
        REJECT = 2,
        SNAP_1 = 4,
        ACCEPT_1 = 3,
    };
};

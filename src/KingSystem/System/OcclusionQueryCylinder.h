#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

// FIXME: requires agl::cull::OcclusionQueryCylinder
class OcclusionQueryCylinder {
public:
    OcclusionQueryCylinder();
    virtual ~OcclusionQueryCylinder();

    void init(sead::Heap* heap);

private:
    u8 _8[0xa0 - 0x8];
};
KSYS_CHECK_SIZE_NX150(OcclusionQueryCylinder, 0xa0);

}  // namespace ksys

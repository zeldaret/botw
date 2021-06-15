#include "KingSystem/Resource/Actor/resResourcePhysics.h"

namespace ksys::res {

void Physics::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool Physics::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return true;

    mParamSet.parse(this, agl::utl::ResParameterArchive{data}, heap);
    return true;
}

}  // namespace ksys::res

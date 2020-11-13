#include "KingSystem/Resource/resResourceUMii.h"

namespace ksys::res {

UMii::UMii() : ParamIO("umii", 0) {}

UMii::~UMii() = default;

bool UMii::parse_(u8* data, size_t, sead::Heap*) {
    agl::utl::ResParameterArchive archive{data + mAllocSize};
    mData = archive.ptr();
    return true;
}

}  // namespace ksys::res

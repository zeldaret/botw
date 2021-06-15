#include "KingSystem/Resource/Actor/resResourceUMii.h"

namespace ksys::res {

UMii::UMii() : ParamIO("umii", 0) {}

UMii::~UMii() = default;

bool UMii::parse_(u8* data, size_t, sead::Heap*) {
    agl::utl::ResParameterArchive archive{data + mAllocSize};
    mArchive = archive;
    return true;
}

}  // namespace ksys::res

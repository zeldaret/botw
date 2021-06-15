#include "KingSystem/Resource/Actor/resResourceLod.h"

namespace ksys::res {

bool Lod::parse_(u8* data, size_t, sead::Heap*) {
    mDisableOutScreenCalcStop.init(false, "DisableOutScreenCalcStop", "", &mHeader);
    mDisableXLinkSkip.init(false, "DisableXLinkSkip", "", &mHeader);
    mDisableCalcSkipFrame.init(4, "DisableCalcSkipFrame", "", &mHeader);
    mDisableConstActor.init(false, "DisableConstActor", "", &mHeader);
    mDistanceScale.init(1.0, "DistanceScale", "", &mHeader);
    mDisableBehaviorSkip.init(false, "DisableBehaviorSkip", "", &mHeader);
    mDisableCalcRescueDistLimit.init(false, "DisableCalcRescueDistLimit", "", &mHeader);

    addObj(&mHeader, "Header");

    if (data)
        applyResParameterArchive(agl::utl::ResParameterArchive{data});

    return true;
}

}  // namespace ksys::res

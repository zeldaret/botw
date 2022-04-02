#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectSystem : public GParamListObject {
public:
    GParamListObjectSystem();
    const char* getName() const override { return "System"; }

    agl::utl::Parameter<sead::SafeString> mSameGroupActorName;
    agl::utl::Parameter<bool> mIsGetItemSelf;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectSystem, 0x80);

inline GParamListObjectSystem::GParamListObjectSystem() {
    auto* const obj = &mObj;

    mSameGroupActorName.init("", "SameGroupActorName", "", obj);
    mIsGetItemSelf.init(false, "IsGetItemSelf", "", obj);
}

}  // namespace ksys::res

#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectEatTarget : public GParamListObject {
public:
    GParamListObjectEatTarget();
    const char* getName() const override { return "EatTarget"; }

    agl::utl::Parameter<sead::SafeString> mFavoriteEatActorNames;
    agl::utl::Parameter<sead::SafeString> mFavoriteEatActorTags;
    agl::utl::Parameter<sead::SafeString> mEatActorNames;
    agl::utl::Parameter<sead::SafeString> mEatActorNames2;
    agl::utl::Parameter<sead::SafeString> mEatActorNames3;
    agl::utl::Parameter<sead::SafeString> mEatActorTags;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectEatTarget, 0x128);

inline GParamListObjectEatTarget::GParamListObjectEatTarget() {
    auto* const obj = &mObj;

    mFavoriteEatActorNames.init("", "FavoriteEatActorNames", "", obj);
    mFavoriteEatActorTags.init("", "FavoriteEatActorTags", "", obj);
    mEatActorNames.init("", "EatActorNames", "", obj);
    mEatActorNames2.init("", "EatActorNames2", "", obj);
    mEatActorNames3.init("", "EatActorNames3", "", obj);
    mEatActorTags.init("", "EatActorTags", "", obj);
}

}  // namespace ksys::res

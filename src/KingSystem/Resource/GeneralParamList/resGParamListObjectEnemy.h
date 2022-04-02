#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectEnemy : public GParamListObject {
public:
    GParamListObjectEnemy();
    const char* getName() const override { return "Enemy"; }

    agl::utl::Parameter<s32> mRank;
    agl::utl::Parameter<s32> mPower;
    agl::utl::Parameter<s32> mDropLife;
    agl::utl::Parameter<s32> mDyingLife;
    agl::utl::Parameter<f32> mLostDist;
    agl::utl::Parameter<f32> mLostHeightMax;
    agl::utl::Parameter<f32> mLostHeightMin;
    agl::utl::Parameter<f32> mLostRayLength;
    agl::utl::Parameter<f32> mLODLostDist;
    agl::utl::Parameter<f32> mLODLostHeightMax;
    agl::utl::Parameter<f32> mLODLostHeightMin;
    agl::utl::Parameter<f32> mIntelligenceLevel;
    agl::utl::Parameter<f32> mEmotionalLevel;
    agl::utl::Parameter<f32> mHeroismLevel;
    agl::utl::Parameter<sead::SafeString> mPartActorName;
    agl::utl::Parameter<bool> mIsMindFriend;
    agl::utl::Parameter<sead::SafeString> mStatusChangeFlag;
    agl::utl::Parameter<f32> mChangeLife;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectEnemy, 0x288);

inline GParamListObjectEnemy::GParamListObjectEnemy() {
    auto* const obj = &mObj;

    mRank.init(0, "Rank", "", obj);
    mPower.init(0, "Power", "", obj);
    mDropLife.init(100, "DropLife", "", obj);
    mDyingLife.init(20, "DyingLife", "", obj);
    mLostDist.init(100.0, "LostDist", "", obj);
    mLostHeightMax.init(30.0, "LostHeightMax", "", obj);
    mLostHeightMin.init(-30.0, "LostHeightMin", "", obj);
    mLostRayLength.init(-1.0, "LostRayLength", "", obj);
    mLODLostDist.init(40.0, "LODLostDist", "", obj);
    mLODLostHeightMax.init(30.0, "LODLostHeightMax", "", obj);
    mLODLostHeightMin.init(-30.0, "LODLostHeightMin", "", obj);
    mIntelligenceLevel.init(0.0, "IntelligenceLevel", "", obj);
    mEmotionalLevel.init(0.0, "EmotionalLevel", "", obj);
    mHeroismLevel.init(0.0, "HeroismLevel", "", obj);
    mPartActorName.init("", "PartActorName", "", obj);
    mIsMindFriend.init(true, "IsMindFriend", "", obj);
    mStatusChangeFlag.init("", "StatusChangeFlag", "", obj);
    mChangeLife.init(-1.0, "ChangeLife", "", obj);
}

}  // namespace ksys::res

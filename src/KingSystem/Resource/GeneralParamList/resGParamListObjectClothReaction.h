#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectClothReaction : public GParamListObject {
public:
    GParamListObjectClothReaction();
    const char* getName() const override { return "ClothReaction"; }

    agl::utl::Parameter<sead::SafeString> mAtkCollidableName;
    agl::utl::Parameter<sead::SafeString> mAtkCollidableBoneName;
    agl::utl::Parameter<f32> mAtkCollidableSpeed;
    agl::utl::Parameter<f32> mAtkCollidableActiveTime;
    agl::utl::Parameter<sead::Vector3f> mAtkCollidableResetPos;
    agl::utl::Parameter<sead::SafeString> mGroundCollidableName;
    agl::utl::Parameter<sead::SafeString> mGroundCollidableBoneName;
    agl::utl::Parameter<f32> mGroundCollidableOffset;
    agl::utl::Parameter<bool> mUseGroundCollidableResetPos;
    agl::utl::Parameter<sead::Vector3f> mGroundCollidableResetPos;
    agl::utl::Parameter<f32> mGroundCollidableMoveSpeed;
    agl::utl::Parameter<sead::SafeString> mWallCollidableName;
    agl::utl::Parameter<sead::SafeString> mWallCollidableBoneName;
    agl::utl::Parameter<f32> mWallCollidableOffset;
    agl::utl::Parameter<sead::SafeString> mPlayerCollidableName;
    agl::utl::Parameter<sead::SafeString> mPlayerCollidableBoneName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectClothReaction, 0x288);

inline GParamListObjectClothReaction::GParamListObjectClothReaction() {
    auto* const obj = &mObj;

    mAtkCollidableName.init("Collidable_Attack", "AtkCollidableName", "", obj);
    mAtkCollidableBoneName.init("Attack", "AtkCollidableBoneName", "", obj);
    mAtkCollidableSpeed.init(6.0, "AtkCollidableSpeed", "", obj);
    mAtkCollidableActiveTime.init(0.5, "AtkCollidableActiveTime", "", obj);
    mAtkCollidableResetPos.init({0.0, 0.0, 2.0}, "AtkCollidableResetPos", "", obj);
    mGroundCollidableName.init("Collidable_Ground_1", "GroundCollidableName", "", obj);
    mGroundCollidableBoneName.init("Ground_1", "GroundCollidableBoneName", "", obj);
    mGroundCollidableOffset.init(0.05, "GroundCollidableOffset", "", obj);
    mUseGroundCollidableResetPos.init(false, "UseGroundCollidableResetPos", "", obj);
    mGroundCollidableResetPos.init({0.0, -1.0, 0.0}, "GroundCollidableResetPos", "", obj);
    mGroundCollidableMoveSpeed.init(300.0, "GroundCollidableMoveSpeed", "", obj);
    mWallCollidableName.init("", "WallCollidableName", "", obj);
    mWallCollidableBoneName.init("", "WallCollidableBoneName", "", obj);
    mWallCollidableOffset.init(0.05, "WallCollidableOffset", "", obj);
    mPlayerCollidableName.init("", "PlayerCollidableName", "", obj);
    mPlayerCollidableBoneName.init("", "PlayerCollidableBoneName", "", obj);
}

}  // namespace ksys::res

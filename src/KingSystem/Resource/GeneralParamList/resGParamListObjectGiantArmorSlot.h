#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGiantArmorSlot : public GParamListObject {
public:
    GParamListObjectGiantArmorSlot();
    const char* getName() const override { return "GiantArmorSlot"; }

    agl::utl::Parameter<sead::SafeString> mSlot0Node;
    agl::utl::Parameter<sead::SafeString> mSlot0RigidBody;
    agl::utl::Parameter<sead::SafeString> mSlot0DefaultActorName;
    agl::utl::Parameter<sead::SafeString> mSlot1Node;
    agl::utl::Parameter<sead::SafeString> mSlot1RigidBody;
    agl::utl::Parameter<sead::SafeString> mSlot1DefaultActorName;
    agl::utl::Parameter<sead::SafeString> mSlot2Node;
    agl::utl::Parameter<sead::SafeString> mSlot2RigidBody;
    agl::utl::Parameter<sead::SafeString> mSlot2DefaultActorName;
    agl::utl::Parameter<sead::SafeString> mSlot3Node;
    agl::utl::Parameter<sead::SafeString> mSlot3RigidBody;
    agl::utl::Parameter<sead::SafeString> mSlot3DefaultActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGiantArmorSlot, 0x218);

inline GParamListObjectGiantArmorSlot::GParamListObjectGiantArmorSlot() {
    auto* const obj = &mObj;

    mSlot0Node.init("", "Slot0Node", "", obj);
    mSlot0RigidBody.init("", "Slot0RigidBody", "", obj);
    mSlot0DefaultActorName.init("", "Slot0DefaultActorName", "", obj);
    mSlot1Node.init("", "Slot1Node", "", obj);
    mSlot1RigidBody.init("", "Slot1RigidBody", "", obj);
    mSlot1DefaultActorName.init("", "Slot1DefaultActorName", "", obj);
    mSlot2Node.init("", "Slot2Node", "", obj);
    mSlot2RigidBody.init("", "Slot2RigidBody", "", obj);
    mSlot2DefaultActorName.init("", "Slot2DefaultActorName", "", obj);
    mSlot3Node.init("", "Slot3Node", "", obj);
    mSlot3RigidBody.init("", "Slot3RigidBody", "", obj);
    mSlot3DefaultActorName.init("", "Slot3DefaultActorName", "", obj);
}

}  // namespace ksys::res

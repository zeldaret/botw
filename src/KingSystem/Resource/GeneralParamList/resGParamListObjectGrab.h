#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGrab : public GParamListObject {
public:
    GParamListObjectGrab();
    const char* getName() const override { return "Grab"; }

    agl::utl::Parameter<sead::SafeString> mSlot0Node;
    agl::utl::Parameter<sead::SafeString> mSlot1Node;
    agl::utl::Parameter<sead::SafeString> mSlot2Node;
    agl::utl::Parameter<sead::SafeString> mSlot3Node;
    agl::utl::Parameter<sead::SafeString> mSlot4Node;
    agl::utl::Parameter<sead::SafeString> mSlot5Node;
    agl::utl::Parameter<sead::SafeString> mSlot0PodNode;
    agl::utl::Parameter<sead::SafeString> mSlot1PodNode;
    agl::utl::Parameter<sead::SafeString> mSlot2PodNode;
    agl::utl::Parameter<sead::SafeString> mSlot3PodNode;
    agl::utl::Parameter<sead::SafeString> mSlot4PodNode;
    agl::utl::Parameter<sead::SafeString> mSlot5PodNode;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGrab, 0x218);

inline GParamListObjectGrab::GParamListObjectGrab() {
    auto* const obj = &mObj;

    mSlot0Node.init("", "Slot0Node", "", obj);
    mSlot1Node.init("", "Slot1Node", "", obj);
    mSlot2Node.init("", "Slot2Node", "", obj);
    mSlot3Node.init("", "Slot3Node", "", obj);
    mSlot4Node.init("", "Slot4Node", "", obj);
    mSlot5Node.init("", "Slot5Node", "", obj);
    mSlot0PodNode.init("", "Slot0PodNode", "", obj);
    mSlot1PodNode.init("", "Slot1PodNode", "", obj);
    mSlot2PodNode.init("", "Slot2PodNode", "", obj);
    mSlot3PodNode.init("", "Slot3PodNode", "", obj);
    mSlot4PodNode.init("", "Slot4PodNode", "", obj);
    mSlot5PodNode.init("", "Slot5PodNode", "", obj);
}

}  // namespace ksys::res

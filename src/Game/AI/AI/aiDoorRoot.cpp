#include "Game/AI/AI/aiDoorRoot.h"

namespace uking::ai {

DoorRoot::DoorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoorRoot::~DoorRoot() = default;

bool DoorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DoorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoorRoot::loadParams_() {
    getStaticParam(&mCloseWaitFrame_s, "CloseWaitFrame");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mOpen_L_AS_s, "Open_L_AS");
    getStaticParam(&mOpen_R_AS_s, "Open_R_AS");
    getStaticParam(&mClose_L_AS_s, "Close_L_AS");
    getStaticParam(&mClose_R_AS_s, "Close_R_AS");
    getMapUnitParam(&mNpcCanOpenFlag_m, "NpcCanOpenFlag");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

}  // namespace uking::ai

#include "Game/AI/Action/actionLandTeleport.h"

namespace uking::action {

LandTeleport::LandTeleport(const InitArg& arg) : TeleportBase(arg) {}

LandTeleport::~LandTeleport() = default;

bool LandTeleport::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void LandTeleport::enter_(ksys::act::ai::InlineParamPack* params) {
    TeleportBase::enter_(params);
}

void LandTeleport::leave_() {
    TeleportBase::leave_();
}

void LandTeleport::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mDistY_s, "DistY");
    getStaticParam(&mSearchClosestPointRadius_s, "SearchClosestPointRadius");
    getStaticParam(&mIsNormalizeAxisY_s, "IsNormalizeAxisY");
}

void LandTeleport::calc_() {
    TeleportBase::calc_();
}

}  // namespace uking::action

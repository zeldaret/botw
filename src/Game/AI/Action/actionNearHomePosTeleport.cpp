#include "Game/AI/Action/actionNearHomePosTeleport.h"

namespace uking::action {

NearHomePosTeleport::NearHomePosTeleport(const InitArg& arg) : LandTeleport(arg) {}

NearHomePosTeleport::~NearHomePosTeleport() = default;

bool NearHomePosTeleport::init_(sead::Heap* heap) {
    return LandTeleport::init_(heap);
}

void NearHomePosTeleport::enter_(ksys::act::ai::InlineParamPack* params) {
    LandTeleport::enter_(params);
}

void NearHomePosTeleport::leave_() {
    LandTeleport::leave_();
}

void NearHomePosTeleport::loadParams_() {
    LandTeleport::loadParams_();
}

void NearHomePosTeleport::calc_() {
    LandTeleport::calc_();
}

}  // namespace uking::action
